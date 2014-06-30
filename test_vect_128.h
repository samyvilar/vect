#ifndef __TEST_VECT_128_H__
#define __TEST_VECT_128_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vect_128.h"

#include "scalr_types.h"
#include "macro_utils.h"

#include "bits.h"

#define SET_PRINTF_GREEN    "\x1B[32m"
#define SET_PRINTF_RED      "\x1B[31m"
#define RESTORE_PRINTF      "\x1B[0m"
#define error(msg) ({printf("%s\n", msg); exit(-1); -1;})
#define error_with_format(msg, format...) ({\
    printf(SET_PRINTF_RED msg RESTORE_PRINTF, format); \
    exit(-1); \
    -1;})

#define print_ok() printf(SET_PRINTF_GREEN "ok.\n" RESTORE_PRINTF)

#define native_scalr_flt_types  double, float
#define native_scalr_sint_types signed long long int, signed long int, signed int, int, signed short int, short int, short, signed char, char
#define native_scalr_uint_types unsigned long long int, unsigned long int, unsigned int, unsigned short, unsigned char
#define native_scalr_types      native_scalr_flt_types, native_scalr_sint_types, native_scalr_uint_types

typedef double                  double_t;
typedef float                   float_t;

typedef signed long long int    sllint_t;
typedef signed long int         slint_t;
typedef signed int              sint_t;
typedef signed                  s_t;
typedef int                     int_t;
typedef signed short int        ssint_t;
typedef signed short            sshort_t;
typedef signed char             schar_t;
typedef char                    char_t;

typedef unsigned long long int  ullint_t;
typedef unsigned long int       ulint_t;
typedef unsigned int            uint_t;
typedef unsigned                u_t;
typedef unsigned short int      usint_t;
typedef unsigned short          ushort_t;
typedef unsigned char           uchar_t;


#define typedef_native_sclar_types \
    double_t, float_t, \
    sllint_t, slint_t, sint_t, s_t, int_t, ssint_t, sshort_t, schar_t, char_t,  \
    ullint_t, ulint_t, uint_t, u_t, usint_t, ushort_t, uchar_t



#define test_memb_types native_scalr_types, typedef_native_sclar_types

#define enable_test


#endif // __TEST_VECT_128_H__
