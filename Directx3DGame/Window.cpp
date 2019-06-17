#include "Window.h"
#include <sstream>

// ウィンドウクラス
Window::WindowClass Window::WindowClass::windowClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}
Window::WindowClass::~WindowClass()
{
	UnregisterClass(windowClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return windowClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return windowClass.hInstance;
}

// ウィンドウ
Window::Window(int width, int height, const char* name)
{
	// サイズに基づいてウィンドウサイズを計算する
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		throw CHWND_LAST_EXCEPT();
	};

	// ウィンドウを作成してhWndを取得
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	// エラーチェック
	if (hWnd == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}

	// ウィンドウ表示？
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// WinAPI側でウィンドウクラスポインタを格納するためにCreateWindow（）から渡されたcreateパラメータを使う
	if (msg == WM_NCCREATE)
	{
		// 作成データからウィンドウクラスへのptrの抽出
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// ウィンドウインスタンスにptrを格納するようにWinAPI管理のユーザーデータを設定します。
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// セットアップが終了したので、メッセージprocを通常の（非セットアップ）ハンドラに設定します
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// ウィンドウインスタンスハンドラにメッセージを転送する
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// WM_NCCREATEメッセージの前にメッセージが表示されたら、
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// ウィンドウインスタンスへのptrを取得する
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// ウィンドウインスタンスハンドラにメッセージを転送する
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// 例外ウィンドウ
Window::Exception::Exception(int line, const char * file, HRESULT hresult) noexcept
	:
	MyException(line, file),
	hresult(hresult)
{}

const char * Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code]" << GetErrorCode() << std::endl
		<< "[Description]" << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * Window::Exception::GetType() const noexcept
{
	return "My Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hresult) noexcept
{
	char* pMsgBuffer = nullptr;
	DWORD nMsgLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hresult, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuffer), 0, nullptr);

	// 文字列が0だった場合
	if (nMsgLength == 0)
	{
		// 未確認エラーコード
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuffer;
	LocalFree(pMsgBuffer);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hresult;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hresult);
}
