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
		pTemp[strlen((pTemp)) - 2] = '\0'; //remove cr and newline character
		sprintf_s(pBuf, bufSize, "%0.*s", bufSize, pTemp);
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

string getProfileOptions(char* appName,char* keyName)
{
	char * temp = new char[513];
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	GetPrivateProfileStringA(appName, keyName, "NULL", temp, 512, g_iniPath.c_str());
	string res = temp;
	delete[] temp;
	if (res == "NULL")
		debugLogs(WsGetErrorInfo());
	return res;
}
string setProfileOptions(char* appName, char* keyName, string value)
{
	//WritePrivateProfileString("UserInfo", "WindowStyle", "Circle", g_iniPath.c_str());
	bool ret = WritePrivateProfileStringA(appName, keyName, value.c_str(), g_iniPath.c_str());
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

string getWindowStyle()
{
	return getProfileOptions("UserInfo", "WindowStyle");
}

string getTime()
{
	return getProfileOptions("UserInfo", "Time");
}

std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP)
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

/********************
	类方法定义区
********************/
sciter::value MainWindow::Test() {
#ifdef  _DEBUG
	MessageBox(NULL, "Test", NULL, NULL);
#endif //  _DEBUG

	return sciter::value("NULL");
}

sciter::value MainWindow::NA_getWorkDir()
{
	return sciter::value(getCurrentWorkDir());
}

sciter::value MainWindow::NA_getStyle()
{
	return sciter::value(getWindowStyle());
}

sciter::value MainWindow::NA_getTime()
{
	return sciter::value(getTime());
}

sciter::value MainWindow::NA_setStyle(sciter::value style)
{
	return sciter::value(setProfileOptions("UserInfo","WindowStyle", WcharToChar(style.to_string().c_str())));
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

void MainWindow::onReady()
{
	if (getDebugMode())
	{
		static sciter::debug_output_console console; //- uncomment it if you will need console window
		pwin->call_function("IA_uiDebugMode", sciter::value(true));
	}
}
