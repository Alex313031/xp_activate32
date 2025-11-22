#ifndef XP_ACTIVATE32_UTILS_H_
#define XP_ACTIVATE32_UTILS_H_

#include "constants.h"
#include "framework.h"

// Function to load arbitrary .ico from arbitrary .dll
HANDLE LoadImageFromDLL(LPCWSTR dllName,
                        UINT resourceId,
                        UINT imgType,
                        int width,
                        int height,
                        UINT flags);

// Decide what icon to use for main dialog
HICON getDialogIcon(bool use_custom_icon, int resource, int x, int y);

// Version getter functions
std::string getVersionA();

std::wstring getVersionW();

#endif // XP_ACTIVATE32_UTILS_H_
