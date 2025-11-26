#include "utils.h"

#include "globals.h"

namespace {
  static bool is_win11;

  static ULONG NT_MAJOR = 0;

  static ULONG NT_MINOR = 0;

  static ULONG NT_BUILD = 0;

  static std::wstring NT_CSD_VERSION;

  static std::string NT_SERVICE_PACK;

  static USHORT NT_SUITE;

  static UCHAR NT_TYPE;
}

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

std::string WinVer;

float getWinNTVersion() {
  // Use RtlGetVersion from winnt.h, not wdm.h
  NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);
  // https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoexw
  OSVERSIONINFOEXW osInfo;

  // Make sure we get the dll
  HMODULE NtDllModule = GetModuleHandleW(L"ntdll");

  // Get and run ntdll.dll function pointer to RtlGetVersion()
  if (NtDllModule && NtDllModule != nullptr) {
    *reinterpret_cast<FARPROC*>(&RtlGetVersion) =
        GetProcAddress(NtDllModule, "RtlGetVersion");
  } else {
    RtlGetVersion = nullptr;
  }

  // Should never be null
  if (RtlGetVersion != nullptr) {
    osInfo.dwOSVersionInfoSize = sizeof osInfo;
    RtlGetVersion(&osInfo);
    NT_MAJOR = osInfo.dwMajorVersion;
    NT_MINOR = osInfo.dwMinorVersion;
    NT_BUILD = osInfo.dwBuildNumber;
    NT_CSD_VERSION = osInfo.szCSDVersion;
    NT_SUITE = osInfo.wSuiteMask;
    NT_TYPE = osInfo.wProductType;
  } else {
    MessageBoxW(g_hMainDlg, strings[IDS_GETVER_ERR], strings[IDS_ERROR], MB_ICONSTOP);
  }
  return 5.1f;
}

std::wstring GetWinVersion() {
  const std::string ver = GetOSName();
  WinVer = ver;
  std::wstring wver = stringToWstring(WinVer);
  return wver;
}

