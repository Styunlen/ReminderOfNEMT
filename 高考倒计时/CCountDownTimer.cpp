/********************
  头文件及宏定义区
********************/
#include "CCountDownTimer.h"
#include <direct.h>
#include <atlstr.h>

/********************
	全局变量定义区
********************/
MainWindow *pwin = nullptr;
sciter::debug_output_console *pconsole = nullptr;
string g_iniPath = getCurrentWorkDir() + "\\options.ini";
string g_themeOptionPath = getCurrentWorkDir() + "\\theme.ini";

/********************
	普通方法定义区
********************/

//方法来源MSDN: https://docs.microsoft.com/zh-cn/windows/win32/fileio/listing-the-files-in-a-directory?redirectedfrom=MSDN
//输出json字符串数组
wstring ListDirs(){
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	string themesDir = getCurrentWorkDir() + "\\themes\\*";
	static wstring ret = wstring();
	ret = L"[";
	HANDLE hFind = FindFirstFile(CharToWchar(themesDir.c_str()).c_str(), &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		ret = L"List dirs with exception: ";
		ret+= CharToWchar(WsGetErrorInfo());
		debugLogs(ret);
		return L"NULL";
	}

	// List all the files in the directory with some info about them.
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!( StrCmpW(ffd.cFileName, L".") && StrCmpW(ffd.cFileName, L"..") ))
				continue;
			ret += L"\"";
			ret += ffd.cFileName;
			ret += L"\",";
		}
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
	ret += L"]";
	return ret;
}
wstring ListFiles(string dir) {
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	dir += "\\*";
	static wstring ret = wstring();
	ret = L"[";
	HANDLE hFind = FindFirstFile(CharToWchar(dir.c_str()).c_str(), &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		ret = L"List dirs with exception: ";
		ret += CharToWchar(WsGetErrorInfo());
		debugLogs(ret);
		return L"NULL";
	}

	// List all the files in the directory with some info about them.
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			ret += L"\"";
			ret += ffd.cFileName;
			ret += L"\",";
		}
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
	ret += L"]";
	return ret;
}

char * WsGetErrorInfo()
{
	static CHAR pBuf[1024] = { 0 };
	const ULONG bufSize = 1024;
	DWORD retSize;
	LPTSTR pTemp = NULL;

	pBuf[0] = '0';

	retSize = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		GetLastError(),
		LANG_NEUTRAL,
		(LPTSTR)&pTemp,
		0,
		NULL);
	if (retSize > 0) {
		pTemp[wcslen(pTemp) - 2] = '\0'; //remove cr and newline character
		sprintf_s(pBuf, bufSize, "%0.*ws", bufSize, pTemp);
		LocalFree((HLOCAL)pTemp);
	}
	return pBuf;
}

char * WsGetErrorInfo(DWORD err)
{
	static CHAR pBuf[1024] = { 0 };
	const ULONG bufSize = 1024;
	DWORD retSize;
	LPTSTR pTemp = NULL;

	pBuf[0] = '0';

	retSize = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,
		err,
		LANG_NEUTRAL,
		(LPTSTR)&pTemp,
		0,
		NULL);
	if (retSize > 0) {
		pTemp[wcslen(pTemp) - 2] = '\0'; //remove cr and newline character
		sprintf_s(pBuf, bufSize, "%0.*ws", bufSize, pTemp);
		LocalFree((HLOCAL)pTemp);
	}
	return pBuf;
}

string	getCurrentWorkDir()
{
	static string ApplicationPath;
	if (ApplicationPath.length() != 0)
		return ApplicationPath;
	char * buffer = new char[MAX_PATH];
	_getcwd(buffer, MAX_PATH);
	ApplicationPath = buffer;
	delete[] buffer;
	return ApplicationPath;
}

string getProfileOptions(string appName, string keyName, string fileLocation)
{
	char * temp = new char[513];
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	GetPrivateProfileStringA(appName.c_str(), keyName.c_str(), "NULL", temp, 512, fileLocation.c_str());
	string res = temp;
	delete[] temp;
	if (res == "NULL")
		debugLogs(WsGetErrorInfo());
	return res;
}

wstring getProfileOptions(wstring appName, wstring keyName, string fileLocation)
{
	wchar_t * temp = new wchar_t[513];
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	GetPrivateProfileStringW(appName.c_str(), keyName.c_str(), L"NULL", temp, 512, CharToWchar(fileLocation.c_str()).c_str());
	wstring res = temp;
	delete[] temp;
	if (res == L"NULL")
		debugLogs(WsGetErrorInfo());
	return res;
}

string setProfileOptions(string appName, string keyName, string value,string fileLocation)
{
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	bool ret = WritePrivateProfileStringA(appName.c_str(), keyName.c_str(), value.c_str(), fileLocation.c_str());
	string res = "SUCCESS";
	if (!ret)
		res = WsGetErrorInfo();
	return res;
}

wstring setProfileOptions(wstring appName, wstring keyName, wstring value, string fileLocation)
{
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	bool ret = WritePrivateProfileStringW(appName.c_str(), keyName.c_str(), value.c_str(), CharToWchar(fileLocation.c_str()).c_str());
	wstring res = L"SUCCESS";
	if (!ret)
		res = CharToWchar( WsGetErrorInfo() );
	return res;
}

