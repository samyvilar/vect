#ifndef TEST_VECT_128_BIN_OPER_H
#define TEST_VECT_128_BIN_OPER_H

#include "test_vect_128_common.h"

#define _test_vect_128_load(_memb_type, load_kind, args, d) ({      \
    _memb_type __attribute__ ((aligned (64))) *_r = (typeof(*_r)[16]){macro_comma_delim_16(bits_rand(_memb_type))};\
    vect_128_t(_memb_type) _v, _temp;                               \
    d = vect_128_ ## load_kind args;                                \
    int index;                                                      \
    for (index = 0; index < vect_memb_cnt(_v); index++) {           \
        if (vect_memb(_v, index) != _r[index])                      \
            error_with_format(                                      \
                "failed to load member type %s\n", #_memb_type      \
            );                                                      \
        _r[index] = -1;                                             \
    }                                                               \
});


#define _test_vect_128_load_bin(_memb_type)             _test_vect_128_load(_memb_type, load, (_single_eval(_r, 0), _v), _temp)
#define _test_vect_128_load_bin_assign(_memb_type)             _test_vect_128_load(_memb_type, load, (_single_eval(_r, 1), _v), _v)
#define _test_vect_128_load_align_bin(_memb_type)       _test_vect_128_load(_memb_type, load_align, (_single_eval(_r, 2), _v), _temp)
#define _test_vect_128_load_align_bin_assign(_memb_type)       _test_vect_128_load(_memb_type, load_align, (_single_eval(_r, 3), _v), _v)

#define _test_vect_128_load_unr(_memb_type)             _test_vect_128_load(_memb_type, load, (_single_eval(_r, 4)), _v)
#define _test_vect_128_load_align_unr(_memb_type)       _test_vect_128_load(_memb_type, load_align, (_single_eval(_r, 6)), _v)
#define _test_vect_128_load_unr_vect_128_p(_memb_type)  _test_vect_128_load(_memb_type, load, ((vect_128_t(_r[0]) *)_single_eval(_r, 5)), _v)
#define _test_vect_128_load_align_unr_vect_128_p(_memb_type) _test_vect_128_load(_memb_type, load_align, ((vect_128_t(_r[0]) *)_single_eval(_r, 7)), _v)


#define macro_packed_args(f, args) f args

