#pragma once

#ifndef _CCOUNTDOWNTIMER_H
#define _CCOUNTDOWNTIMER_H
/********************
  头文件及宏定义区
********************/
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>

//#include "sciter-x.h"
//#include "sciter-x-host-callback.h"
#include "sciter-x-window.hpp"
#define debugLogs(logs) pwin->call_function("IA_debugLogs",sciter::value(logs))

/********************
	前向声明区
********************/
using namespace std;
class MainWindow;

/********************
	全局变量声明区
********************/
extern MainWindow *pwin;
extern string g_iniPath;
extern HINSTANCE ghInstance;

/********************
	普通方法声明区
********************/
char * WsGetErrorInfo();
char * WsGetErrorInfo(DWORD err);
string	getCurrentWorkDir();
string getProfileOptions(const char* appName, const char* keyName, string fileLocation = g_iniPath);
wstring getProfileOptions(const wchar_t* appName, const wchar_t* keyName, string fileLocation = g_iniPath);
string setProfileOptions(const char* appName, const char* keyName, string value, string fileLocation = g_iniPath);//执行成功返回大写的"SUCCESS"
string setProfileOptions(const wchar_t* appName, const wchar_t* keyName, wstring value, string fileLocation = g_iniPath);
bool getDebugMode();
string getThemeName();
string getTime();
std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP);
std::wstring CharToWchar(const char* c, size_t m_encode = CP_ACP);


/********************
	  类声明区
********************/

class MainWindow : public sciter::window {
public:
BEGIN_FUNCTION_MAP
	FUNCTION_0("Test", Test);
	FUNCTION_0("NA_getWorkDir", NA_getWorkDir); //NA means native
	FUNCTION_0("NA_getThemeName", NA_getThemeName);
	FUNCTION_0("NA_getTime", NA_getTime);
	FUNCTION_1("NA_setThemeName", NA_setThemeName);
	FUNCTION_1("NA_setTime", NA_setTime);
	FUNCTION_0("NA_getPos", NA_getPos);
	FUNCTION_1("NA_setPos", NA_setPos);
	FUNCTION_3("NA_saveThemeOption", NA_saveThemeOption);
	FUNCTION_2("NA_getThemeOption", NA_getThemeOption);
	FUNCTION_0("NA_getThemeList", NA_getThemeList);
END_FUNCTION_MAP
	sciter::value Test();
	sciter::value NA_getWorkDir();
	sciter::value NA_getThemeName();
	sciter::value NA_getTime();
	sciter::value NA_setThemeName(sciter::value themeName);
	sciter::value NA_setTime(sciter::value time);
	sciter::value NA_getPos();
	sciter::value NA_setPos(sciter::value pos);
	sciter::value NA_saveThemeOption(sciter::value themeName, sciter::value optionName, sciter::value optionValue);
	sciter::value NA_getThemeOption(sciter::value themeName,sciter::value optionName);
	sciter::value NA_getThemeList();
	void onReady();
	MainWindow() : window( SW_ALPHA | SW_MAIN | SW_ENABLE_DEBUG) {}
};

#endif