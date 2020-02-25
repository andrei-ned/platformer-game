#pragma once
//#include "SFML/Graphics.hpp"
#include "Game.h"
#include <windows.h>
#include "D3DHandler.h"
#include "WinData.h"

// Boilerplate setup for handling the game
class Application
{
public:
	Application();
	~Application();
	void run(HINSTANCE hInstance);
private:
	Game mGame;
	bool InitMainWindow(int width, int height, HINSTANCE hInstance, const std::string& appName, WNDPROC mssgHandler, bool centred);
	//sf::RenderWindow mWindow;
	WinData mWinData;
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	D3DHandler *pD3D;
};

