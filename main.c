//
//  main.c
//  vect
//
//  Created by Samy Vilar on 6/27/14.
//  Copyright (c) 2014 samyvilar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vect_128.h"

#include "scalr_types.h"
#include "macro_utils.h"

int error(char *msg) {
    printf("%s\n", msg);
    exit(-1);
    return 0;
}

#define error_with_format(msg, format...) ({printf(msg, format); exit(-1); 0;})

#define error_if_memb_t_not(v, exp_t)                                       \
    comp_select(                                                            \
        scalr_types_neq(vect_memb_t(v), exp_t),                             \
        error_with_format(                                                  \
            "Error expected a vector with member type `%s`\n", #exp_t       \
        ),                                                                  \
        (void)0                                                             \
    )

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

void test_vect_128_decl() { // test vect_128 declarations ....
    #define _test_vect_128_decl_by_type_name(_memb_name)    \
        error_if_memb_t_not((vect_128_t(_memb_name)){}, _memb_name);

    #define _test_vect_128_decl_by_expr(_memb_name)         \
        error_if_memb_t_not((vect_128_t((_memb_name)0)){}, _memb_name);

    printf("test_vect_128_decl: ");

#ifdef enable_test
    MAP_2(_test_vect_128_decl_by_type_name, test_memb_types)

    if (!comp_types_eq(vect_128_t(union {}), void))
        error("failed to handle vect_128_t non-scalar member type ...\n");

    if (!comp_types_eq(vect_128_t(union {}, int), int))
        error("failed to return default type while creating a non supported vect_128_t member type ...\n");
#endif
    printf("ok.\n");
}

void test_vect_128_set() { // test vect_128 member initialization ...

    #define _test_vect_set(_comp_kind)  ({                                      \
        vect_128_t(_comp_kind) _v;                                              \
        _comp_kind ms[] = {macro_comma_delim_16((_comp_kind)rand())};           \
        _v = vect_128_set(                                                      \
            _v,                                                                 \
            ms[0], ms[1], ms[2], ms[3], ms[4], ms[5], ms[6], ms[7],             \
            ms[8], ms[9], ms[10], ms[11], ms[12], ms[13], ms[14], ms[15]        \
        );                                                                      \
        typeof(vect_memb_cnt(_v)) index;                                        \
        for (index = 0; index < vect_memb_cnt(_v); index++)                     \
            if (ms[index] != vect_memb(_v, vect_memb_cnt(_v) - index - 1))      \
                error_with_format(                                              \
                    "failed to set vector component at index %lu\n", index      \
                );                                                              \
    });

    printf("test_vect_128_set: ");
    #ifdef enable_test
        MAP_2(_test_vect_set, test_memb_types)
    #endif
    printf("ok\n");
}

void test_vect_128_broad_cast() { // test broadcast ....
    #define _test_vect_128_broad_cast(_memb_kind) ({        \
        vect_128_t(_memb_kind) _v;                          \
        _memb_kind _r = (_memb_kind)rand();                 \
        _v = vect_128_broad_cast(_v, _r);                   \
        int index;                                          \
        for (index = 0; index < vect_memb_cnt(_v); index++) \
            if (_r != vect_memb(_v, index))                 \
                error_with_format(                          \
                    "failed to broadcast member type %s\n", \
                    # _memb_kind                            \
                );                                          \
    });
    printf("test_vect_128_broad_cast: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_broad_cast, test_memb_types);
    #endif
    printf("ok\n");
}

void test_vect_128_load() {
    #define _test_vect_128_load(_memb_kind) ({                          \
        _memb_kind _r[] = {macro_comma_delim_16((_memb_kind)rand())};   \
        vect_128_t(_memb_kind) _v;                                      \
        _v = vect_128_load(_r, _v);                                     \
        int index;                                                      \
        for (index = 0; index < vect_memb_cnt(_v); index++) {           \
            if (vect_memb(_v, index) != _r[index])                      \
                error_with_format(                                      \
                    "failed to load member type %s\n", #_memb_kind      \
                );                                                      \
            _r[index] = -1;                                             \
        }                                                               \
    });

    printf("test_vect_128_load: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_load, test_memb_types)
    #endif
    printf("ok\n");
}

void test_vect_128_store() {
    #define _test_vect_128_store(_memb_kind) ({                             \
        _memb_kind _src[] = {macro_comma_delim_16((_memb_kind)rand())};     \
        _memb_kind _dest[16];                                               \
        vect_128_t(_memb_kind) _v;                                          \
        _v = vect_128_load((typeof(_v) *)_src, _v);                         \
        _v = vect_128_store((typeof(_v) *)_dest, _v);                       \
        if (memcmp(_src, _dest, 16))                                        \
            error_with_format(                                              \
                "failed to store member type %s\n", #_memb_kind             \
            );                                                              \
     });

    printf("test_vect_128_store: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_store, test_memb_types)
    #endif
    printf("ok\n");
}


#define _test_vect_128_bit_bin_oper(oper, _memb_kind) ({            \
    _memb_kind _a[] = {macro_comma_delim_16((_memb_kind)rand())},   \
               _b[] = {macro_comma_delim_16((_memb_kind)rand())};   \
   vect_128_t(_memb_kind) _va, _vb, _vo;                            \
    _va = vect_128_load(_a, _va);                                   \
    _vb = vect_128_load(_a, _vb);                                   \
    _vo = vect_128_ ## oper(_va, _vb, _vo);                         \
    int index;                                                      \
    for (index = 0; index < vect_memb_cnt(_vo); index++)            \
        if (scalr_ ## oper(vect_memb(_va, index), vect_memb(_vb, index)) != vect_memb(_vo, index))  \
            error_with_format(                                      \
                "failed to apply xor over members: %s", #_memb_kind \
           );                                                       \
});


#define _test_vect_128_xor(_memb_kind)  _test_vect_128_bit_bin_oper(xor, _memb_kind)
#define _test_vect_128_and(_memb_kind)  _test_vect_128_bit_bin_oper(and, _memb_kind)
#define _test_vect_128_or(_memb_kind)   _test_vect_128_bit_bin_oper(or, _memb_kind)


void test_vect_128_xor() {
    printf("test_vect_128_xor: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_xor, test_memb_types)
    #endif
    printf("ok\n");
}

void test_vect_128_and() {
    printf("test_vect_128_and: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_and, test_memb_types)
    #endif
    printf("ok\n");
}

void test_vect_128_or() {
    printf("test_vect_128_or: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_or, test_memb_types)
    #endif
    printf("ok\n");
}


void test_vect_128() {
    void (*tests[])() = {
        test_vect_128_decl,           // test declaration of varying component types
        test_vect_128_set,           // test initialization of vector components
        test_vect_128_broad_cast,     // test scalar broadcasting into a vector (duplicate components ...)
        test_vect_128_load,
        test_vect_128_store,
        test_vect_128_xor,
        test_vect_128_and,
        test_vect_128_or
   };

    int index;
    for (index = 0; index < sizeof(tests)/sizeof(tests[0]); index++)
        tests[index]();
}

int main()
{
    test_vect_128();

    return 0;
}
