//--------------------------------------------------------------------------------------
// File: DXErr.h
//
// DirectX Error Library
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once
#include "MyWindows.h"
#include <sal.h>

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------------
// DXGetErrorString
//--------------------------------------------------------------------------------------
const WCHAR* WINAPI DXGetErrorStringW( _In_ HRESULT hresult );
const CHAR* WINAPI DXGetErrorStringA( _In_ HRESULT hresult);
#ifdef UNICODE
#define DXGetErrorString DXGetErrorStringW
#else
#define DXGetErrorString DXGetErrorStringA
#endif
//--------------------------------------------------------------------------------------
// DXGetErrorDescription has to be modified to return a copy in a buffer rather than
// the original static string.
//--------------------------------------------------------------------------------------
void WINAPI DXGetErrorDescriptionW( _In_ HRESULT hresult, _Out_cap_(count) WCHAR* desc, _In_ size_t count );
void WINAPI DXGetErrorDescriptionA( _In_ HRESULT hresult, _Out_cap_(count) CHAR* desc, _In_ size_t count );
#ifdef UNICODE
#define DXGetErrorDescription DXGetErrorDescriptionW
#else
#define DXGetErrorDescription DXGetErrorDescriptionA
#endif
//--------------------------------------------------------------------------------------
//  DXTrace
//
//  Desc:  Outputs a formatted error message to the debug stream
//
//  Args:  WCHAR* strFile   The current file, typically passed in using the 
//                         __FILEW__ macro.
//         DWORD dwLine    The current line number, typically passed in using the 
//                         __LINE__ macro.
//         HRESULT hr      An HRESULT that will be traced to the debug stream.
//         CHAR* strMsg    A string that will be traced to the debug stream (may be NULL)
//         BOOL bPopMsgBox If TRUE, then a message box will popup also containing the passed info.
//
//  Return: The hr that was passed in.  
//--------------------------------------------------------------------------------------
HRESULT WINAPI DXTraceW( _In_z_ const WCHAR* strFile, _In_ DWORD dwLine, _In_ HRESULT hresult, _In_opt_ const WCHAR* strMsg, _In_ bool bPopMsgBox );
//--------------------------------------------------------------------------------------
//  DXTrace
//
//  Desc:  Outputs a formatted error message to the debug stream
//
//  Args:  CHAR* strFile   The current file, typically passed in using the 
//                         __FILE__ macro.
//         DWORD dwLine    The current line number, typically passed in using the 
//                         __LINE__ macro.
//         HRESULT hr      An HRESULT that will be traced to the debug stream.
//         CHAR* strMsg    A string that will be traced to the debug stream (may be NULL)
//         BOOL bPopMsgBox If TRUE, then a message box will popup also containing the passed info.
//
//  Return: The hr that was passed in.  
//--------------------------------------------------------------------------------------
HRESULT WINAPI DXTraceA( _In_z_ const CHAR* strFile, _In_ DWORD dwLine, _In_ HRESULT hresult, _In_opt_ const CHAR* strMsg, _In_ bool bPopMsgBox );
#ifdef UNICODE
#define DXTrace DXTraceW
#else
#define DXTrace DXTraceA
#endif
//--------------------------------------------------------------------------------------
//
// Helper macros
//
//--------------------------------------------------------------------------------------
#if defined(DEBUG) || defined(_DEBUG)
#ifdef UNICODE
#define DXTRACE_MSG(str)              DXTrace( __FILEW__, (DWORD)__LINE__, 0, str, false )
#define DXTRACE_ERR(str,hresult )           DXTrace( __FILEW__, (DWORD)__LINE__, hresult , str, false )
#define DXTRACE_ERR_MSGBOX(str,hresult )    DXTrace( __FILEW__, (DWORD)__LINE__, hresult , str, true )
#else
#define DXTRACE_MSG(str)              DXTrace( __FILE__, (DWORD)__LINE__, 0, str, false )
#define DXTRACE_ERR(str,hresult )           DXTrace( __FILE__, (DWORD)__LINE__, hresult , str, false )
#define DXTRACE_ERR_MSGBOX(str,hresult )    DXTrace( __FILE__, (DWORD)__LINE__, hresult , str, true )
#endif
#else
#define DXTRACE_MSG(str)              (0L)
#define DXTRACE_ERR(str,hresult )           (hresult )
#define DXTRACE_ERR_MSGBOX(str,hresult )    (hresult )
#endif

#ifdef __cplusplus
}
#endif //__cplusplus
