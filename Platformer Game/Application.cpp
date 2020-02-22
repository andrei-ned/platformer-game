#include "Application.h"
#include "GameConstants.h"
#include "Constants.h"
#include <cassert>
#include "DirectXColors.h"
#include "SpriteBatch.h"
#include <WICTextureLoader.h>
#include "CommonStates.h"
#include "Sprite.h"

using namespace DirectX;

Application::Application()
{
	//mWindow.create(sf::VideoMode(GameConstants::SCREEN_RES_X, GameConstants::SCREEN_RES_Y), GameConstants::WINDOW_NAME);
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
	case WM_CHAR:
		switch (wParam)
		{
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			break;
		}
		//Game::Get().ProcessKey((char)wParam);
		break;
	case WM_INPUT:
		//Game::Get().mMKIn.MessageEvent((HRAWINPUT)lParam);
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
				mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
			}
			else if (wParam == SIZE_RESTORED)
			{

				// Restoring from minimized state?
				if (mWinData.minimized)
				{
					mWinData.appPaused = false;
					mWinData.minimized = false;
					mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
				}
				// Restoring from maximized state?
				else if (mWinData.maximized)
				{
					mWinData.appPaused = false;
					mWinData.maximized = false;
					mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
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
					mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
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
		if (mpD3D)
			mpD3D->OnResize(mWinData.clientWidth, mWinData.clientHeight);
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
	float deltaTime;
	bool shouldQuit = false;

	mpD3D = new D3DHandler(mWinData);

	//**TESTING
	ID3D11ShaderResourceView *pT;
	DirectX::CreateWICTextureFromFile(&mpD3D->GetDevice(), L"../Assets/Player/Idle.png", nullptr, &pT);
	CommonStates dxstate(&mpD3D->GetDevice());

	Sprite spr(*pT);
	//spr.setTexture(pT);
	//****

	assert(pT);

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
			mpD3D->BeginRender(DirectX::Colors::Blue.v);

			RECT rect;
			

			//mGame.Update
			//mGame.Render

			//**TESTING
			DirectX::SpriteBatch sb(&mpD3D->GetDeviceCtx());
			sb.Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());
			//sb.Draw(pT, SimpleMath::Vector2(-500.0f,0.0f), SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f));
			spr.mOrigin = SimpleMath::Vector2(500.0f, 0.0f);
			spr.render(sb);
			sb.End();
			//****

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
	// Start the game loop 
	//sf::Clock clock;
	//while (mWindow.isOpen())
	//{
	//	// Process events
	//	sf::Event event;
	//	while (mWindow.pollEvent(event))
	//	{
	//		// Close window: exit
	//		if (event.type == sf::Event::Closed)
	//			mWindow.close();
	//		if (event.type == sf::Event::TextEntered)
	//		{
	//			if (event.text.unicode < Constants::ASCII_RANGE)
	//			{
	//				if (static_cast<char>(event.text.unicode) == Constants::ESCAPE_KEY)
	//					mWindow.close();
	//			}
	//		}
	//	}

	//	// Clear screen
	//	mWindow.clear();

	//	mGame.update(clock.restart());
	//	mGame.render(mWindow);

	//	// Update the window
	//	mWindow.display();
	//}
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
