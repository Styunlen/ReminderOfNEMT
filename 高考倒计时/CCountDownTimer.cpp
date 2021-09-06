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
string g_iniPath = getCurrentWorkDir() + "\\options.ini";
string g_themeOptionPath = getCurrentWorkDir() + "\\theme.ini";

/********************
	普通方法定义区
********************/

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

string getProfileOptions(const char* appName, const char* keyName, string fileLocation)
{
	char * temp = new char[513];
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	GetPrivateProfileStringA(appName, keyName, "NULL", temp, 512, fileLocation.c_str());
	string res = temp;
	delete[] temp;
	if (res == "NULL")
		debugLogs(WsGetErrorInfo());
	return res;
}

wstring getProfileOptions(const wchar_t* appName, const wchar_t* keyName, string fileLocation)
{
	wchar_t * temp = new wchar_t[513];
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	GetPrivateProfileStringW(appName, keyName, L"NULL", temp, 512, CharToWchar(fileLocation.c_str()).c_str());
	wstring res = temp;
	delete[] temp;
	if (res == L"NULL")
		debugLogs(WsGetErrorInfo());
	return res;
}

string setProfileOptions(const char* appName, const char* keyName, string value,string fileLocation)
{
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	bool ret = WritePrivateProfileStringA(appName, keyName, value.c_str(), fileLocation.c_str());
	string res = "SUCCESS";
	if (!ret)
		res = WsGetErrorInfo();
	return res;
}

string setProfileOptions(const wchar_t* appName, const wchar_t* keyName, wstring value, string fileLocation)
{
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	bool ret = WritePrivateProfileStringW(appName, keyName, value.c_str(), CharToWchar(fileLocation.c_str()).c_str());
	string res = "SUCCESS";
	if (!ret)
		res = WsGetErrorInfo();
	return res;
}

bool getDebugMode()
{
	bool ret = true;
	if (getProfileOptions("UserInfo", "DebugIsEnabled") == "0")
		ret = false;
	return ret;
}

string getThemeName()
{
	return getProfileOptions("UserInfo", "Theme");
}

string getTime()
{
	return getProfileOptions("UserInfo", "Time");
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

/********************
	类方法定义区
********************/
sciter::value MainWindow::Test() {
#ifdef  _DEBUG
	MessageBoxA(NULL, "Test", NULL, NULL);
#endif //  _DEBUG

	return sciter::value("NULL");
}

sciter::value MainWindow::NA_getWorkDir()
{
	return sciter::value(getCurrentWorkDir());
}

sciter::value MainWindow::NA_getThemeName()
{
	return sciter::value(getThemeName());
}

sciter::value MainWindow::NA_getTime()
{
	return sciter::value(getTime());
}

sciter::value MainWindow::NA_setThemeName(sciter::value themeName)
{
	return sciter::value(setProfileOptions("UserInfo","Theme", WcharToChar(themeName.to_string().c_str())));
}

sciter::value MainWindow::NA_setTime(sciter::value time)
{
	return sciter::value(setProfileOptions("UserInfo", "Time", WcharToChar(time.to_string().c_str())));
}

sciter::value MainWindow::NA_getPos()
{
	return sciter::value(getProfileOptions("UserInfo", "WindowPos"));
}

sciter::value MainWindow::NA_setPos(sciter::value pos)
{
	return sciter::value(setProfileOptions("UserInfo", "WindowPos", WcharToChar(pos.to_string().c_str())));
}

sciter::value MainWindow::NA_saveThemeOption(sciter::value themeName, sciter::value optionName, sciter::value optionValue)
{
	wstring wstr_optVal = optionValue.to_string().c_str();
	return sciter::value(setProfileOptions(themeName.to_string().c_str(),optionName.to_string().c_str(), wstr_optVal,g_themeOptionPath));
}

sciter::value MainWindow::NA_getThemeOption(sciter::value themeName, sciter::value optionName)
{
	return sciter::value(getProfileOptions(themeName.to_string().c_str(), optionName.to_string().c_str(), g_themeOptionPath));
}

void MainWindow::onReady()
{
	if (getDebugMode())
	{
		static sciter::debug_output_console console; //- uncomment it if you will need console window
		pwin->call_function("IA_uiDebugMode", sciter::value(true));
	}
}
