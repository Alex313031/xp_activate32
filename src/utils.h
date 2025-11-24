#ifndef XP_ACTIVATE32_UTILS_H_
#define XP_ACTIVATE32_UTILS_H_

#include "constants.h"
#include "framework.h"

extern wchar_t strings[16][256];

namespace {
  static ULONG NT_MAJOR = 0;

  static ULONG NT_MINOR = 0;

  static ULONG NT_BUILD = 0;

  static std::wstring NT_CSD_VERSION;

  static std::string NT_SERVICE_PACK;

  static USHORT NT_SUITE;

  static UCHAR NT_TYPE;
}

static std::string NT_FEATURE_VERSION;

static std::string NT_POST_STRING;

// Function to load arbitrary .ico from arbitrary .dll
HANDLE LoadImageFromDLL(LPCWSTR dllName,
                        UINT resourceId,
                        UINT imgType,
                        int width,
                        int height,
                        UINT flags);

// Decide what icon to use for main dialog
HICON getDialogIcon(bool use_custom_icon, int resource, int x, int y);

// App version getter functions
std::string getVersionA();

std::wstring getVersionW();

// Windows version getter functions
float getWinNTVersion();

extern std::string WinVer;

std::wstring GetWinVersion();

std::string const GetOSName();

std::string const GetNTString();

// Debug functions

void NotReachedImpl(std::string func_name);

#ifndef NOTREACHED
#define NOTREACHED() \
        std::string func_name(__FUNC__); \
        NotReachedImpl(func_name);
#endif // NOTREACHED

#endif // XP_ACTIVATE32_UTILS_H_
