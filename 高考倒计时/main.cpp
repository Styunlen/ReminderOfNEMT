#include "CCountDownTimer.h"

#include "resources.cpp"

//HINSTANCE ghInstance = 0;

#define WINDOW_CLASS_NAME L"¸ß¿¼µ¹¼ÆÊ±"			// the main window class name

int uimain(std::function<int()> run) {
	SciterSetOption(NULL, SCITER_SET_DEBUG_MODE, TRUE);
	
	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
	MainWindow *pwin = new MainWindow();
	SciterSetOption(pwin->get_hwnd(), SCITER_ALPHA_WINDOW, TRUE);
	SciterSetOption(pwin->get_hwnd(), SCITER_SET_SCRIPT_RUNTIME_FEATURES,
		ALLOW_FILE_IO |
		ALLOW_SOCKET_IO |
		ALLOW_EVAL |
		ALLOW_SYSINFO);
	::pwin = pwin;
	
	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
	pwin->showDebugWindow();
#ifdef _DEBUG
	pwin->load( CharToWchar( (getCurrentWorkDir() + "\\res\\main.html").c_str() ).c_str() );
#else
	pwin->load(WSTR("this://app/main.html"));
#endif // _DEBUG
	pwin->expand(false);
	pwin->call_function("IA_DebugMode",getDebugMode());
	return run();
}