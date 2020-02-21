#pragma once

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
