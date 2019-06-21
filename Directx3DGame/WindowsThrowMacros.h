#pragma once

#define CHWND_EXCEPT( hresult ) Window::HresultException( __LINE__,__FILE__,(hresult) )
#define CHWND_LAST_EXCEPT() Window::HresultException( __LINE__,__FILE__,GetLastError() )
#define CHWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )
