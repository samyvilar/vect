
#include "test_vect_128_common.h"

int main() { // test broadcast ....
    #define _test_vect_128_broad_cast(_memb_type) ({        \
        vect_128_t(_memb_type) _v;                          \
        _memb_type _r = bits_rand(_memb_type);              \
        _v = vect_128_broad_cast(_r, _v);                   \
        int index;                                          \
        for (index = 0; index < vect_memb_cnt(_v); index++) \
            if (_r != vect_memb(_v, index))                 \
                error_with_format(                          \
                    "failed to broadcast member type %s\n", \
                    # _memb_type                            \
                );                                          \
    });

    run_test_vect_128(broad_cast, _test_vect_128_broad_cast, _test_type);

    return 0;
}

