
#include "test_vect_128_common.h"


/*** TEST Broadcast assemblies ******************************************************************************/
#define _vect_128_broad_cast_native(_test_type) ({                      \
    int temp;                                                           \
    typeof(vect_native((vect_128_t(_test_type)){})) na = scalr_switch(  \
        _test_type,                                                     \
        _mm_set1_pd, _mm_set1_ps,                                       \
        _mm_set1_epi64x, _mm_set1_epi32, _mm_set1_epi16, _mm_set1_epi8, \
        _mm_set1_epi64x, _mm_set1_epi32, _mm_set1_epi16, _mm_set1_epi8, \
        (void)0)(*(_test_type *)&temp);                                                   \
    na; })

#define _test_vect_128_broad_cast_unr_native _vect_128_broad_cast_native
#define _test_vect_128_broad_cast_bin_native _vect_128_broad_cast_native


#define _test_vect_128_broad_cast_unr_vect(_test_type) ({    \
    int temp;   \
    vect_128_t(_test_type) a = vect_128_broad_cast(*(_test_type *)&temp); \
    vect_native(a); })

#define _test_vect_128_broad_cast_bin_vect(_test_type) ({       \
    int temp;                                                   \
    vect_128_t(_test_type) a;                                   \
    vect_128_broad_cast(*(_test_type *)&temp, a);                  \
    vect_native(a);})


/*** TEST load assemblies .... ******************************************************************************/

#ifdef FAST_COMPILATION
    #define vect_128_store_native(_store_kind, _memb_kind, _dest, _m)  vect_128_## _store_kind ##_scalr(_dest, _m)
    #define vect_128_load_native(_load_kind, _memb_kind, _sr)   vect_128_## _load_kind ## _scalr(_sr)
#else
    #define vect_128_store_native(_store_kind, _memb_type, sr, _m)  scalr_switch(   \
        _test_type,                                                                 \
        vect_128_ ## _store_kind ## _flt64bit((double *)(sr), (__m128d)_va),        \
        vect_128_ ## _store_kind ## _flt32bit((int *)(sr), (__m128)_va),            \
        vect_128_ ## _store_kind ## _intgl((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m),\
        vect_128_ ## _store_kind ## _intgl((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m), vect_128_ ## _store_kind ## _intgl ((__m128i *)(sr), (__m128i)_m),\
        (void)0)

    #define vect_128_load_native(_load_kind, _memb_type, _sr) scalr_switch(     \
        _memb_type,                                                 \
        vect_128_ ## _load_kind ## _flt64bit((double *)(_sr)),      \
        vect_128_ ## _load_kind ## _flt32bit((float *)(_sr)),       \
        vect_128_## _load_kind ##_intgl((__m128i *)(_sr)), vect_128_## _load_kind ##_intgl((__m128i *)(_sr)),vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)(_sr)),    \
        vect_128_## _load_kind ##_intgl((__m128i *)(_sr)), vect_128_## _load_kind ##_intgl((__m128i *)(_sr)),vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)(_sr)),    \
        (void)0)
#endif
#define _test_vect_128_load_native_(_load_kind, _memb_type) ({   \
    int temp;                                               \
    /*static const vect_128_t(_memb_type) _t;*/                 \
    typeof(vect_native((vect_128_t(_memb_type)){})) _na;    \
    _na = (typeof(_na))vect_128_load_native(_load_kind, _memb_type, &temp);                      \
    _na;    })

#define _test_vect_128_load_bin_native(_memb_type) _test_vect_128_load_native_(load, _memb_type)
#define _test_vect_128_load_unr_native(_memb_type) _test_vect_128_load_native_(load, _memb_type)

#define _test_vect_128_load_align_bin_native(_memb_type) _test_vect_128_load_native_(load_align, _memb_type)
#define _test_vect_128_load_align_unr_native(_memb_type) _test_vect_128_load_native_(load_align, _memb_type)


#define _test_vect_128_load_bin_vect_(_load_kind, _memb_type, args) ({ \
    int temp;   \
    /*static const vect_128_t(_memb_type) _t;  */             \
    vect_128_t(_memb_type) _va;         \
    vect_128_ ## _load_kind args;       \
    vect_native(_va);    })

#define _test_vect_128_load_unr_vect_(_load_kind, _memb_type, args) ({  \
    int temp;   \
    vect_128_t(_memb_type) _va = vect_128_ ## _load_kind args;  \
    vect_native(_va);   })

#define _test_vect_128_load_bin_vect(_memb_type) \
    _test_vect_128_load_bin_vect_(load, _memb_type, ((_test_type *)&temp, _va))

#define _test_vect_128_load_align_bin_vect(_memb_type) \
    _test_vect_128_load_bin_vect_(load_align, _memb_type, ((_test_type *)&temp, _va))

#define _test_vect_128_load_unr_vect(_memb_type)        _test_vect_128_load_unr_vect_(load, _memb_type, ((_test_type *)&temp))
#define _test_vect_128_load_align_unr_vect(_memb_type)  _test_vect_128_load_unr_vect_(load_align, _memb_type, ((_test_type *)&temp))


/*** TEST store assemblies *******************************************************/

#define _test_vect_128_store_native_(_store_kind, _test_type) ({        \
    int temp;                                               \
    typeof(vect_native((vect_128_t(_test_type)){})) _va;    \
    _va = (typeof(_va))_mm_set1_epi64x((long long)&temp);   \
    vect_128_store_native(_store_kind, _test_type, &temp, _va);                      \
    _va;    })


#define _test_vect_128_store_native(_test_type)         _test_vect_128_store_native_(store, _test_type)
#define _test_vect_128_store_align_native(_test_type)   _test_vect_128_store_native_(store_align, _test_type)

#define _test_vect_128_store_vect_(_store_kind, _test_type) ({  \
    int temp;                      \
    vect_128_t(_test_type) _va;         \
    vect_128_set_native(_va, (typeof(vect_native(_va)))_mm_set1_epi64x((long long)&temp));    \
    vect_128_ ## _store_kind ((void *)&temp, _va);  \
    vect_native(_va);   })

#define _test_vect_128_store_vect(_test_type)       _test_vect_128_store_vect_(store, _test_type)
#define _test_vect_128_store_align_vect(_test_type) _test_vect_128_store_vect_(store_align, _test_type)

int main() {

    typeof(vect_native((vect_128_t(_test_type)){})) nv
            = _test_vect_128_assembly(_test_type, _test_oper)
    ;

    if (_mm_comieq_sd((__m128d)nv, _mm_setzero_pd()))
        printf("nothing ...");

    return 0;
}
