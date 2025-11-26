#ifndef XP_ACTIVATE32_STRINGS_H_
#define XP_ACTIVATE32_STRINGS_H_

#include "framework.h"

#include <stdexcept>
#include <string>

std::wstring stringToWstring(const std::string& str);

std::string WstringToString(const std::wstring& wstr);

#endif // XP_ACTIVATE32_STRINGS_H_
