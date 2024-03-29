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
#include <ctime>
#include <regex>
#include <fstream>

//#include "sciter-x.h"
//#include "sciter-x-host-callback.h"
#include "sciter-x-window.hpp"

//#define debugLogs(logs) pwin->call_function("IA_debugLogs",sciter::value(logs))
//以上代码有潜在崩溃的bug，具体查看listDirs中对debugLogs的调用(窗口还未初始化成功，就尝试调用前端方法，引发错误)
#define debugLogs(logs) pwin->NA_debugLogs(logs)
/********************
	前向声明区
********************/
using std::string;
using std::wstring;
using std::regex;
using namespace std::regex_constants;
using std::sregex_token_iterator;
using std::ifstream;
class MainWindow;

/********************
	全局变量声明区
********************/
extern MainWindow *pwin;
extern sciter::debug_output_console *pconsole;
extern string g_iniPath;
extern HINSTANCE ghInstance;

/********************
	普通方法声明区
********************/
char * WsGetErrorInfo();
char * WsGetErrorInfo(DWORD err);
string	getCurrentWorkDir();
string getProfileOptions(string appName, string keyName, string fileLocation = g_iniPath);
wstring getProfileOptions(wstring appName, wstring keyName, string fileLocation = g_iniPath);
string setProfileOptions(string appName, string keyName, string value, string fileLocation = g_iniPath);//执行成功返回大写的"SUCCESS"
wstring setProfileOptions(wstring appName, wstring keyName, wstring value, string fileLocation = g_iniPath);
bool getDebugMode();
string getThemeName();
string getTime();
std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP);
std::wstring CharToWchar(const char* c, size_t m_encode = CP_ACP);
void Color(int a);
void ResetColor();
string getFormattedTime(string format = "%Y-%m-%d %H:%M:%S");

/********************
	  类声明区
********************/

class MainWindow : public sciter::window {
public:
BEGIN_FUNCTION_MAP
	FUNCTION_0("Test", Test); 
	FUNCTION_0("NA_getWorkDir", NA_getWorkDir); //NA means native
	FUNCTION_1("NA_getAppOption", NA_getAppOption);
	FUNCTION_2("NA_setAppOption", NA_setAppOption);
	FUNCTION_3("NA_saveThemeOption", NA_saveThemeOption);
	FUNCTION_2("NA_getThemeOption", NA_getThemeOption);
	FUNCTION_0("NA_getThemeList", NA_getThemeList);
	FUNCTION_1("NA_getThemeScreenshot", NA_getThemeScreenshot);
	FUNCTION_1("NA_isOptionFileExt", NA_isOptionFileExt);
	FUNCTION_2("NA_debugLogs", NA_debugLogs);
	FUNCTION_0("NA_getDebugMode", NA_getDebugMode);
	FUNCTION_2("NA_getHitokotos", NA_getHitokotos);
END_FUNCTION_MAP
	sciter::value Test();
	sciter::value NA_getAppOption(sciter::value optionName);
	sciter::value NA_setAppOption(sciter::value optionName, sciter::value optionValue);
	sciter::value NA_getWorkDir();
	sciter::value NA_saveThemeOption(sciter::value themeName, sciter::value optionName, sciter::value optionValue);
	sciter::value NA_getThemeOption(sciter::value themeName,sciter::value optionName);
	sciter::value NA_getThemeList();
	sciter::value NA_getThemeScreenshot(sciter::value themeName); //返回指定主题的预览图的地址
	sciter::value NA_isOptionFileExt(sciter::value themeName); //返回指定主题是否存在设置页面
	//输出彩色调试信息，方便阅读
	sciter::value NA_debugLogs(sciter::value logs,sciter::value logType="DEBUG" );
	sciter::value NA_getDebugMode();
	sciter::value NA_getHitokotos(sciter::value types, sciter::value num);
	void showDebugWindow();
	MainWindow() : window( SW_MAIN | SW_ENABLE_DEBUG) {}
};

#endif