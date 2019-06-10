#include <Windows.h>
#include "WindowsMessageMap.h"

// HWND hWnd ウィンドウハンドル(型)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	// デバッグウィンドの出力(std::stringからcharのポインタを取り出す)
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
// エントリポイント
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR IpCmdLine,
	int nCmdShow)
{
	const auto pClassName = "DirectX3DGame";

	// register window class ウィンドウクラス(設計書)の登録
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance ウィンドウのインスタンス(実体)を作成
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// show the window ウィンドウを表示
	ShowWindow(hWnd, SW_SHOW);

	// message pump　メッセージループ
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == 1)
	{
		return -1;
	}
	else
	{		
		return msg.wParam;		
	}
}
