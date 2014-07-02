

#include "test_vect_128_common.h"

int main() {
    #define _test_vect_128_store(_memb_type) ({                             \
        _memb_type _src[] = {macro_comma_delim_16(bits_rand(_memb_type))};  \
        _memb_type _dest[16];                                               \
        vect_128_t(_memb_type) _v;                                          \
        _v = vect_128_load((typeof(_v) *)_src, _v);                         \
        _v = vect_128_store((typeof(_v) *)_dest, _v);                       \
        if (memcmp(_src, _dest, 16))                                        \
            error_with_format(                                              \
                "failed to store member type %s\n", #_memb_type             \
            );                                                              \
     });


    run_test_vect_128(store, _test_vect_128_store, _test_type);

    return 0;
}

