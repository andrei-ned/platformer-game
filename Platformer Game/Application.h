#pragma once
//#include "SFML/Graphics.hpp"
#include "Game.h"
#include <windows.h>

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
	struct WinData
	{
		//all windows apps have these handles
		HINSTANCE hAppInst = 0;
		HWND      hMainWnd = 0;
		bool      appPaused = false;
		bool      minimized = false;
		bool      maximized = false;
		bool      resizing = false;
		std::string mainWndCaption;
		int clientWidth;
		int clientHeight;
	};
	WinData mWinData;
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

