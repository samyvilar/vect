#ifndef TEST_VECT_128_UNR_OPER_H
#define TEST_VECT_128_UNR_OPER_H

#include "test_vect_128_common.h"


#define _test_vect_128_unr_oper(oper_name, _memb_type, args) ({                       \
    _memb_type _a[16] = {macro_comma_delim_16(bits_rand(_memb_type))}, _res;    \
    vect_128_t(_memb_type) _vo, _va;                        \
    _va = vect_128_load(_a, _va);                           \
    _vo = vect_128_ ## oper_name args;                 \
    int index;                                              \
    for (index = 0; index < vect_memb_cnt(_va); index++)    \
        if (scalr_cmp_bits_neq((_res = scalr_oper(oper_name)(_a[index])), vect_memb(_vo, index)))   \
            error_with_format(                                                  \
                "failed to apply unary operator vector_128_%s on type: %s\n"    \
                ,#oper_name, #_memb_type                                        \
            );                                                                  \
    })

#define _test_vect_128_sign_ext_unr(_memb_type) \
    _test_vect_128_unr_oper(sign_ext, _memb_type, (_single_eval(_va, 0)))
#define _test_vect_128_sign_ext_bin(_memb_type) \
    _test_vect_128_unr_oper(sign_ext, _memb_type, (_single_eval(_va, 0), _vo))

#endif // TEST_VECT_128_UNR_OPER_H
