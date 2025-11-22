#ifndef XP_ACTIVATE32_H_
#define XP_ACTIVATE32_H_

#include <stdint.h>
#include <intrin.h>

#ifndef MAJOR_VERSION
 #define MAJOR_VERSION 1
 #define MINOR_VERSION 0
 #define PATCH_VERSION 1
#endif

#ifndef STRICT
 #define STRICT
#endif 

#ifndef UNICODE
 #define UNICODE
#endif

#ifndef _UNICODE
 #define _UNICODE
#endif

typedef int64_t i64;
typedef uint64_t ui64;

#define MOD 0x16A6B036D7F2A79ULL

#define NON_RESIDUE 43

static const ui64 f[6] = {0, 0x21840136C85381ULL, 0x44197B83892AD0ULL, 0x1400606322B3B04ULL, 0x1400606322B3B04ULL, 1};

#endif // XP_ACTIVATE32_H_
