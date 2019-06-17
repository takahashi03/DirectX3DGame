#pragma once
#include "MyWindows.h"
#include "MyException.h"

class Window
{
public:
	class Exception :public MyException
	{
	public:
		Exception(int line, const char* file, HRESULT hresult)noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hresult)noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hresult;
	};
	//{
	//	using MyException::MyException;
	//public:
	//	static std::string TranslateErrorCode(HRESULT hresult) noexcept;
	//};
	//class HresultException : public Exception
	//{
	//public:
	//	HresultException(int line, const char* file, HRESULT hresult) noexcept;
	//	const char* what() const noexcept override;
	//	const char* GetType() const noexcept override;
	//	HRESULT GetErrorCode() const noexcept;
	//	std::string GetErrorDescription() const noexcept;
	//private:
	//	HRESULT hresult;
	//};
	//class NoGfxException : public Exception
	//{
	//public:
	//	using Exception::Exception;
	//	const char* GetType() const noexcept override;
	//};

private:
	// シングルトンはウィンドウクラスの登録 / クリーンアップを管理
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		static constexpr const char* windowClassName = "Window";
		static WindowClass windowClass;
		HINSTANCE hInstance;
	};
public:
	// コンストラクタ
	Window(int width, int height, const char* name);
	// デスストラクタ
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
};

// 例外エラーのヘルパーマクロ
#define CHWND_EXCEPT(hresult)Window::Exception(__LINE__,__FILE__,hresult)
#define CHWND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError())

