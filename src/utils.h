#ifndef XP_ACTIVATE32_UTILS_H_
#define XP_ACTIVATE32_UTILS_H_

#ifdef __MINGW32__
 extern "C" {
  static __inline__ __attribute__((always_inline)) unsigned long long __emulu(
      const unsigned int a, const unsigned int b) {
    unsigned long long retval;
    __asm__("mull %[b]" : "=A"(retval) : [a] "a"(a), [b] "rm"(b));
    return retval;
  }
 }
 #define __noop(...) ((void)0)
#endif // __MINGW32__

#include <intrin.h>

#include "constants.h"
#include "framework.h"
#include "strings.h"

extern wchar_t strings[16][256];

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
