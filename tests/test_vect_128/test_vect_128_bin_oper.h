#ifndef TEST_VECT_128_BIN_OPER_H
#define TEST_VECT_128_BIN_OPER_H

#include "test_vect_128_common.h"

#define _test_vect_128_bin_oper(oper, _memb_type) ({                                                \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))},                              \
               _b[16] = {macro_comma_delim_16(bits_rand(_memb_type))}, _res;                        \
   vect_128_t(_memb_type) _va, _vb, _vo, _vo_vect_sclr, _vo_sclr_vect, _vo_sclr_sclr;               \
    _va = vect_128_load(_a, _va);                                                                   \
    _vb = vect_128_load(_b, _vb);                                                                   \
    _vo = vect_128_ ## oper(_va, _vb, _vo);                                                         \
    _vo_vect_sclr = vect_128_ ## oper(_va, _b[0], _vo_vect_sclr);                                   \
    _vo_sclr_vect = vect_128_ ## oper(_a[0], _vb, _vo_sclr_vect);                                   \
    _vo_sclr_sclr = vect_128_ ## oper(_a[0], _b[0], _vo_sclr_sclr);                                 \
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
});

#define _test_vect_128_xor(_memb_type)  _test_vect_128_bin_oper(xor, _memb_type)
#define _test_vect_128_and(_memb_type)  _test_vect_128_bin_oper(and, _memb_type)
#define _test_vect_128_or(_memb_type)   _test_vect_128_bin_oper(or,  _memb_type)
#define _test_vect_128_add(_memb_type)  _test_vect_128_bin_oper(add, _memb_type)
#define _test_vect_128_sub(_memb_type)  _test_vect_128_bin_oper(sub, _memb_type)
#define _test_vect_128_mul(_memb_type)  _test_vect_128_bin_oper(mul, _memb_type)


// test
#define _test_vect_128_opernd_b(oper, _memb_type, oper_b) ({                    \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))}, _res;    \
    vect_128_t(_memb_type) _va, _vo;                                        \
    _va = vect_128_load(_a, _va);                                           \
    _vo = vect_128_ ## oper(_va, oper_b, _vo);                              \
    int index;                                                              \
    for (index = 0; index < vect_memb_cnt(_vo); index++)                    \
        if (scalr_cmp_bits_neq((_res = scalr_oper(oper)(_a[index], oper_b)), vect_memb(_vo, index))) \
            error_with_format(                                              \
                "failed to apply operator vect_128_%s(%s, %s)\n"            \
                "got: (%s %s %s) == (%s) =/= (%s)\n"                        \
                ,#oper, #_memb_type, #oper_b                                \
                ,scalr_str((char [512]){}, _a[index])                       \
                ,macro_apply(token_str, oper_symbl(oper))                   \
                ,scalr_str((char [512]){}, oper_b)                          \
                ,scalr_str((char [512]){}, _res)                            \
                ,scalr_str((char [512]){}, vect_memb(_vo, index))           \
            );                                                              \
})

#define _test_vect_128_lshift_imm(_memb_type)   _test_vect_128_opernd_b(lshift_imm, _memb_type, 5)

#define _test_vect_128_lshift_scalr(_memb_type) ({                  \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(lshift_scalr, _memb_type, temp);        \
})

#define _test_vect_128_lshift(_memb_type) ({                        \
    _test_vect_128_opernd_b(lshift, _memb_type, 4);                 \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(lshift, _memb_type, temp);              \
})

#define _test_vect_128_rshift_logic_imm(_memb_type)     _test_vect_128_opernd_b(rshift_logic_imm, _memb_type, 5)
#define _test_vect_128_rshift_logic_scalr(_memb_type)   ({          \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(rshift_logic_scalr, _memb_type, temp);  \
  })
#define _test_vect_128_rshift_logic(_memb_type)   ({                \
    _test_vect_128_opernd_b(rshift_logic, _memb_type, 4);           \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(rshift_logic, _memb_type, temp);        \
 })

#define _test_vect_128_rshift_arith_imm(_memb_type)     _test_vect_128_opernd_b(rshift_arith_imm, _memb_type, 5)
#define _test_vect_128_rshift_arith_scalr(_memb_type)   ({          \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(rshift_arith_scalr, _memb_type, temp);  \
 })
#define _test_vect_128_rshift_arith(_memb_type) ({                  \
    _test_vect_128_opernd_b(rshift_arith, _memb_type, 4);           \
    int temp = rand() % bit_size(_memb_type);                       \
    _test_vect_128_opernd_b(rshift_arith, _memb_type, temp);        \
})


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
