
#include "test_vect_128_common.h"

#define _vect_128_broad_cast_native(_test_type) ({                      \
    _test_type _e = bits_rand(_test_type);                              \
    typeof(vect_native((vect_128_t(_test_type)){})) na = scalr_switch(  \
        _test_type,                                                     \
        _mm_set1_pd, _mm_set1_ps,                                       \
        _mm_set1_epi64x, _mm_set1_epi32, _mm_set1_epi16, _mm_set1_epi8, \
        _mm_set1_epi64x, _mm_set1_epi32, _mm_set1_epi16, _mm_set1_epi8, \
        (void)0)(_e);                                                   \
    na; })

#define _vect_128_broad_cast_unr_native _vect_128_broad_cast_native
#define _vect_128_broad_cast_bin_native _vect_128_broad_cast_native


#define _vect_128_broad_cast_unr_vect(_test_type) ({    \
    _test_type _e = bits_rand(_test_type);              \
    vect_128_t(_test_type) a = vect_128_broad_cast(_e); \
    vect_native(a);})

#define _vect_128_broad_cast_bin_vect(_test_type) ({    \
    _test_type _e = bits_rand(_test_type);              \
    vect_128_t(_test_type) a;                           \
    vect_128_broad_cast(_e, a);                         \
    vect_native(a);})


#define _test_vect_128_assembly(_test_type, _test_kind)  _vect_128_ ## _test_kind (_test_type)

int main() {

    typeof(vect_native((vect_128_t(_test_type)){})) nv \
            = macro_apply(_test_vect_128_assembly, _test_type, _test_oper);

    if (_mm_comieq_sd((__m128d)nv, _mm_setzero_pd()))
        printf("nothing ...");


    return 0;
}
