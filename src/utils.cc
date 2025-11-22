#include "utils.h"

HANDLE LoadImageFromDLL(LPCWSTR dllName,
                        UINT resourceId,
                        UINT imgType,
                        int width,
                        int height,
                        UINT flags) {
  // Load the .dll module from supplied name
  HMODULE hModule = LoadLibraryW(dllName);
  if (!hModule) {
    return nullptr;
  }

  // Load the image using LoadImageW
  HANDLE hImage;
  hImage = LoadImageW(
      hModule,                   // hinst
      MAKEINTRESOURCEW(resourceId), // resource name/id
      imgType,
      width,
      height,
      flags);

  // We can free the module after loading unless caller wants otherwise
  if (hImage) {
    FreeLibrary(hModule);
  }

  return hImage;
}

HICON getDialogIcon(bool use_custom_icon, int resource, int x, int y) {
  HICON icon;
  // Get key icon
  static const LPCWSTR dll_name = L"shell32.dll";
  if (use_custom_icon) {
    icon = (HICON)LoadImageFromDLL(
        dll_name,
        resource,
        IMAGE_ICON,
        x,
        y,
        LR_DEFAULTCOLOR);
  } else {
    icon = (HICON)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_SMALL),  // Our normal telephone icon
        IMAGE_ICON,
        x,
        y,
        LR_DEFAULTCOLOR);
  }
  return icon;
}

std::string getVersionA() {
  std::ostringstream ostr;
  ostr << MAJOR_VERSION << "." << MINOR_VERSION << L"." << BUILD_VERSION;
  return ostr.str();
}

std::wstring getVersionW() {
  std::wostringstream wostr;
  wostr << MAJOR_VERSION << L"." << MINOR_VERSION << L"." << BUILD_VERSION;
  return wostr.str();
}
