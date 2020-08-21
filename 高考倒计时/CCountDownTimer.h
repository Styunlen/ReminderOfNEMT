#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "sciter-x.h"
#include "sciter-x-host-callback.h"
#include "resource.h"
using namespace std;

extern HINSTANCE ghInstance;

class window : public sciter::host<window>
{
	HWND _hwnd;

	static LRESULT CALLBACK	wnd_proc(HWND, UINT, WPARAM, LPARAM);
	static window* ptr(HWND hwnd);
	static bool init_class();
public:
	// notification_handler traits:
	HWND      get_hwnd() { return _hwnd; }
	HINSTANCE get_resource_instance() { return ghInstance; }

	window();
	bool init(); // instance
	bool is_valid() const { return _hwnd != 0; }
};


//class frame : public sciter::window {
//public:
//	BEGIN_FUNCTION_MAP
//		//FUNCTION_0("DoTask", DoTask);
//	END_FUNCTION_MAP
//	//sciter::value  DoTask();
//	frame() : window(SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}
//};
//
//extern frame *pwin;