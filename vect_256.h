

#ifndef __VECT_256__
#define __VECT_256__

#include "vect_def.h"

#define vect_256_flt32bit_supprt  0
#define vect_256_flt64bit_supprt  0
#define vect_256_sint8bit_supprt  0
#define vect_256_sint16bit_supprt 0
#define vect_256_sint32bit_supprt 0
#define vect_256_sint64bit_supprt 0
#define vect_256_uint8bit_supprt  0
#define vect_256_uint16bit_supprt 0
#define vect_256_uint32bit_supprt 0
#define vect_256_uint64bit_supprt 0

#define vect_256_no_supprt      vect_not_supprtd(256)


#define vect_256_load           vect_256_no_supprt
#define vect_256_load_align     vect_256_no_supprt
#define vect_256_store          vect_256_no_supprt
#define vect_256_store_algin    vect_256_no_supprt

#define vect_256_broad_cast     vect_256_no_supprt
#define vect_256_add            vect_256_no_supprt
#define vect_256_sub            vect_256_no_supprt
#define vect_256_mul            vect_256_no_supprt
#define vect_256_div            vect_256_no_supprt

#define vect_256_lshft          vect_256_no_supprt

#define vect_256_rshft_arith    vect_256_no_supprt
#define vect_256_rshft_logic    vect_256_no_supprt

#define vect_256_extrt          vect_256_no_supprt

#define vect_256_sign_ext       vect_256_no_supprt


#define _vect_256_t             vect_256_no_supprt
#define vect_256_t              vect_256_no_supprt


#define vect_256_flt_intrs(_memb_kind, _memb_bit_size) vect_256_ ## _memb_kind ## _ ## _memb_bit_size ## _intrs_t
#define vect_256_sint_intrs(_memb_kind, _memb_bit_size) vect_256_ ## _memb_kind ## _intrs_t
#define vect_256_uint_intrs vect_128_sint_intrs

#define vect_256_intrs(_memb_kind, _memb_bit_size) vect_128_ ## _memb_kind ## _intrs(_memb_kind, _memb_bit_size)


// instrinsics for 256 bit vectors ...
#if defined (__AVX__)

#undef vect_256_flt64bit_supprt
#undef vect_256_flt32bit_supprt
#define vect_256_flt32bit_supprt 1
#define vect_256_flt64bit_supprt 1

#define vect_256_flt32bit_intrs_t    __m128
#define vect_256_flt64bit_intrs_t    __m128d

vect_typedef(256, flt, 64);
vect_typedef(256, flt, 32);


#define vect_256_sel_t(expr_a, _type_a, expr_b) __builtin_choose_expr(expr_a, (_type_a){}, (expr_b))

#define _vect_256_t(_memb_name) vect_256_ ## _memb_name ## _t

#undef vect_256_t
#define vect_256_t(_memb_t) typeof(                                             \
    vect_256_sel_t(type_is_flt64bit(_memb_t), _vect_256_t(flt64bit),         \
    vect_256_sel_t(type_is_flt32bit(_memb_t), _vect_256_t(flt32bit),         \
        vect_err_memb_no_suppt(_memb_t)))                                       \
    )


#define vector_load             _mm256_lddqu_si256
#define vector_load_align       _mm256_load_si256

// broad cast single element ...
#define vect_256_broad_cast_32_float    _mm256_set1_ps
#define vect_256_borad_cast_64_float    _mm256_set1_pd

#define vect_256_broad_cast_8_s_int     _mm256_set1_epi8
#define vect_256_broad_cast_16_s_int    _mm256_set1_epi16
#define vect_256_broad_cast_32_s_int    _mm256_set1_epi32
#define vect_256_broad_cast_64_s_int    _mm256_set1_epi64x

#define vect_256_broad_cast_8_u_int     vect_256_broad_cast_8_s_int
#define vect_256_broad_cast_16_u_int    vect_256_broad_cast_16_s_int
#define vect_256_broad_cast_32_u_int    vect_256_broad_cast_32_s_int
#define vect_256_broad_cast_64_u_int    vect_256_broad_cast_64_s_int

#define vect_256_broad_cast(_v, _m)



// add two vectors ..
#define vect_256_add_32_float   _mm256_add_ps
#define vect_256_add_64_float   _mm256_add_pd

// sub two vectors
#define vect_256_sub_32_float   _mm256_sub_ps
#define vect_256_sub_64_float   _mm256_sub_pd

// mult two vects
#define vect_256_mult_32_float  _mm256_mul_ps
#define vect_256_mult_64_float  _mm256_mul_pd

// div two vects
#define vect_256_div_32_float   _mm256_div_ps
#define vect_256_div_64_float   _mm256_div_pd

#define vect_256_eq(a, b)     _mm256_testz_si256(vector_xor((a), (b)), _mm256_set1_epi32(-1))

#define vector_or               _mm256_or_pd
#define vector_xor              _mm256_xor_pd
#define vector_and              _mm256_and_pd

#endif


#ifdef __AVX2__
#define vector_xor              _mm256_xor_si256
#define vector_or               _mm256_or_si256
#define vector_and              _mm256_and_si256

#undef vect_256_eq
#define vect_256_eq(a, b)     _mm256_testz_si256(vector_xor((a), (b)), _mm256_set1_epi32(-1))
#endif

#endif
