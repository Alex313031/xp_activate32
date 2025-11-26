#include "strings.h"

std::wstring stringToWstring(const std::string& str) {
  if (str.empty()) {
    return std::wstring();
  }
// Windows: convert UTF-8 → UTF-16
#ifdef _WIN32
  // Get length of string
  int wide_len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
  if (wide_len == 0) {
    throw std::runtime_error("MultiByteToWideChar failed!");
  }

  // Convert it!
  std::wstring result(wide_len, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], wide_len);

  // Remove the null terminator added by Windows API ugh
  if (!result.empty() && result.back() == L'\0') {
    result.pop_back();
  }
// POSIX systems: convert UTF-8 → UTF-32 wchar_t
#else
  // Set locale for multibyte conversion (thread-local)
  std::mbstate_t state{};
  const char* src = str.c_str();
  // find required size
  size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
  if (len == static_cast<size_t>(-1)) {
    throw std::runtime_error("mbsrtowcs failed");
  }

  std::wstring result(len, L'\0');
  state = std::mbstate_t{};
  src = str.c_str();
  std::mbsrtowcs(result.data(), &src, len, &state);
#endif
  return result;
}

std::string WstringToString(const std::wstring& wstr) {
  if (wstr.empty()) {
    return std::string();
  }
}
