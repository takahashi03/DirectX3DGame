#pragma once
#include "WindowsSet.h"

class Window
{
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
	Window(int width, int height,const char* name);
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

