
#include "test_vect_128_common.h"


#define _test_vect_128_broad_cast_(_memb_type, _args, d) ({        \
    vect_128_t(_memb_type) _v, __temp;                  \
    _memb_type _r = bits_rand(_memb_type);              \
    d = vect_128_broad_cast _args;                      \
    __temp = d;                                         \
    int index;                                          \
    for (index = 0; index < vect_memb_cnt(_v); index++) \
        if (_r != vect_memb(_v, index))                 \
            error_with_format(                          \
                "failed to broadcast member type %s\n", \
                # _memb_type                            \
            );                                          \
})

#define  _test_vect_128_broad_cast_bin(_memb_type) \
    _test_vect_128_broad_cast_( \
        _memb_type,             \
        (_single_eval(_r, 0), _v), \
        __temp                  \
    )

#define  _test_vect_128_broad_cast_bin_assign(_memb_type) \
    _test_vect_128_broad_cast_(     \
        _memb_type,                 \
        (_single_eval(_r, 1), _v),\
        _v                         \
    )

#define _test_vect_128_broad_cast_unr(_memb_type)       \
    _test_vect_128_broad_cast_(                         \
        _memb_type,                                     \
        (_single_eval(_r, 2)),  \
        _v                                              \
    )



int main() { // test broadcast ....

    run_test_vect_128(broad_cast_bin, _test_vect_128_broad_cast_bin, _test_type);

    run_test_vect_128(broad_cast_bin_assign, _test_vect_128_broad_cast_bin_assign, _test_type);

    run_test_vect_128(broad_cast_unr, _test_vect_128_broad_cast_unr, _test_type);


    return 0;
}

