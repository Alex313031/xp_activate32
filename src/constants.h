#ifndef XP_ACTIVATE32_CONSTANTS_H_
#define XP_ACTIVATE32_CONSTANTS_H_

#include <cstdint>
#include <string>

#define assert(x) /*nothing*/

typedef int64_t i64;
typedef uint64_t ui64;

#define MOD 0x16A6B036D7F2A79ULL

#define NON_RESIDUE 43

static const ui64 f[6] = {0, 0x21840136C85381ULL, 0x44197B83892AD0ULL, 0x1400606322B3B04ULL, 0x1400606322B3B04ULL, 1};

#endif // XP_ACTIVATE32_CONSTANTS_H_
