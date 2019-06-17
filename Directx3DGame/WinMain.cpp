#include "Window.h"

// �G���g���|�C���g
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     IpCmdLine,
	int       nCmdShow)
{
	try
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

			//while (!window.mouse.IsEmpty())
			//{
			//	const auto e = window.mouse.Read();
			//	if (e.GetType() == Mouse::Event::Type::Move)
			//	{
			//		std::ostringstream oss;
			//		oss << "Mouse POsition" << e.GetPosX() << "," << e.GetPosY() << endl;
			//	}
			//}
		}

		if (gResult == 1)
		{
			return -1;
		}

		return msg.wParam;
	}
	catch (const MyException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}
