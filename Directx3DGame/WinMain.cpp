#include "Window.h"

// �G���g���|�C���g
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     IpCmdLine,
	int       nCmdShow)
{
	// Window���C���X�^���X��
	Window window(800, 300, "Winodw");

	// ���b�Z�[�W���[�v
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
