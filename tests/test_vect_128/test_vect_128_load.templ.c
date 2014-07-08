
#include "test_vect_128_common.h"


#undef  _check_side_effects
#define _check_side_effects(_test_name, _test_type) \
_test_type *_test_side_effects ## _ ## _test_name ## _ ## _test_type (_test_type *_rand_value) {  \
    static int _not_called = 1;         \
    if (_not_called) {                  \
        _not_called = 0;                \
        return _rand_value;             \
    }                                   \
    error_with_format("%s(%s): Error expression evaluted more than once!", #_test_name, #_test_type);      \
}                                                               \


_check_side_effects(load_bin, _test_type)

_check_side_effects(load_bin_assign, _test_type)

_check_side_effects(load_align_bin, _test_type)

_check_side_effects(load_align_bin_assign, _test_type)


_check_side_effects(load_unr, _test_type)

_check_side_effects(load_unr_vect_128_p, _test_type)


_check_side_effects(load_align_unr, _test_type)

_check_side_effects(load_align_unr_vect_128_p, _test_type)




int main() {
    #define _test_vect_128_load(_memb_type, load_kind, args, d) ({      \
        _memb_type __attribute__ ((aligned (64))) _r[] = {macro_comma_delim_16(bits_rand(_memb_type))};\
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
        load, (_check_side_effects_name(load_bin, _test_type)(_r), _v), _temp);

   run_test_vect_128(
        load_bin_assign, _test_vect_128_load, _test_type,
        load, (_check_side_effects_name(load_bin_assign, _test_type)(_r), _v), _v);

   run_test_vect_128(
        load_align_bin, _test_vect_128_load,
        _test_type, load_align, (_check_side_effects_name(load_align_bin, _test_type)(_r), _v), _temp);

    run_test_vect_128(
    load_align_bin_assign, _test_vect_128_load, _test_type,
        load_align, (_check_side_effects_name(load_align_bin_assign, _test_type)(_r), _v), _v);

    run_test_vect_128(
        load_unr, _test_vect_128_load, _test_type,
        load, (_check_side_effects_name(load_unr, _test_type)(_r)), _v);

    run_test_vect_128(
        load_unr_vect_128_p, _test_vect_128_load, _test_type,
        load, ((vect_128_t(_r[0]) *)_check_side_effects_name(load_unr_vect_128_p, _test_type)(_r)), _v);


    run_test_vect_128(
        load_align_unr, _test_vect_128_load, _test_type,
        load_align, (_check_side_effects_name(load_align_unr, _test_type)(_r)), _v);

    run_test_vect_128(
        load_align_unr_vect_128_p, _test_vect_128_load, _test_type,
        load_align, ((vect_128_t(_r[0]) *)_check_side_effects_name(load_align_unr_vect_128_p, _test_type)(_r)), _v);

    return 0;
}


