
#include "test_vect_128_common.h"

int main() {
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



   run_test_vect_128(
        load_bin, _test_vect_128_load, _test_type,
        load, (_single_eval(_r, 0), _v), _temp);

   run_test_vect_128(
        load_bin_assign, _test_vect_128_load, _test_type,
        load, (_single_eval(_r, 1), _v), _v);

   run_test_vect_128(
        load_align_bin, _test_vect_128_load,
        _test_type, load_align, (_single_eval(_r, 2), _v), _temp);

    run_test_vect_128(
    load_align_bin_assign, _test_vect_128_load, _test_type,
        load_align, (_single_eval(_r, 3), _v), _v);

    run_test_vect_128(
        load_unr, _test_vect_128_load, _test_type,
        load, (_single_eval(_r, 4)), _v);

    run_test_vect_128(
        load_unr_vect_128_p, _test_vect_128_load, _test_type,
        load, ((vect_128_t(_r[0]) *)_single_eval(_r, 5)), _v);


    run_test_vect_128(
        load_align_unr, _test_vect_128_load, _test_type,
        load_align, (_single_eval(_r, 6)), _v);

    run_test_vect_128(
        load_align_unr_vect_128_p, _test_vect_128_load, _test_type,
        load_align, ((vect_128_t(_r[0]) *)_single_eval(_r, 7)), _v);

    return 0;
}


