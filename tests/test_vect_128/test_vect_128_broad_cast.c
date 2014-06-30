
#include "test_vect_128_common.h"

int main() { // test broadcast ....
    #define _test_vect_128_broad_cast(_memb_type) ({        \
        vect_128_t(_memb_type) _v;                          \
        _memb_type _r = bits_rand(_memb_type);              \
        _v = vect_128_broad_cast(_v, _r);                   \
        int index;                                          \
        for (index = 0; index < vect_memb_cnt(_v); index++) \
            if (_r != vect_memb(_v, index))                 \
                error_with_format(                          \
                    "failed to broadcast member type %s\n", \
                    # _memb_type                            \
                );                                          \
    });
    printf("test_vect_128_broad_cast: ");
    #ifdef enable_test
        MAP_2(_test_vect_128_broad_cast, test_memb_types);
    #endif
    print_ok();

    return 0;
}

