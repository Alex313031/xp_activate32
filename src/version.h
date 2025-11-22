#ifndef XP_ACTIVATE32_VERSION_H_
#define XP_ACTIVATE32_VERSION_H_

#pragma code_page(65001) // UTF-8

#include <WinSDKVer.h>

#define WINVER _WIN32_WINNT_WINXP
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define _WIN64_WINNT _WIN32_WINNT_WS03s // Minimum version for 64 bit
#define _WIN32_IE 0x0600 // Minimum Internet Explorer version

// See https://tedwvc.wordpress.com/2014/01/01/how-to-target-xp-with-vc2012-or-vc2013-and-continue-to-use-the-windows-8-x-sdk/
//#define _USING_V110_SDK71_
#define _ATL_XP_TARGETING

#include <SDKDDKVer.h>

// Macro to convert to string
#if !defined(_STRINGIZER) && !defined(STRINGIZE)
 #define _STRINGIZER(in) #in
 #define STRINGIZE(in) _STRINGIZER(in)
#endif

// Main version constant
#ifndef _VERSION
 // Run stringizer above
 #define _VERSION(major,minor,build) STRINGIZE(major) "." STRINGIZE(minor) "." STRINGIZE(build)
#endif

// These next few lines are where we control version number and copyright year
// Adhere to semver > semver.org
#define MAJOR_VERSION 1
#define MINOR_VERSION 0
#define BUILD_VERSION 1

#define MAIN_TITLE L"XP_Activate32"

#ifndef VERSION_STRING
 #define VERSION_STRING _VERSION(MAJOR_VERSION, MINOR_VERSION, BUILD_VERSION)
 #define ABOUT_TITLE L"About XP_Activate32"
 #define ABOUT_VERSION L"xp_activate32 ver. 1.0.1"
 #define ABOUT_COPYRIGHT L"Copyright © 2025 Alex313031"
 #define LEGAL_COPYRIGHT L"© 2025"
#endif // VERSION_STRING

#endif // XP_ACTIVATE32_VERSION_H_
