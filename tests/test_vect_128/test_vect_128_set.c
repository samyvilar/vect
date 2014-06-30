

#include "test_vect_128_common.h"

int main() { // test vect_128 member initialization ...

    #define _test_vect_set(_memb_type)  ({                                      \
        vect_128_t(_memb_type) _v;                                              \
        _memb_type ms[] = {macro_comma_delim_16(bits_rand(_memb_type))};        \
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

    print_ok();

    return 0;
}



