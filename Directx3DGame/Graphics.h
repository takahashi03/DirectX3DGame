#pragma once
#include "MyWindows.h"
#include "MyException.h"
#include <d3d11.h>
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
	~Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	// Directx11�̃f�o�C�X
	ID3D11Device* pDevice = nullptr;
	// ��ʏo�͗p�̃X���b�v�`�F�C��
	IDXGISwapChain* pSwap = nullptr;
	// �`��p�̃f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};