// Use WINNT API functions to get OS and system information
std::string const GetOSName() {
  // Human readable OS name
  std::string OsVer;
  // For obscure versions or pre NT4 SP6
  std::ostringstream debugStream;

  float NT_VER = getWinNTVersion();

  // Get the service pack
  std::string NT_SERVICE_PACK(NT_CSD_VERSION.begin(),
                              NT_CSD_VERSION.end());

  
  if (NT_MAJOR <= 3) {
    NT_FEATURE_VERSION = NT_SERVICE_PACK;
    NT_POST_STRING = NT_FEATURE_VERSION;
  }
  if (NT_MAJOR == 4) {
    if (NT_BUILD < 1381) {
      if (NT_SUITE == VER_SUITE_TERMINAL) {
        NT_FEATURE_VERSION = " Beta Cairo Build";
      } else {
        NT_FEATURE_VERSION = " Beta Hydra Build";
      }
    } else {
      if (NT_SUITE == VER_SUITE_TERMINAL) {
        NT_FEATURE_VERSION = " Terminal Server";
      }
    }
  } else if (NT_MAJOR == 5) {
    switch (NT_MINOR) {
      case 0:
          if (NT_BUILD > 1386 && NT_BUILD < 2195) {
            NT_FEATURE_VERSION = " Beta Win2K Build";
          }
          break;
      case 1:
          if (NT_BUILD > 2196 && NT_BUILD < 2600) {
            NT_FEATURE_VERSION = " Beta Whistler Build";
          }
          if (NT_BUILD == 2700) {
            NT_FEATURE_VERSION = " MCE 2005";
          }
          if (NT_BUILD == 2710) {
            NT_FEATURE_VERSION = " MCE 2005 Update Rollup 2";
          }
          break;
      case 2:
          if (NT_BUILD > 2228 && NT_BUILD < 3790) {
            NT_FEATURE_VERSION = " Beta Whistler Build";
          }
          if (NT_SUITE == VER_SUITE_WH_SERVER) {
            if (NT_BUILD > 1282 && NT_BUILD < 3790) {
              NT_FEATURE_VERSION = " Beta Quattro Build";
            }
          }
          break;
      default:
          NT_FEATURE_VERSION = "";
          break;
    }
  } else if (NT_MAJOR == 6) {
    switch (NT_MINOR) {
      case 0:
          if (NT_BUILD > 3663 && NT_BUILD < 6000) {
            NT_FEATURE_VERSION = " Beta Longhorn Build";
          } else if (NT_BUILD == 6003) {
            NT_FEATURE_VERSION = " KB4489887";
          }
          break;
      case 1:
          if (NT_BUILD > 6429 && NT_BUILD < 7600) {
            NT_FEATURE_VERSION = " Beta Win7 Build";
          }
          break;
      case 2:
          if (NT_BUILD > 7652 && NT_BUILD < 9200) {
            NT_FEATURE_VERSION = " Beta Win8 Build";
          }
          break;
      case 3:
          if (NT_BUILD > 9255 && NT_BUILD < 9600) {
            NT_FEATURE_VERSION = " Beta Blue Build";
          }
          break;
      default:
          NT_FEATURE_VERSION = "";
          break;
    }
    NT_POST_STRING = NT_SERVICE_PACK + NT_FEATURE_VERSION;
    // No such thing as feature releases for Windows 8.1 and below
  } else if (NT_MAJOR >= 10) {
    if (NT_BUILD > 19045) {
      is_win11 = true;
    } else {
      is_win11 = false;
    }

    if (NT_BUILD < 10240) {
      NT_FEATURE_VERSION = "Beta Threshold Build ";
    } else if (NT_BUILD == 10240) {
      NT_FEATURE_VERSION = "1507 (RTM 2015 Release) ";
    } else if (NT_BUILD == 10586) {
      NT_FEATURE_VERSION = "1511 (Nov. 2015 Update) ";
    } else if (NT_BUILD == 14393) {
      NT_FEATURE_VERSION = "1607 (Anniversary Update) ";
    } else if (NT_BUILD == 15063) {
      NT_FEATURE_VERSION = "1703 (Creators Update) ";
    } else if (NT_BUILD == 16299) {
      NT_FEATURE_VERSION = "1709 (Fall Creators Update) ";
    } else if (NT_BUILD == 17134) {
      NT_FEATURE_VERSION = "1803 (Apr. 2018 Update) ";
    } else if (NT_BUILD == 17763) {
      NT_FEATURE_VERSION = "1809 (Oct. 2018 Update) ";
    } else if (NT_BUILD == 18362) {
      NT_FEATURE_VERSION = "1903 (May. 2019 Update) ";
    } else if (NT_BUILD == 18363) {
      NT_FEATURE_VERSION = "1909 (Nov. 2019 Update) ";
    } else if (NT_BUILD == 19041) {
      NT_FEATURE_VERSION = "2004 (May. 2020 Update) ";
    } else if (NT_BUILD == 19042) {
      NT_FEATURE_VERSION = "20H2 (Oct. 2020 Update) ";
    } else if (NT_BUILD == 19043) {
      NT_FEATURE_VERSION = "21H1 (May. 2021 Update) ";
    } else if (NT_BUILD == 19044) {
      NT_FEATURE_VERSION = "21H2 (Nov. 2021 Update) ";
    } else if (NT_BUILD == 19045) {
      NT_FEATURE_VERSION = "22H2 (Oct. 2022 Update) ";
    } else if (NT_BUILD == 20348 || NT_BUILD == 25398) {
      NT_FEATURE_VERSION = "Server 2022 ";
    } else if (NT_BUILD < 22000 && NT_BUILD > 20348 && NT_BUILD != 25398) {
      NT_FEATURE_VERSION = "Beta Build ";
    } else if (NT_BUILD == 22000) {
      NT_FEATURE_VERSION = "21H2 (RTM 2021 Release) ";
    } else if (NT_BUILD == 22621) {
      NT_FEATURE_VERSION = "22H2 (Sep. 2022 Update) ";
    } else if (NT_BUILD == 22631) {
      NT_FEATURE_VERSION = "23H2 (Oct. 2023 Update) ";
    } else if (NT_BUILD == 26100) {
      NT_FEATURE_VERSION = "24H2 (Oct. 2024 Update) ";
    } else {
      NOTREACHED();
    }
  }
  NT_POST_STRING = NT_SERVICE_PACK + NT_FEATURE_VERSION;
  

  if (NT_MAJOR == 3) {
    OsVer = "Windows NT 3.x";
  } else if (NT_MAJOR == 4) {
    // Known to be buggy on NT 4.0, and needs SP6 to work
    switch (NT_MINOR) {
      case 0:
          OsVer = "Windows NT 4.0 ";
          break;
      default:
          debugStream.str("");
          debugStream.clear();
          debugStream << " Unknown Windows "
                      << NT_MAJOR << NT_MINOR
                      << NT_BUILD << std::endl;
          OsVer = debugStream.str();
          break;
    }
  } else if (NT_MAJOR == 5) {
    switch (NT_MINOR) {
      case 0:
          OsVer = "Windows 2000 " + NT_POST_STRING;
          break;
      case 1:
          if (NT_SUITE == VER_SUITE_PERSONAL) {
            OsVer = "Windows XP Home Edition " + NT_POST_STRING;
          } else if (NT_SUITE == VER_SUITE_EMBEDDEDNT) {
            OsVer = "Windows XP Embedded " + NT_POST_STRING;
          } else {
            OsVer = "Windows XP Professional " + NT_POST_STRING;
          }
          break;
      case 2:
          if (NT_SUITE == VER_SUITE_WH_SERVER) {
            OsVer = "Windows Home Server" + NT_POST_STRING;
          } else {
            OsVer = "Windows Server 2003/XP x64 " + NT_POST_STRING;
          }
          break;
      case 5:
          OsVer = "Windows Neptune " + NT_POST_STRING;
          break;
      default:
          debugStream.str("");
          debugStream.clear();
          debugStream << " Unknown Windows "
                      << NT_MAJOR << NT_MINOR
                      << NT_BUILD << std::endl;
          OsVer = debugStream.str();
          break;
    }
  } else if (NT_MAJOR == 6) {
    switch (NT_MINOR) {
      case 0:
          if (NT_TYPE == VER_NT_WORKSTATION) {
            OsVer = "Windows Vista " + NT_POST_STRING;
          } else {
            OsVer = "Windows Server 2008 " + NT_POST_STRING;
          }
          break;
      case 1:
          if (NT_BUILD == 8400 || NT_SUITE == VER_SUITE_WH_SERVER) {
            OsVer = "Windows Home Server 2011 " + NT_POST_STRING;
          } else {
            if (NT_TYPE == VER_NT_WORKSTATION) {
              OsVer = "Windows 7 " + NT_POST_STRING;
            } else {
              OsVer = "Windows Server 2008 R2 " + NT_POST_STRING;
            }
          }
          break;
      case 2:
          if (NT_TYPE == VER_NT_WORKSTATION) {
            OsVer = "Windows 8 " + NT_POST_STRING;
          } else {
            OsVer = "Windows Server 2012 " + NT_POST_STRING;
          }
          break;
      case 3:
          if (NT_TYPE == VER_NT_WORKSTATION) {
            OsVer = "Windows 8.1 " + NT_POST_STRING;
          } else {
            OsVer = "Windows Server 2012 R2 " + NT_POST_STRING;
          }
          break;
      default:
          debugStream.str("");
          debugStream.clear();
          debugStream << " Unknown Windows "
                      << NT_MAJOR << NT_MINOR
                      << NT_BUILD << std::endl;
          OsVer = debugStream.str();
          break;
    }
  } else if (NT_MAJOR == 10) {
    switch (NT_MINOR) {
      case 0: {
          if (!is_win11) {
            if (NT_TYPE == VER_NT_WORKSTATION) {
              OsVer = "Windows 10 " + NT_POST_STRING;
            } else {
              if (NT_BUILD >= 14393 && NT_BUILD < 17763) {
                OsVer = "Windows Server 2016 " + NT_POST_STRING;
              } else if (NT_BUILD >= 17763 && NT_BUILD < 20348) {
                OsVer = "Windows Server 2019 " + NT_POST_STRING;
              } else if (NT_BUILD >= 20348 && NT_BUILD <= 25398) {
                OsVer = "Windows Server 2022 " + NT_POST_STRING;
              } else {
                OsVer = "Windows Server " + NT_POST_STRING;
              }
            }
          } else {
            if (NT_TYPE == VER_NT_WORKSTATION) {
              OsVer = "Windows 11 " + NT_POST_STRING;
            } else {
              if (NT_BUILD == 26100) {
                OsVer = "Windows Server 2025 " + NT_POST_STRING;
              } else {
                OsVer = "Windows Server " + NT_POST_STRING;
              }
            }
          }
          break;
        }
      case 1:
          OsVer = "Windows 12 " + NT_POST_STRING;
          break;
      default:
          debugStream.str("");
          debugStream.clear();
          debugStream << " - Unknown Windows "
                      << NT_MAJOR << NT_MINOR
                      << NT_BUILD << std::endl;
          OsVer = debugStream.str();
          break;
    }
  } else {
    debugStream.str("");
    debugStream.clear();
    debugStream << " - Unknown Windows";
    OsVer = debugStream.str();
    NOTREACHED();
  }

  return OsVer;
}

