#include <Windows.h>
#include "WindowsMessageMap.h"

// HWND hWnd �E�B���h�E�n���h��(�^)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	// �f�o�b�O�E�B���h�̏o��(std::string����char�̃|�C���^�����o��)
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
// �G���g���|�C���g
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR IpCmdLine,
	int nCmdShow)
{
	const auto pClassName = "DirectX3DGame";

	// register window class �E�B���h�E�N���X(�݌v��)�̓o�^
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

	// create window instance �E�B���h�E�̃C���X�^���X(����)���쐬
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// show the window �E�B���h�E��\��
	ShowWindow(hWnd, SW_SHOW);

	// message pump�@���b�Z�[�W���[�v
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
