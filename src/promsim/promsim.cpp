#include <windows.h>

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	MessageBox(nullptr, "Hello there!", "PromSim", IDOK);
	return EXIT_SUCCESS;
}