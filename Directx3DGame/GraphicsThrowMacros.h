#pragma once

#define GFX_EXCEPT_NOINFO(hresult) Graphics::HresutlException( __LINE__,__FILE__,(hresult) )
#define GFX_THROW_NOINFO(hrcall) if( FAILED( hresult = (hrcall) ) ) throw Graphics::HresultException( __LINE__,__FILE__,hresult )

#ifndef NDEBUG
#define GFX_EXCEPT(hresult) Graphics::HresultException( __LINE__,__FILE__,(hresult),infoManager.GetMessages() )
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if( FAILED( hresult = (hrcall) ) ) throw GFX_EXCEPT(hresult)
#define GFX_DEVICE_REMOVED_EXCEPT(hresult) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hresult),infoManager.GetMessages() )
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,v);}}
#else
#define GFX_EXCEPT(hresult) Graphics::HresultException( __LINE__,__FILE__,(hresult) )
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hresult) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hresult) )
#define GFX_THROW_INFO_ONLY(call) (call)
#endif

// macro for importing infomanager into local scope
// this.GetInfoManager(Graphics& gfx) must exist
#ifdef NDEBUG
#define INFOMAN(gfx) HRESULT hr
#else
#define INFOMAN(gfx) HRESULT hr; DxgiInfoManager& infoManager = GetInfoManager((gfx))
#endif