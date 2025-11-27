#pragma once

#ifndef STRICT
 #define STRICT
#endif 

#ifndef UNICODE
 #define UNICODE
#endif

#ifndef _UNICODE
 #define _UNICODE
#endif

#ifndef WINVER
 #define WINVER 0x0501
#endif // WINVER
#ifndef _WIN32_WINNT
 #if defined(_M_X64) || defined(__amd64__) || defined(_WIN64)
  #define _WIN32_WINNT 0x0502 // Windows XP x64/Server 2003
 #else
  #define _WIN32_WINNT 0x0501 // Windows XP x86
 #endif // defined(_M_X64) || defined(__amd64__) || defined(_WIN64)
#endif // _WIN32_WINNT
#ifndef _WIN64_WINNT
 #define _WIN64_WINNT 0x0502 // Minimum version for 64 bit
#endif // _WIN64_WINNT
#ifndef _WIN32_IE
 #define _WIN32_IE 0x0600 // Minimum Internet Explorer version
#endif // _WIN32_IE

// See https://tedwvc.wordpress.com/2014/01/01/how-to-target-xp-with-vc2012-or-vc2013-and-continue-to-use-the-windows-8-x-sdk/
//#define _USING_V110_SDK71_
#ifndef _ATL_XP_TARGETING
 #define _ATL_XP_TARGETING
#endif // _ATL_XP_TARGETING

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <string>
