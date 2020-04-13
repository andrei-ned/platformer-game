#pragma once
#include "Game.h"
#include <windows.h>
#include "D3DHandler.h"
#include "WinData.h"
#include "Event.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <memory>


// Boilerplate setup for handling the game and directX logic
class Application
{
public:
	static Event<int, int> sOnWindowResize;

	Application();
	~Application();

	void run(HINSTANCE hInstance);
private:
	bool InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred);
	WinData mWinData;
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::unique_ptr<D3DHandler> mpD3D;
	std::unique_ptr<Game> mpGame;
	std::unique_ptr<DirectX::Keyboard> mpKb;
	std::unique_ptr<DirectX::Mouse> mpMouse;
};

