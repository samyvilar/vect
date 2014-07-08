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
#define SET_PRINTF_YELLOW   "\x1B[33m"
#define RESTORE_PRINTF      "\x1B[0m"

#define set_str_color(s, color)  SET_PRINTF_ ## color s  RESTORE_PRINTF

#define error(msg) ({printf(set_str_color("%s\n", RED), msg); exit(-1); -1;})
#define error_with_format(msg, format...) ({    \
    printf(set_str_color(msg, RED), format);    \
    exit(-1);                                   \
    -1;})

#define print_ok() printf(set_str_color("ok.\n", GREEN))

#define print_test_vect_128_name(_test_oper, _test_type) \
printf(                                         \
    "test_vect_128_"                            \
    set_str_color("%s", GREEN) "("              \
    set_str_color("%s", YELLOW) "): "           \
    ,macro_apply(stringify_token, _test_oper)   \
    ,macro_apply(stringify_token, _test_type)   \
)

#define run_test_vect_128(_name, func, args...) ({ \
    print_test_vect_128_name(_name, macro_arg_0(args));      \
    func(args);                                 \
    print_ok();                                 \
})

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

#define signed_long_long_int    signed long long int
#define signed_long_int         signed long int
#define signed_int              signed int
#define signed_short_int        signed short int
#define short_int               short int
#define signed_char             signed char
#define unsigned_long_long_int  unsigned long long int
#define unsigned_long_int       unsigned long int
#define unsigned_int            unsigned int
#define unsigned_short          unsigned short
#define unsigned_char           unsigned char

#define stringify_token(_t) #_t

#define test_vect_128_oper(_name) _test_vect_128_ ## _name


#define _check_side_effects_name(_test_name, _test_type)  _test_side_effects ## _ ## _test_name ## _ ## _test_type

// make sure that an expression is only called onced!
#define _check_side_effects(_test_name, _test_type) \
_test_type _test_side_effects ## _ ## _test_name ## _ ## _test_type (_test_type _rand_value) {  \
    static int _not_called = 1;         \
    if (_not_called) {                  \
        _not_called = 0;                \
        return _rand_value;             \
    }                                   \
    error_with_format("%s(%s): Error expression evaluted more than once!", #_test_name, #_test_type);      \
}                                                               \



#endif // __TEST_VECT_128_H__
