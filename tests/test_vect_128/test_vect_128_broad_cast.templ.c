
#include "test_vect_128_common.h"


#define _test_vect_128_broad_cast_(_memb_type, _args, d) ({        \
    vect_128_t(_memb_type) _v;                          \
    _memb_type _r = bits_rand(_memb_type);              \
    d = vect_128_broad_cast _args;                      \
    int index;                                          \
    for (index = 0; index < vect_memb_cnt(_v); index++) \
        if (_r != vect_memb(_v, index))                 \
            error_with_format(                          \
                "failed to broadcast member type %s\n", \
                # _memb_type                            \
            );                                          \
})

#define _test_vect_128_broad_cast_unr(_memb_type)   \
    _test_vect_128_broad_cast_(_memb_type, (_single_eval(_r, 0)), _v)



int main() { // test broadcast ....

    run_test_vect_128(broad_cast_unr, _test_vect_128_broad_cast_unr, _test_type);


    return 0;
}