bool getDebugMode()
{
	static int ret = -1;
	if (ret != -1) return ret;
	ret = (getProfileOptions("AppOptions", "DebugIsEnabled") == "0") ? 0 : 1;
	return ret;
}

string getThemeName()
{
	return getProfileOptions("AppOptions", "Theme");
}

string getTime()
{
	return getProfileOptions("AppOptions", "Time");
}

std::string WcharToChar(const wchar_t* wp, size_t m_encode)
{
	std::string str;
	int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char	*m_char = new char[len + 1];
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

std::wstring CharToWchar(const char* c, size_t m_encode)
{
	std::wstring str;
	int len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
	wchar_t*	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(m_encode, 0, c, strlen(c), m_wchar, len);
	m_wchar[len] = '\0';
	str = m_wchar;
	delete m_wchar;
	return str;
}

void Color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}//设置输出颜色

void ResetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

string getFormattedTime(string format)
{
	time_t rawtime;
	struct tm info;
	char buffer[80];
	time(&rawtime);
	localtime_s(&info, &rawtime);
	strftime(buffer, 80, format.c_str(), &info);
	return buffer;
}

/********************
	类方法定义区
********************/
sciter::value MainWindow::Test() {
#ifdef  _DEBUG
	MessageBoxA(NULL, "Test", NULL, NULL);
#endif //  _DEBUG

	return sciter::value("NULL");
}

sciter::value MainWindow::NA_getAppOption(sciter::value optionName)
	{
		return sciter::value( getProfileOptions(L"AppOptions", optionName.to_string() ));
	}

sciter::value MainWindow::NA_setAppOption(sciter::value optionName, sciter::value optionValue)
	{
		return sciter::value( setProfileOptions(L"AppOptions", optionName.to_string(), optionValue.to_string()) );
	}

sciter::value MainWindow::NA_getWorkDir()
{
	return sciter::value(getCurrentWorkDir());
}

sciter::value MainWindow::NA_saveThemeOption(sciter::value themeName, sciter::value optionName, sciter::value optionValue)
{
	wstring wstr_optVal = optionValue.to_string().c_str();
	return sciter::value( setProfileOptions(themeName.to_string(),optionName.to_string(), wstr_optVal,g_themeOptionPath));
}

sciter::value MainWindow::NA_getThemeOption(sciter::value themeName, sciter::value optionName)
{
	return sciter::value(getProfileOptions(themeName.to_string(), optionName.to_string(), g_themeOptionPath));
}

sciter::value MainWindow::NA_getThemeList()
{
	return sciter::value(ListDirs());
}

sciter::value MainWindow::NA_getThemeScreenshot(sciter::value themeName)
{
	regex e("\"(screenshot|preview).(jpg|png|gif)\"", std::regex_constants::icase);
	string str = getCurrentWorkDir() + "\\themes\\" + WcharToChar( themeName.to_string().c_str() );
	str = WcharToChar(ListFiles(str).c_str());
	sregex_token_iterator pos(str.cbegin(), str.cend(), e, 0);// 0表示匹配结果的整个字符串，正则表达式中还有三个分组，如果参数为1表示第一个分组，以此类推
	sregex_token_iterator end;
	string ret = "[";
	for (; pos != end; ++pos)
	{
		ret += pos->str(); //已包含引号
	}
	ret += "]";
	return sciter::value( CharToWchar(ret.c_str()) );
}

sciter::value MainWindow::NA_debugLogs(sciter::value logs, sciter::value logType)
{
	//MessageBox(NULL, logs.to_string().c_str(), L"233",NULL);
	if (pconsole == nullptr || !getDebugMode()) return false;
	Color(7);
	pconsole->print("\n ");
	pconsole->print(getFormattedTime().c_str());
	pconsole->print(" ");
	ResetColor();
	pconsole->printf("[");
	if (logType == "DEBUG")
	{
		Color(13);
		pconsole->printf("DEBUG");
	}
	else if (logType == "INFO")
	{
		Color(11);
		pconsole->printf("INFO");
	}
	else if (logType == "ERROR")
	{
		Color(12);
		pconsole->printf("ERROR");
	}
	else
	{
		Color(14);
		pconsole->printf("WARNING");
	}
	ResetColor();
	pconsole->print("] ");
	pconsole->print(logs.to_string().c_str());
	pconsole->print("\n");
	return sciter::value(true);
}

sciter::value MainWindow::NA_getDebugMode()
{
	return sciter::value(getDebugMode());
}

inline string getHitokotoType(char type)
{

	char* hitokotoTypes[] = {"动画", "漫画", "游戏", "文学", "原创", "网络", "其他", "影视", "诗词", "网易云", "哲学", "抖机灵"};
	int index = type - '97';
	return hitokotoTypes[index];
	
}

sciter::value MainWindow::NA_getHitokotos(sciter::value types, sciter::value num)
{
	ifstream infile;
	infile.open("hitokoto/");
	return sciter::value();
}

void MainWindow::showDebugWindow()
{
	if (getDebugMode())
	{
		static sciter::debug_output_console console; //- uncomment it if you will need console window
		pconsole = &console;
		//pwin->call_function("IA_uiDebugMode", sciter::value(true));
		NA_debugLogs(L"Theme installed:");
		NA_debugLogs(ListDirs());
	}
}
