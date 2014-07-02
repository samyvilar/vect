
#include "test_vect_128_common.h"

int main() {
    #define _test_vect_128_load(_memb_type) ({                          \
        _memb_type _r[] = {macro_comma_delim_16(bits_rand(_memb_type))};\
        vect_128_t(_memb_type) _v;                                      \
        _v = vect_128_load(_r, _v);                                     \
        int index;                                                      \
        for (index = 0; index < vect_memb_cnt(_v); index++) {           \
            if (vect_memb(_v, index) != _r[index])                      \
                error_with_format(                                      \
                    "failed to load member type %s\n", #_memb_type      \
                );                                                      \
            _r[index] = -1;                                             \
        }                                                               \
    });


   run_test_vect_128(load, _test_vect_128_load, _test_type);

    return 0;
}


