#include <Windows.h>
#include "Graphics.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 1280, 720 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,"MainWindow", "Snake", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL
	);

	if (!windowHandle)
		return -1;

	graphics = new Graphics();

	if (!graphics->Init(windowHandle)) {
		delete graphics;
		return -1;
	}


	ShowWindow(windowHandle, nShowCmd);

	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) > 0) {
		DispatchMessage(&message);
	}
	
	delete graphics;

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	/* 
	case WM_CREATE:
		SetTimer(hwnd, 1, 16, NULL);
		break; 
	*/

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		graphics->BeginDraw();
		graphics->ClearScreen(0.f, 0.0f, 0.5f);
		//Spam circles
		for (int i = 0; i < 1000; i++)
		{
			graphics->DrawCircle(
				rand() % 1280,
				rand() % 720,
				rand() % 100,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f
			);

		}
		graphics->EndDraw();

	/*
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	*/

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}