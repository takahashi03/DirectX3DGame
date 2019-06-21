#pragma once
#include "MyWindows.h"
#include "MyException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"

class Graphics
{
public:
	class Exception : public MyException
	{
		using MyException::MyException;
	};
	class HresultException : public Exception
	{
	public:
		HresultException(int line, const char* file, HRESULT hresult, std::vector<std::string> infoMsgs = {})noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hresult;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException :public HresultException
	{
		using HresultException::HresultException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawTestTriangle(float angle, float x, float y);
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	// Directx11のデバイス
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	// 画面出力用のスワップチェイン
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	// 描画用のデバイスコンテキスト
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	// レンダラーターゲット
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;	
	// 深度ステンシルビュー
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};