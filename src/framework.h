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

#ifndef __MINGW32__
 #include <WinSDKVer.h>
#endif // not __MINGW32__

#ifndef WINVER
 #define WINVER _WIN32_WINNT_WINXP
#endif // WINVER
#ifndef _WIN32_WINNT
 #define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif // _WIN32_WINNT
#ifndef _WIN64_WINNT
 #define _WIN64_WINNT _WIN32_WINNT_WS03s // Minimum version for 64 bit
#endif // _WIN64_WINNT
#ifndef _WIN32_IE
 #define _WIN32_IE 0x0600 // Minimum Internet Explorer version
#endif // _WIN32_IE

// See https://tedwvc.wordpress.com/2014/01/01/how-to-target-xp-with-vc2012-or-vc2013-and-continue-to-use-the-windows-8-x-sdk/
//#define _USING_V110_SDK71_
#ifndef _ATL_XP_TARGETING
 #define _ATL_XP_TARGETING
#endif // _ATL_XP_TARGETING

#ifndef __MINGW32__
 #include <SDKDDKVer.h>
#endif // not __MINGW32__

#include <windows.h>
#include <combaseapi.h>
#include <commctrl.h>
#include <commdlg.h>
#include <tchar.h>

#include <iostream>
#include <sstream>
#include <string>