std::string const GetNTString() {
  // NT version number
  std::string NtVer;
  std::ostringstream debugStream;

  float NT_VER = getWinNTVersion();

  // Make sure that the values returned make sense.
  // NT Kernels with numbers outside this range don't exist
  if (NT_MAJOR >=3 && NT_MAJOR <=11) {
    // Define NtVer as human readable string literal separated by decimals
    NtVer = " " + std::to_string(NT_MAJOR)
                + "." +
                std::to_string(NT_MINOR)
                + "." +
                std::to_string(NT_BUILD);
  }

  return NtVer;
}

// Intentionally execute an invalid opcode to kill the program and signal to debugger
// See http://ref.x86asm.net/coder32.html
void ImmediateDebugCrash() {
#if defined(_WIN32) && !defined(_WIN64)
 #ifdef __MINGW32__
  asm("int3\n\t"
      "ud2");
 #else
  // 32 bit assembly code
  __asm int 3 // Execute int3 interrupt
  __asm {
          UD2 // Execute 0x0F, 0x0B
        }
 #endif // __MINGW32__
#elif defined(_WIN64) // x86_64
  /* MSVC-specific x64 ud2 since MSVC doesn't allow inline assembly
     when compiling for x64 */
  __debugbreak();
#endif // defined(_WIN32) && !defined(_WIN64)
}

// Dumb equivalent of Chromium's implementation
void NotReachedImpl(std::string func_name) {
  // Log function name and then crash the program
  std::string func_string = func_name;
  std::cerr << "NOTREACHED(): " << func_string << std::endl;
  ImmediateDebugCrash();
}
