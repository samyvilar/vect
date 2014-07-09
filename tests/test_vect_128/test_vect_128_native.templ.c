
#include "test_vect_128_common.h"


/*** TEST Broadcast assemblies ******************************************************************************/
#define _vect_128_broad_cast_native(_test_type) ({                      \
    int temp = 10;       \
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
    int temp = 10;   \
    vect_128_t(_test_type) a = vect_128_broad_cast(*(_test_type *)&temp); \
    vect_native(a);})

#define _test_vect_128_broad_cast_bin_vect(_test_type) ({       \
    int temp = 10;                                                   \
    vect_128_t(_test_type) a;                                   \
    vect_128_broad_cast(*(_test_type *)&temp, a);                  \
    vect_native(a);})


/*** TEST load assemblies .... ******************************************************************************/

#define _test_vect_128_load_native_(_load_kind, _memb_type) ({   \
    int temp;\
    typeof(vect_native((vect_128_t(_memb_type)){})) _na;    \
    _na = scalr_switch(                                     \
        _memb_type,                                         \
        vect_128_ ## _load_kind ## _flt64bit((double *)&temp),         \
        vect_128_ ## _load_kind ## _flt32bit((float *)&temp),         \
        vect_128_## _load_kind ##_intgl((__m128i *)&temp), vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)&temp),    \
        vect_128_## _load_kind ##_intgl((__m128i *)&temp), vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)&temp),vect_128_## _load_kind ##_intgl((__m128i *)&temp),    \
        (void)0                                 \
    );                                      \
    _na;    })

#define _test_vect_128_load_bin_native(_memb_type) _test_vect_128_load_native_(load, _memb_type)
#define _test_vect_128_load_unr_native(_memb_type) _test_vect_128_load_native_(load, _memb_type)

#define _test_vect_128_load_align_bin_native(_memb_type) _test_vect_128_load_native_(load_align, _memb_type)
#define _test_vect_128_load_align_unr_native(_memb_type) _test_vect_128_load_native_(load_align, _memb_type)


#define _test_vect_128_load_bin_vect_(_load_kind, _memb_type, args) ({ \
    int temp;   \
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
    int temp = 10;                                                      \
    typeof(vect_native((vect_128_t(_test_type)){})) _va;                \
    _va = (typeof(_va))_mm_set1_epi64x((long long)&temp);                          \
    scalr_switch(\
        _test_type,                              \
        vect_128_ ## _store_kind ## _flt64bit((double *)&temp, (__m128d)_va),           \
        vect_128_ ## _store_kind ## _flt32bit((int *)&temp, (__m128)_va),           \
        vect_128_ ## _store_kind ## _intgl((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va),\
        vect_128_ ## _store_kind ## _intgl((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va), vect_128_ ## _store_kind ## _intgl ((__m128i *)&temp, (__m128i)_va),\
        (void)0 \
    );  _va;    })


#define _test_vect_128_store_native(_test_type)         _test_vect_128_store_native_(store, _test_type)
#define _test_vect_128_store_align_native(_test_type)   _test_vect_128_store_native_(store_align, _test_type)

#define _test_vect_128_store_vect_(_store_kind, _test_type) ({  \
    int temp = 10;                      \
    vect_128_t(_test_type) _va;         \
    vect_128_set_native(_va, (typeof(vect_native(_va)))_mm_set1_epi64x((long long)&temp));    \
    vect_128_ ## _store_kind ((void *)&temp, _va);  \
    vect_native(_va);   })

#define _test_vect_128_store_vect(_test_type)       _test_vect_128_store_vect_(store, _test_type)
#define _test_vect_128_store_align_vect(_test_type) _test_vect_128_store_vect_(store_align, _test_type)

int main() {

    typeof(vect_native((vect_128_t(_test_type)){})) nv
            = macro_apply(_test_vect_128_assembly, _test_type, _test_oper)
    ;

    if (_mm_comieq_sd((__m128d)nv, _mm_setzero_pd()))
        printf("nothing ...");

    return 0;
}
