#pragma once
#include "MyWindows.h"
#include "MyException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window
{
public:
	class Exception :public MyException
	{
		using MyException::MyException;
	public:
		static std::string TranslateErrorCode(HRESULT hresult)noexcept;
	};
	class HresultException: public Exception
	{
	public:
		HresultException(int line, const char* file, HRESULT hresult)noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hresult;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
private:
	// �V���O���g���̓E�B���h�E�N���X�̓o�^ / �N���[���A�b�v���Ǘ�
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* windowClassName = "Window";
		static WindowClass windowClass;
		HINSTANCE hInstance;
	};
public:
	// �R���X�g���N�^
	Window(int width, int height, const char* name);
	// �f�X�X�g���N�^
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keyboard;
	Mouse mouse;

private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