#define _test_vect_128_oper(oper, _memb_type, args...) ({                                           \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))},                              \
               _b[16] = {macro_comma_delim_16(bits_rand(_memb_type))}, _res;                        \
   vect_128_t(_memb_type) _va, _vb, _vo, _vo_vect_sclr, _vo_sclr_vect, _vo_sclr_sclr;               \
    _va = vect_128_load(_a, _va);                                                                   \
    _vb = vect_128_load(_b, _vb);                                                                   \
    _vo           = macro_packed_args(vect_128_ ## oper, macro_arg_0(args));                        \
    _vo_vect_sclr = macro_packed_args(vect_128_ ## oper, macro_arg_1(args));                        \
    _vo_sclr_vect = macro_packed_args(vect_128_ ## oper, macro_arg_2(args));                        \
    _vo_sclr_sclr = macro_packed_args(vect_128_ ## oper, macro_arg_3(args));                        \
    int index;                                                                                      \
    for (index = 0; index < vect_memb_cnt(_vo); index++)                                            \
        if ((_res = (scalr_oper(oper)(_a[index], _b[index]))) != vect_memb(_vo, index))             \
            error_with_format(                                                                      \
                "failed to apply operator vector_128_%s on types: %s\n"                             \
                /*"got: (%s %s %s) == (%s) =/= (%s)\n"*/,                                           \
                #oper, #_memb_type                                                                  \
                /*,scalr_str((char [128]){}, _a[index]),                                            \
                macro_apply(token_str, oper_symbl(oper)),                                           \
                scalr_str((char [128]){}, _b[index]),                                               \
                scalr_str((char [128]){}, _res),                                                    \
                scalr_str((char [128]){}, vect_memb(_vo, index))*/                                  \
           );                                                                                       \
    for (index = 0; index < vect_memb_cnt(_vo_sclr_vect); index++)  {                               \
        if ((_res = (scalr_oper(oper)(_a[0], _b[index]))) != vect_memb(_vo_sclr_vect, index))       \
            error_with_format(                                                                      \
                "failed to broadcast operand a and apply operator vector_128_%s on types: %s\n"     \
                ,#oper, #_memb_type                                                                 \
            );                                                                                      \
        if ((_res = (scalr_oper(oper)(_a[index], _b[0]))) != vect_memb(_vo_vect_sclr, index))       \
            error_with_format(                                                                      \
                "failed to broadcast operand b and apply operator vector_128_%s on types: %s\n"     \
                ,#oper, #_memb_type                                                                 \
            );                                                                                      \
        if ((_res = (scalr_oper(oper)(_a[0], _b[0]))) != vect_memb(_vo_sclr_sclr, index))           \
            error_with_format(                                                                      \
                "failed to broadcast operand a, b and apply operator vector_128_%s on types: %s\n"  \
                ,#oper, #_memb_type                                                                 \
            );                                                                                      \
    }                                                                                               \
})


#define tnr_opers_0     (_single_eval(_va, 0), _single_eval(_vb, 1), _vo)
#define tnr_opers_1     (_single_eval(_va, 2), _single_eval(_b[0], 3), _vo_vect_sclr)
#define tnr_opers_2     (_single_eval(_a[0], 4), _single_eval(_vb, 5), _vo_sclr_vect)
#define tnr_opers_3     (_single_eval(_a[0], 6), _single_eval(_b[0], 7), _vo_sclr_sclr)
#define tnr_opers   tnr_opers_0, tnr_opers_1, tnr_opers_2, tnr_opers_3

#define bin_opers_0     (_single_eval(_va, 0), _single_eval(_vb, 1))
#define bin_opers_1     (_single_eval(_va, 2), _single_eval(_b[0], 3))
#define bin_opers_2     (_single_eval(_a[0], 4), _single_eval(_vb, 5))
#define bin_opers_3     (_single_eval(_a[0], 6), _single_eval(_b[0], 7))
#define bin_opers   bin_opers_0, bin_opers_1, bin_opers_2, bin_opers_3


#define _test_vect_128_xor_tnr(_memb_type)  _test_vect_128_oper(xor, _memb_type, tnr_opers)
#define _test_vect_128_and_tnr(_memb_type)  _test_vect_128_oper(and, _memb_type, tnr_opers)
#define _test_vect_128_or_tnr(_memb_type)   _test_vect_128_oper(or,  _memb_type, tnr_opers)
#define _test_vect_128_add_tnr(_memb_type)  _test_vect_128_oper(add, _memb_type, tnr_opers)
#define _test_vect_128_sub_tnr(_memb_type)  _test_vect_128_oper(sub, _memb_type, tnr_opers)
#define _test_vect_128_mul_tnr(_memb_type)  _test_vect_128_oper(mul, _memb_type, tnr_opers)

#define _test_vect_128_xor_bin(_memb_type)  _test_vect_128_oper(xor, _memb_type, bin_opers)
#define _test_vect_128_and_bin(_memb_type)  _test_vect_128_oper(and, _memb_type, bin_opers)
#define _test_vect_128_or_bin(_memb_type)   _test_vect_128_oper(or,  _memb_type, bin_opers)
#define _test_vect_128_add_bin(_memb_type)  _test_vect_128_oper(add, _memb_type, bin_opers)
#define _test_vect_128_sub_bin(_memb_type)  _test_vect_128_oper(sub, _memb_type, bin_opers)
#define _test_vect_128_mul_bin(_memb_type)  _test_vect_128_oper(mul, _memb_type, bin_opers)

#define to_binary(buffer, expr) ({\
    typeof(expr) e = (expr);  \
    char *dest = (buffer);\
    int __index;  \
    for (__index = 0; __index < bit_size(e); __index++) {\
        dest[bit_size(e) - __index - 1] = '0' + scalr_and(_interp(e, flt32bit_t, uint32bit_t), 1);  \
        e = scalr_rshift_logic(e, 1);   \
    }\
    dest; })

