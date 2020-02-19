#include <windows.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Application app;
	app.run(hInstance);
	return 0;
}
