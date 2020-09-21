#include "CCountDownTimer.h"

#include "resources.cpp"

//HINSTANCE ghInstance = 0;

#define WINDOW_CLASS_NAME L"¸ß¿¼µ¹¼ÆÊ±"			// the main window class name

int uimain(std::function<int()> run) {
	SciterSetOption(NULL, SCITER_SET_DEBUG_MODE, TRUE);

	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
	MainWindow *pwin = new MainWindow();
	SciterSetOption(pwin->get_hwnd(), SCITER_ALPHA_WINDOW, TRUE);
	::pwin = pwin;
	
	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
	pwin->load(WSTR("this://app/main.html"));

	pwin->expand(false);
	pwin->onReady();
	return run();
}