#define local_temp_str (char [512]){}
// test
#define _test_vect_128_shift(shift_direct, _memb_type, shift_arg, args...) ({                    \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))}, _res;    \
    vect_128_t(_memb_type) _va, _vo, _vb;                                        \
    _va = vect_128_load(_a, _va);                                           \
    _vo = vect_128_ ## shift_direct(_single_eval(_va, 0), args);                              \
    _vb = vect_128_ ## shift_direct(_single_eval(_a[0], 10), shift_arg);  \
    /*vect_128_ ## shift_direct(_single_eval(_a[0], 11), shift_arg, _vb);*/  \
    int index;                                                              \
    for (index = 0; index < vect_memb_cnt(_vo); index++)                    \
        if (scalr_cmp_bits_neq((_res = scalr_oper(shift_direct)(_a[index], shift_arg)), vect_memb(_vo, index))) \
            error_with_format(                                              \
                "failed to apply operator vect_128_%s(%s, %s)\n"            \
                "got: (%s %s %s) == (%s) =/= (%s)\n"                        \
                /*"bin(%s): (%s)\n"   \
                "bin(%s): (%s)\n"   \
                "bin(%s): (%s)\n"*/   \
                ,#shift_direct, #_memb_type, #shift_arg                                \
                ,scalr_str(local_temp_str, _a[index])                       \
                ,macro_apply(token_str, oper_symbl(shift_direct))                   \
                ,scalr_str(local_temp_str, shift_arg)                          \
                ,scalr_str(local_temp_str, _res)                            \
                ,scalr_str(local_temp_str, vect_memb(_vo, index))           \
                /*,scalr_str(local_temp_str, _a[index]), to_binary(local_temp_str, _a[index])           \
                ,scalr_str(local_temp_str, _res), to_binary(local_temp_str, _res)           \
                ,scalr_str(local_temp_str, vect_memb(_vo, index)), to_binary(local_temp_str, vect_memb(_vo, index))*/ \
            );                                                              \
        else if (scalr_cmp_bits_neq((_res = scalr_oper(shift_direct)(_a[0], shift_arg)), vect_memb(_vb, index))) \
            error_with_format("failed to broadcast initial operand of vect_128_%s\n", #shift_direct); \
    })

#define _test_vect_128_lshift_imm_bin(_memb_type) _test_vect_128_shift(lshift, _memb_type, 5, 5)
#define _test_vect_128_lshift_imm_tnr(_memb_type) _test_vect_128_shift(lshift, _memb_type, 5, 5, _vo)

#define _test_vect_128_shift_scalr(shift_kind, _memb_type, args...) ({  \
    int temp = rand() % bit_size(_memb_type);   \
    _test_vect_128_shift(shift_kind, _memb_type, temp, args);     \
})
#define _test_vect_128_lshift_scalr_bin(_memb_type) _test_vect_128_shift_scalr(lshift, _memb_type, temp)
#define _test_vect_128_lshift_scalr_tnr(_memb_type) _test_vect_128_shift_scalr(lshift, _memb_type, _single_eval(temp, 1), _vo)


#define _test_vect_128_rshift_logic_imm_bin(_memb_type)     _test_vect_128_shift(rshift_logic, _memb_type, 5, 5)
#define _test_vect_128_rshift_logic_imm_tnr(_memb_type)     _test_vect_128_shift(rshift_logic, _memb_type, 5, 5, _vo)
#define _test_vect_128_rshift_logic_scalr_bin(_memb_type)   _test_vect_128_shift_scalr(rshift_logic, _memb_type, _single_eval(temp, 1))
#define _test_vect_128_rshift_logic_scalr_tnr(_memb_type)   _test_vect_128_shift_scalr(rshift_logic, _memb_type, _single_eval(temp, 1), _vo)

#define _test_vect_128_rshift_arith_imm_bin(_memb_type)     _test_vect_128_shift(rshift_arith, _memb_type, 5, 5)
#define _test_vect_128_rshift_arith_imm_tnr(_memb_type)     _test_vect_128_shift(rshift_arith, _memb_type, 5, 5, _vo)
#define _test_vect_128_rshift_arith_scalr_bin(_memb_type)   _test_vect_128_shift_scalr(rshift_arith, _memb_type, _single_eval(temp, 1))
#define _test_vect_128_rshift_arith_scalr_tnr(_memb_type)   _test_vect_128_shift_scalr(rshift_arith, _memb_type, _single_eval(temp, 1), _vo)



#define _test_vect_128_extrt_imm_at_(_memb_type, va, index)     \
    if (vect_128_extrt_imm(va, (index % vect_memb_cnt(va))) != vect_memb(va, (index % vect_memb_cnt(va)))) \
        error_with_format("failed to apply vect_128_extrt_imm(%s)\n", #_memb_type)


#define _test_vect_128_extrt_imm(_memb_type)  ({    \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))};    \
    vect_128_t(_memb_type) _va;     \
    _va = vect_128_load(_a, _va);   \
    if (vect_128_extrt_imm(_va, 0) != vect_memb(_va, 0))    \
        error_with_format("failed to apply vect_128_%s(%s)\n", "extrt_imm", #_memb_type);           \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 1);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 2);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 3);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 4);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 5);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 6);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 7);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 8);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 9);    \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 10);   \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 11);   \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 12);   \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 13);   \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 14);   \
    _test_vect_128_extrt_imm_at_(_memb_type, _va, 15);   \
})


#ifndef _test_type
    #error please specify the vector component type using -D_test_type=a_type_name
#endif


#endif // TEST_VECT_128_BIN_OPER_H
