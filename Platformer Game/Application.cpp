#include "Application.h"
#include "GameConstants.h"
#include "Constants.h"
#include <cassert>
#include "DirectXColors.h"
#include "SpriteBatch.h"
#include "CommonStates.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TextureCache.h"
#include "FontCache.h"

using namespace DirectX;

Event<int, int> Application::sOnWindowResize;

Application::Application()
{
}

Application::~Application()
{
}

LRESULT CALLBACK Application::MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Application* me = (Application*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (me) return me->MemberWndProc(hwnd, msg, wParam, lParam);
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK Application::MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	switch (msg)
	{
		// Respond to a keyboard event.
	//case WM_CHAR:
	//	break;
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		break;
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mWinData.appPaused = true;
		}
		else
		{
			mWinData.appPaused = false;
		}
		return 0;
	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;
		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		mWinData.clientWidth = LOWORD(lParam);
		mWinData.clientHeight = HIWORD(lParam);
		if (mpD3D && mpD3D->GetDeviceReady())
		{
			if (wParam == SIZE_MINIMIZED)
			{
				mWinData.appPaused = true;
				mWinData.minimized = true;
				mWinData.maximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				mWinData.appPaused = false;
				mWinData.minimized = false;
				mWinData.maximized = true;
				sOnWindowResize.invoke(mWinData.clientWidth, mWinData.clientHeight);
			}
			else if (wParam == SIZE_RESTORED)
			{

				// Restoring from minimized state?
				if (mWinData.minimized)
				{
					mWinData.appPaused = false;
					mWinData.minimized = false;
					sOnWindowResize.invoke(mWinData.clientWidth, mWinData.clientHeight);
				}
				// Restoring from maximized state?
				else if (mWinData.maximized)
				{
					mWinData.appPaused = false;
					mWinData.maximized = false;
					sOnWindowResize.invoke(mWinData.clientWidth, mWinData.clientHeight);
				}
				else if (mWinData.resizing)
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					sOnWindowResize.invoke(mWinData.clientWidth, mWinData.clientHeight);
				}
			}
		}
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		mWinData.appPaused = true;
		mWinData.resizing = true;
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		mWinData.appPaused = false;
		mWinData.resizing = false;
		sOnWindowResize.invoke(mWinData.clientWidth, mWinData.clientHeight);
		//if (mpD3D)
		//	mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Application::run(HINSTANCE hInstance) {
	InitMainWindow(GameConstants::SCREEN_RES_X, GameConstants::SCREEN_RES_Y, hInstance, GameConstants::WINDOW_NAME, Application::MainWndProc, true);

	LARGE_INTEGER cpuFrequency, time1, time2;
	QueryPerformanceFrequency(&cpuFrequency);
	QueryPerformanceCounter(&time1);
	QueryPerformanceCounter(&time2);
	float deltaTime = 0.0f;
	bool shouldQuit = false;

	mpD3D = new D3DHandler(mWinData);
	DirectX::SpriteBatch spriteBatch(&mpD3D->GetDeviceCtx());
	CommonStates dxstate(&mpD3D->GetDevice());
	TextureCache::get().setDevice(mpD3D->GetDevice());
	FontCache::get().setDevice(mpD3D->GetDevice());

	mpGame = new Game(*mpD3D, spriteBatch);
	Keyboard* kb = new Keyboard;
	Mouse* mouse = new Mouse;

	Event<int> test;
	EventFunction<int> testFunc([](int x) {DBOUT(x); });
	test += testFunc;
	test.invoke(3);

	while (!shouldQuit)
	{
		MSG msg = { 0 };

		// If there are Window messages then process them.
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				shouldQuit = true;
		}

		if (!mWinData.appPaused)
		{
			//mGame.update(deltaTime);
			mpGame->update(deltaTime);

			// Rendering
			mpD3D->BeginRender(DirectX::Colors::Black.v);
			mpD3D->BeginRender(Color(.5,.4,.6,1));
			spriteBatch.Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), &mpD3D->GetWrapSampler());

			mpGame->render();

			spriteBatch.End();
			mpD3D->EndRender();
		}
		else
		{
			Sleep(100);
		}

		QueryPerformanceCounter(&time2);
		deltaTime = (float)(time2.QuadPart - time1.QuadPart) / cpuFrequency.QuadPart;
		time1 = time2;
	}
	
	delete mpD3D;
	delete mpGame;
	delete kb;
	delete mouse;
}

bool Application::InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	assert(mssgHandler);
	mWinData.mainWndCaption = appName;
	mWinData.hAppInst = hInstance;
	mWinData.clientWidth = width;
	mWinData.clientHeight = height;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = mssgHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mWinData.hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mWinData.clientWidth, mWinData.clientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int w = R.right - R.left;
	int h = R.bottom - R.top;

	int offsetX = CW_USEDEFAULT, offsetY = CW_USEDEFAULT;
	if (centred) {
		offsetY = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
		offsetX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	}
	mWinData.hMainWnd = CreateWindow("D3DWndClassName", mWinData.mainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, offsetX, offsetY, w, h, 0, 0, mWinData.hAppInst, 0);
	if (!mWinData.hMainWnd)
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return false;
	}

	SetWindowLongPtr(mWinData.hMainWnd, GWLP_USERDATA, (long)this);

	ShowWindow(mWinData.hMainWnd, SW_SHOW);
	UpdateWindow(mWinData.hMainWnd);

	return true;
}
