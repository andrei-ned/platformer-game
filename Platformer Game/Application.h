#pragma once
#include "Game.h"
#include <windows.h>
#include "D3DHandler.h"
#include "WinData.h"
#include "Event.h"

// Boilerplate setup for handling the game
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

	D3DHandler* mpD3D;
	Game* mpGame;
};

