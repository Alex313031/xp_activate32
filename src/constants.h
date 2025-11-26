#ifndef XP_ACTIVATE32_CONSTANTS_H_
#define XP_ACTIVATE32_CONSTANTS_H_

#include "framework.h"

#include <cstdint>
#include <string>

#include "resource.h"

#define assert(x) /*nothing*/

#ifndef __FUNC__
 #define __FUNC__ __func__
#endif // __FUNC__

typedef int64_t i64;
typedef uint64_t ui64;

#define MOD 0x16A6B036D7F2A79ULL

#define NON_RESIDUE 43

const ui64 f[6] = {0, 0x21840136C85381ULL, 0x44197B83892AD0ULL, 0x1400606322B3B04ULL, 0x1400606322B3B04ULL, 1};

static const CLSID licdllCLSID = {0xACADF079, 0xCBCD, 0x4032, {0x83, 0xF2, 0xFA, 0x47, 0xC4, 0xDB, 0x09, 0x6F}};
static const IID licenseAgentIID = {0xB8CBAD79, 0x3F1F, 0x481A, {0xBB, 0x0C, 0xE7, 0xBB, 0xD7, 0x7B, 0xDD, 0xD1}};
//IID for ICOMLicenseAgent2, with three extra functions
static const IID licenseAgentIID2 = {0x6A07C5A3, 0x9C67, 0x4BB6, {0xB0, 0x20, 0xEC, 0xBE, 0x7F, 0xDF, 0xD3, 0x26}};

const LPCWSTR XP_MISMATCH = L"It seems you are not running Windows XP, \nwould you like to run the program anyway \nin debug mode for testing?";

__inline static constexpr float XP_NTVER = 5.1f;

__inline static constexpr float XP64_NTVER = 5.2f;

#endif // XP_ACTIVATE32_CONSTANTS_H_
