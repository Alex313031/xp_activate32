#pragma once

#include <WinSDKVer.h>

#define WINVER _WIN32_WINNT_WINXP
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define _WIN64_WINNT _WIN32_WINNT_WS03s // Minimum version for 64 bit
#define _WIN32_IE 0x0600 // Minimum Internet Explorer version

// See https://tedwvc.wordpress.com/2014/01/01/how-to-target-xp-with-vc2012-or-vc2013-and-continue-to-use-the-windows-8-x-sdk/
//#define _USING_V110_SDK71_
#define _ATL_XP_TARGETING

#include <SDKDDKVer.h>

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <tchar.h>

#include <iostream>
#include <sstream>
#include <string>
