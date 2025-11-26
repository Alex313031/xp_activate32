#include "strings.h"

std::wstring stringToWstring(const std::string& str) {
  if (str.empty()) {
    return std::wstring();
  }
#ifdef _WIN32 // Windows: convert 1252/UTF-8 → UTF-16
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
#else // POSIX systems: convert UTF-8 → UTF-16/32 wchar_t
  // Set locale for multibyte conversion (thread-local)
  std::mbstate_t state{};
  const char* src = str.c_str();
  // find required size
  size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
  if (len == static_cast<size_t>(-1)) {
    throw std::runtime_error("mbsrtowcs failed!");
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
#ifdef _WIN32 // Windows: UTF-16 → UTF-8/1252
  int utf8_len = WideCharToMultiByte(
      CP_UTF8, 0,
      wstr.c_str(), -1,
      nullptr, 0,
      nullptr, nullptr
  );

  if (utf8_len == 0) {
    throw std::runtime_error("WideCharToMultiByte failed!");
  }

  // Convert
  std::string result(utf8_len, '\0');
  WideCharToMultiByte(
      CP_UTF8, 0,
      wstr.c_str(), -1,
      &result[0], utf8_len,
      nullptr, nullptr
  );

  // Remove trailing null terminator
  if (!result.empty() && result.back() == '\0') {
    result.pop_back();
  }
#else // POSIX: UTF-16/32 → UTF-8
  std::mbstate_t state{};
  const wchar_t* src = wstr.c_str();

  // Determine required buffer size
  size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
  if (len == static_cast<size_t>(-1)) {
    throw std::runtime_error("wcsrtombs failed!");
  }

  std::string result(len, '\0');

  state = std::mbstate_t{};
  src = wstr.c_str();
  std::wcsrtombs(result.data(), &src, len, &state);
#endif
  return result;
}
