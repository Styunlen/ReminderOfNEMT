#include "CCountDownTimer.h"

#include "resources.cpp"



HINSTANCE ghInstance = 0;

#define WINDOW_CLASS_NAME L"�߿�����ʱ"			// the main window class name


//
//  FUNCTION: window::init()
//
//  PURPOSE: Registers the window class.
//
bool window::init_class()
{
	static ATOM cls = 0;
	if (cls)
		return true;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wnd_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = ghInstance;
	wcex.hIcon = LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_FAVICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;//MAKEINTRESOURCE(IDC_PLAINWIN);
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FAVICON));

	cls = RegisterClassEx(&wcex);
	return cls != 0;
}

window::window()
{
	init_class();
	_hwnd = CreateWindowEx(
		0,
		WINDOW_CLASS_NAME,
		L"demo",
		WS_POPUP, 100, 100, 500, 500, NULL, NULL, ghInstance, this);
	if (!_hwnd)
		return;

	init();

	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
}

window* window::ptr(HWND hwnd)
{
	return reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

bool window::init()
{
	SciterSetOption(_hwnd, SCITER_ALPHA_WINDOW, TRUE);
	SetWindowLongPtr(_hwnd, GWLP_USERDATA, LONG_PTR(this));
	setup_callback();
	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
	load_file(WSTR("this://app/main.html"));
	
	//load_file(L"http://sciter.com/test/layered/default.html");
	return true;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//

LRESULT CALLBACK window::wnd_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//SCITER integration starts
	BOOL handled = FALSE;
	LRESULT lr = SciterProcND(hWnd, message, wParam, lParam, &handled);
	if (handled)
		return lr;
	//SCITER integration ends

	window* self = ptr(hWnd);

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// the WinMain

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	OleInitialize(0); // for system drag-n-drop

	ghInstance = hInstance;

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Perform application initialization:

	window wnd;

	if (!wnd.is_valid())
		return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAYERED));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	OleUninitialize();

	return (int)msg.wParam;
}

//int uimain(std::function<int()> run) {
//	SciterSetOption(NULL, SCITER_SET_DEBUG_MODE, TRUE);
//#ifdef  _DEBUG
//	sciter::debug_output_console console; //- uncomment it if you will need console window
//#endif //  _DEBUG
//
//
//
//
//	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
//	frame *pwin = new frame();
//
//	::pwin = pwin;
//	// note: this:://app URL is dedicated to the sciter::archive content associated with the application
//	pwin->load(WSTR("this://app/main.html"));
//
//	pwin->expand(false);
//	return run();
//}