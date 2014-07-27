

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

#include <immintrin.h>

// instrinsics for 256 bit vectors ...
#if defined (__AVX2__)  // AVX2 adds support to all scalar types ...

#undef vect_256_flt64bit_supprt
#undef vect_256_flt32bit_supprt
#define vect_256_flt32bit_supprt 1
#define vect_256_flt64bit_supprt 1

// native vect types ...
#define vect_256_flt32bit_native_t    __m256
#define vect_256_flt64bit_native_t    __m256d
#define vect_256_intgl_native_t       __m256i
#define vect_256_sint64bit_native_t  vect_256_intgl_native_t
#define vect_256_sint32bit_native_t  vect_256_intgl_native_t
#define vect_256_sint16bit_native_t  vect_256_intgl_native_t
#define vect_256_sint8bit_native_t   vect_256_intgl_native_t
#define vect_256_uint64bit_native_t  vect_256_intgl_native_t
#define vect_256_uint32bit_native_t  vect_256_intgl_native_t
#define vect_256_uint16bit_native_t  vect_256_intgl_native_t
#define vect_256_uint8bit_native_t   vect_256_intgl_native_t


vect_typedef(256, flt64bit);
vect_typedef(256, flt32bit);

vect_typedef(256, sint64bit);
vect_typedef(256, sint32bit);
vect_typedef(256, sint16bit);
vect_typedef(256, sint8bit);

vect_typedef(256, uint64bit);
vect_typedef(256, uint32bit);
vect_typedef(256, uint16bit);
vect_typedef(256, uint8bit);


#define _vect_256_t(_memb_name) vect_256_ ## _memb_name ## _t

#undef vect_256_t
#define vect_256_t(_memb_t) typeof(                                             \
    vect_256_sel_t(type_is_flt64bit(_memb_t), _vect_256_t(flt64bit),         \
    vect_256_sel_t(type_is_flt32bit(_memb_t), _vect_256_t(flt32bit),         \
        vect_err_memb_no_suppt(_memb_t)))                                       \
    )


#define vect_256_load             _mm256_lddqu_si256
#define vect_256_load_align       _mm256_load_si256

// broad cast single element ...
#define vect_256_borad_cast_flt64bit    _mm256_set1_pd
#define vect_256_broad_cast_flt32bit    _mm256_set1_ps

#define vect_256_broad_cast_intgl64bit    _mm256_set1_epi64x
#define vect_256_broad_cast_intgl32bit    _mm256_set1_epi16
#define vect_256_broad_cast_intgl16bit    _mm256_set1_epi32
#define vect_256_broad_cast_intgl8bit     _mm256_set1_epi8



#define vect_256_xor_scalr          _mm256_xor_si256
#define vect_256_or_scalr           _mm256_or_si256
#define vect_256_and_scalr          _mm256_and_si256

// add two vectors ..
#define vect_256_add_flt64bit       _mm256_add_pd
#define vect_256_add_flt32bit       _mm256_add_ps
#define vect_256_add_intgl64bit     _mm256_add_epi64
#define vect_256_add_intgl32bit     _mm256_add_epi32
#define vect_256_add_intgl16bit     _mm256_add_epi16
#define vect_256_add_intgl8bit      _mm256_add_epi8

// sub two vectors
#define vect_256_sub_flt64bit       _mm256_sub_pd
#define vect_256_sub_flt32bit       _mm256_sub_ps
#define vect_256_sub_intgl64bit     _mm256_sub_epi64
#define vect_256_sub_intgl32bit     _mm256_sub_epi32
#define vect_256_sub_intgl16bit     _mm256_sub_epi16
#define vect_256_sub_intgl8bit      _mm256_sub_epi8


// mult two vects
#define vect_256_mul_flt64bit  _mm256_mul_pd
#define vect_256_mul_flt32bit  _mm256_mul_ps

#define vect_256_mul_intgl64bit _mm256_mullo_epi64

#define vect_256_mul_intgl32bit _mm256_mullo_epi32
#define vect_256_mul_intgl16bit _mm256_mullo_epi16

#define vect_256_mul_intgl8bit _mm256_mullo_epi8


// div two vects
#define vect_256_div_flt64bit   _mm256_div_pd
#define vect_256_div_flt32bit   _mm256_div_ps

#endif // __AVX2__


#endif // FILE
