#ifndef XP_ACTIVATE32_H_
#define XP_ACTIVATE32_H_

#include <intrin.h>

#include "constants.h"
#include "framework.h"
#include "resource.h"

#ifndef STRICT
 #define STRICT
#endif 

#ifndef UNICODE
 #define UNICODE
#endif

#ifndef _UNICODE
 #define _UNICODE
#endif

typedef struct {
  ui64 u[2];
  ui64 v[2];
} TDivisor;

#define ERR_TOO_SHORT 1
#define ERR_TOO_LARGE 2
#define ERR_INVALID_CHARACTER 3
#define ERR_INVALID_CHECK_DIGIT 4
#define ERR_UNKNOWN_VERSION 5
#define ERR_UNLUCKY 6

#define BAD 0xFFFFFFFFFFFFFFFFULL

#define CHARTYPE wchar_t

static FILE* fDummyFile;

ui64 residue_add(ui64 x, ui64 y);

ui64 residue_sub(ui64 x, ui64 y);

uint64_t __umul128(uint64_t multiplier, uint64_t multiplicand, uint64_t *product_hi);

ui64 ui128_quotient_mod(ui64 lo, ui64 hi);

ui64 residue_mul(ui64 x, ui64 y);

ui64 residue_pow(ui64 x, ui64 y);

ui64 inverse(ui64 u, ui64 v);

ui64 residue_inv(ui64 x);

ui64 residue_sqrt(ui64 what);

int find_divisor_v(TDivisor* d);

int polynomial_mul(int adeg, const ui64 a[], int bdeg, const ui64 b[], int resultprevdeg, ui64 result[]);

int polynomial_div_monic(int adeg, ui64 a[], int bdeg, const ui64 b[], ui64* quotient);

void polynomial_xgcd(int adeg, const ui64 a[3], int bdeg, const ui64 b[3], int* pgcddeg, ui64 gcd[3], int* pmult1deg, ui64 mult1[3], int* pmult2deg, ui64 mult2[3]);

int u2poly(const TDivisor* src, ui64 polyu[3], ui64 polyv[2]);

void divisor_add(const TDivisor* src1, const TDivisor* src2, TDivisor* dst);

void divisor_mul(const TDivisor* src, ui64 mult, TDivisor* dst);

void divisor_mul128(const TDivisor* src, ui64 mult_lo, ui64 mult_hi, TDivisor* dst);

unsigned rol(unsigned x, int shift);

void sha1_single_block(unsigned char input[64], unsigned char output[20]);

void Mix(unsigned char* buffer, size_t bufSize, const unsigned char* key, size_t keySize);

void Unmix(unsigned char* buffer, size_t bufSize, const unsigned char* key, size_t keySize);

int generate(const CHARTYPE* installation_id_str, CHARTYPE confirmation_id[49]);

//#undef INTERFACE
//#define INTERFACE ICOMLicenseAgent
//DECLARE_INTERFACE_(ICOMLicenseAgent, IDispatch);

static void OnActivationIdChange(HWND hDlg);

static BOOL LoadLicenseManager(HWND hParentForMsgBox);

static void GetIdFromSystem(HWND hDlg);

static void PutIdToSystem(HWND hDlg);

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // XP_ACTIVATE32_H_
