#include "Graphics.h"
#include "dxerr.h"
#include <sstream>


// DirectX11ライブラリ
#pragma comment(lib,"d3d11.lib")

// graphics exception checking/throwing macros (some with dxgi infos)
#define GFX_EXCEPT_NOINFO(hresult) Graphics::HresutlException( __LINE__,__FILE__,(hresult) )
#define GFX_THROW_NOINFO(hrcall) if( FAILED( hresult = (hrcall) ) ) throw Graphics::HresultException( __LINE__,__FILE__,hresult )

#ifndef NDEBUG
#define GFX_EXCEPT(hresult) Graphics::HresultException( __LINE__,__FILE__,(hresult),infoManager.GetMessages() )
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if( FAILED( hresult = (hrcall) ) ) throw GFX_EXCEPT(hresult)
#define GFX_DEVICE_REMOVED_EXCEPT(hresult) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hresult),infoManager.GetMessages() )
#else
#define GFX_EXCEPT(hresult) Graphics::HresultException( __LINE__,__FILE__,(hresult) )
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hresult) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hresult) )
#endif

// 初期化
Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	// バッファ情報の設定
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;

	// MSAAの設定
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	
	// ウィンドウの設定
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// for checking results of d3d functions
	HRESULT hresult;

	// デバイスの作成
	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	));
	// gain access to texture subresource in swap chain (back buffer)
	ID3D11Resource* pBackBuffer = nullptr;
	GFX_THROW_INFO(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)));
	GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget));
	pBackBuffer->Release();
}

Graphics::~Graphics()
{
	if (pTarget != nullptr)
	{
		pTarget->Release();
	}
	if (pContext != nullptr)
	{
		pContext->Release();
	}
	if (pSwap != nullptr)
	{
		pSwap->Release();
	}
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
}

void Graphics::EndFrame()
{
	HRESULT hresult;
#ifndef NDEBUG
	infoManager.Set();
#endif
	if (FAILED(hresult = pSwap->Present(1u, 0u)))
	{
		if (hresult == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			throw GFX_EXCEPT(hresult);
		}
	}
}

void Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}


Graphics::HresultException::HresultException(int line, const char * file, HRESULT hresult, std::vector<std::string> infoMsgs) noexcept:
	Exception(line,file),
	hresult(hresult)
{
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* Graphics::HresultException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::HresultException::GetType() const noexcept
{
	return "My Graphics Exception";
}

HRESULT Graphics::HresultException::GetErrorCode() const noexcept
{
	return hresult;
}

std::string Graphics::HresultException::GetErrorString() const noexcept
{
	return DXGetErrorString(hresult);
}

std::string Graphics::HresultException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(hresult, buf, sizeof(buf));
	return buf;
}

std::string Graphics::HresultException::GetErrorInfo() const noexcept
{
	return info;
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "My Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
