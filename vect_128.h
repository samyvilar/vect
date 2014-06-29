

#ifndef __VECT_128__
#define __VECT_128__

#include "macro_utils.h"
#include "vect_def.h"

#include "scalr_types.h"
#include "comp_utils.h"

#include <emmintrin.h>

/*  DEFAULTs vect_128, if theres is no SSE support ********************************************************************/
#define vect_128_flt32bit_supprt  0
#define vect_128_flt64bit_supprt  0
#define vect_128_sint8bit_supprt  0
#define vect_128_sint16bit_supprt 0
#define vect_128_sint32bit_supprt 0
#define vect_128_sint64bit_supprt 0
#define vect_128_uint8bit_supprt  0
#define vect_128_uint16bit_supprt 0
#define vect_128_uint32bit_supprt 0
#define vect_128_uint64bit_supprt 0


#define vect_128_no_supprt      vect_not_supprtd(128)

#define _vect_128_t             vect_128_no_supprt
#define vect_128_t              vect_128_no_supprt


#define vect_128_load           vect_128_no_supprt
#define vect_128_load_align     vect_128_no_supprt
#define vect_128_store          vect_128_no_supprt
#define vect_128_store_algin    vect_128_no_supprt

#define vect_128_broad_cast     vect_128_no_supprt

#define vect_128_xor            vect_128_no_supprt
#define vect_128_or             vect_128_no_supprt
#define vect_128_and            vect_128_no_supprt

#define vect_128_add            vect_128_no_supprt
#define vect_128_sub            vect_128_no_supprt
#define vect_128_mul            vect_128_no_supprt
#define vect_128_div            vect_128_no_supprt

#define vect_128_lshft          vect_128_no_supprt

#define vect_128_rshft_arith    vect_128_no_supprt
#define vect_128_rshft_logic    vect_128_no_supprt

#define vect_128_extrt          vect_128_no_supprt

#define vect_128_sign_ext       vect_128_no_supprt
/********************************************************************************************************************/



#if defined (__SSE2__)


#undef vect_128_flt32bit_supprt
#undef vect_128_flt64bit_supprt
#undef vect_128_sint8bit_supprt
#undef vect_128_sint16bit_supprt
#undef vect_128_sint32bit_supprt
#undef vect_128_sint64bit_supprt
#undef vect_128_uint8bit_supprt
#undef vect_128_uint16bit_supprt
#undef vect_128_uint32bit_supprt
#undef vect_128_uint64bit_supprt
// SSE2 adds support to all 10 scalar types, being over a decade old it should be very common on x86 machines.
#define vect_128_flt32bit_supprt  1
#define vect_128_flt64bit_supprt  1
#define vect_128_sint8bit_supprt  1
#define vect_128_sint16bit_supprt 1
#define vect_128_sint32bit_supprt 1
#define vect_128_sint64bit_supprt 1
#define vect_128_uint8bit_supprt  1
#define vect_128_uint16bit_supprt 1
#define vect_128_uint32bit_supprt 1
#define vect_128_uint64bit_supprt 1


// native vect types ...
#define vect_128_flt32bit_native_t    __m128
#define vect_128_flt64bit_native_t    __m128d
#define vect_128_intgl_native_t       __m128i
#define vect_128_sint64bit_native_t  vect_128_intgl_native_t
#define vect_128_sint32bit_native_t  vect_128_intgl_native_t
#define vect_128_sint16bit_native_t  vect_128_intgl_native_t
#define vect_128_sint8bit_native_t   vect_128_intgl_native_t
#define vect_128_uint64bit_native_t  vect_128_intgl_native_t
#define vect_128_uint32bit_native_t  vect_128_intgl_native_t
#define vect_128_uint16bit_native_t  vect_128_intgl_native_t
#define vect_128_uint8bit_native_t   vect_128_intgl_native_t


#define vect_128_typedef(_memb_name)    vect_typedef(128, _memb_name);
/*      ^^^^^^^^^^^^^^^^ typedef a new internal vect_128 type containing packed (flt64bit, flt32bit, sint64bit ...)*/

MAP(vect_128_typedef, scalrs_names)
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * declare varying internal vect_128_t types to keep track of packed member types
 * in order to determine which intrinsic to apply (@ compile time) ...
 */

#undef _vect_128_t
#define _vect_128_t(_memb_name) vect_128_ ## _memb_name ## _t
#define vect_128_sel_t(expr_a, _type_a, expr_b) comp_select(expr_a, (_type_a){}, (expr_b))

#undef vect_128_t
#define vect_128_default_t vect_err_memb_no_suppt
#define _vect_128_expr(_memb_name) ((vect_t_name(128, _memb_name)){})

#define vect_128_t(args...) typeof(                      \
/*      ^^^^^^^^^^ returns an internal vect_128_t type representing
 *                   packed typeof(arg_0) if there is no support than
 *                   either return typeof(arg_1) if giving
 *                   or emit compilation error
 */                                                      \
    macro_apply(                                         \
        scalr_switch,                                    \
        macro_arg_0(args),                               \
        MAP_LIST(_vect_128_expr, scalrs_names),          \
        (macro_arg_1(args, void))0                       \
      )                                                  \
    )

#define vect_128_intrs_name(_kind, _memb_name) vect_128_ ## _kind ## _ ##  _memb_name
//      ^^^^^^^^^^^^^^^^^^^ returns the intrinsic macro name for vect_128 holding packed
//                          _memb_name(flt64bit, flt32bit, uint64bit ....)



/***** STORE 128 bit vectors *******************************************************************************************/
// store on aligned addrs
#define vect_128_store_align_flt32bit(_p, _nv) 	_mm_store_ps((float *)(_p), _nv)
#define vect_128_store_align_flt64bit(_p, _nv)	_mm_store_pd((double *)(_p), _nv)
#define vect_128_store_align_intgl(_p, _nv) 		_mm_store_si128((__m128i *)(_p), _nv)
#define vect_128_store_align_sint64             vect_128_store_align_intgl
#define vect_128_store_align_sint32             vect_128_store_align_intgl
#define vect_128_store_align_sint16             vect_128_store_align_intgl
#define vect_128_store_align_sint8              vect_128_store_align_intgl
#define vect_128_store_align_uint64             vect_128_store_align_intgl
#define vect_128_store_align_uint32             vect_128_store_align_intgl
#define vect_128_store_align_uint16             vect_128_store_align_intgl
#define vect_128_store_align_uint8              vect_128_store_align_intgl
#define _vect_128_store_align_(_memb_kind) vect_128_store_align_ ## _memb_kind  macro_cons_parens


// store on any addrs, (safer but slower than aligned)
#define vect_128_store_flt32bit(_p, _nv)			_mm_storeu_ps((float *)(_p), _nv)
#define vect_128_store_flt64bit(_p, _nv)			_mm_storeu_pd((double *)(_p), _nv)
#define vect_128_store_intgl(_p, _nv)			_mm_storeu_si128((__m128i *)(_p), _nv)
#define vect_128_store_sint64bit                vect_128_store_intgl
#define vect_128_store_sint32bit                vect_128_store_intgl
#define vect_128_store_sint16bit                vect_128_store_intgl
#define vect_128_store_sint8bit                 vect_128_store_intgl
#define vect_128_store_uint64bit                vect_128_store_intgl
#define vect_128_store_uint32bit                vect_128_store_intgl
#define vect_128_store_uint16bit                vect_128_store_intgl
#define vect_128_store_uint8bit                 vect_128_store_intgl
#define _vect_128_store_(_memb_kind) vect_128_store_ ## _memb_kind  macro_cons_parens


#define vect_128_store_(_kind, _p, _v) (            \
    macro_apply(                                    \
        scalr_switch,                               \
        vect_memb_t(_v),                            \
        MAP_LIST_APPLY_ARG(                         \
            _vect_128_ ## _kind ## _,               \
            macro_pack_args(_p, vect_native(_v)),   \
            scalrs_names                            \
        ),                                          \
        (void)0                                     \
    ), _v                                           \
)

#undef  vect_128_store_align
#define vect_128_store_align(_p, _v) vect_128_store_(store_align, _p, _v)

#undef  vect_128_store
#define vect_128_store(_p, _v) vect_128_store_(store, _p, _v)
                    
/***** LOAD 128 bit vectors *******************************************************************************************/
// LOAD 128 bit vector on aligned addresses
#define vect_128_load_align_flt32bit(_p)    _mm_load_ps((float const *)(_p))
#define vect_128_load_align_flt64bit(_p)    _mm_load_pd((double const *)(_p))
#define vect_128_load_align_intgl(_p)       _mm_load_si128((__m128i const *)(_p))
#define vect_128_load_align_sint64bit       vect_128_load_align_intgl
#define vect_128_load_align_sint32bit       vect_128_load_align_intgl
#define vect_128_load_align_sint16bit       vect_128_load_align_intgl
#define vect_128_load_align_sint8bit        vect_128_load_align_intgl
#define vect_128_load_align_usint64bit      vect_128_load_align_intgl
#define vect_128_load_align_usint32bit      vect_128_load_align_intgl
#define vect_128_load_align_usint16bit      vect_128_load_align_intgl
#define vect_128_load_align_usint8bit       vect_128_load_align_intgl
#define _vect_128_load_align_(_memb_kind)   vect_128_load_align_ ## _memb_kind

                    
// LOAD 128 bit vector on any addresses
#define vect_128_load_flt32bit(_p)     _mm_loadu_ps((float const *)(_p))
#define vect_128_load_flt64bit(_p)     _mm_loadu_pd((double const *)(_p))
#define vect_128_load_intgl(_p)        _mm_loadu_si128((__m128i const *)(_p))
#define vect_128_load_sint64bit         vect_128_load_intgl
#define vect_128_load_sint32bit         vect_128_load_intgl
#define vect_128_load_sint16bit         vect_128_load_intgl
#define vect_128_load_sint8bit          vect_128_load_intgl
#define vect_128_load_uint64bit         vect_128_load_intgl
#define vect_128_load_uint32bit         vect_128_load_intgl
#define vect_128_load_uint16bit         vect_128_load_intgl
#define vect_128_load_uint8bit          vect_128_load_intgl
#define _vect_128_load_(_memb_kind)   vect_128_load_ ## _memb_kind

#define _vect_128_load_(_memb_kind) vect_128_load_ ## _memb_kind

#define vect_128_load_(_kind, _p, _v) ({                                    \
    vect_set_native(                                                        \
        _v,                                                                 \
        macro_apply(                                                        \
            scalr_switch,                                                   \
            vect_memb_t(_v),                                                \
            MAP_LIST_APPLY_ARG(_vect_128_ ## _kind ## _, _p, scalrs_names),  \
            (void)0                                                         \
        )); _v; })

#undef  vect_128_load_align                    
#define vect_128_load_align(_p, _v)  vect_128_load_(load_align, _p, _v)

#undef vect_128_load
#define vect_128_load(_p, _v)        vect_128_load_(load, _p, _v)



#define _select_2(arg_0, arg_1, ...) arg_0, arg_1
#define _select_4(arg_0, arg_1, ...) arg_0, arg_1, _select_2(__VA_ARGS__)
#define _select_8(arg_0, arg_1, arg_2, arg_3, ...) arg_0, arg_1, arg_2, arg_3, _select_4(__VA_ARGS__)
#define _select_16(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, ...)\
    arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, _select_8(__VA_ARGS__)

#define _select(cnt, ...) _select_ ## cnt (__VA_ARGS__)

#define vect_128_set_flt64bit(...)   _mm_set_pd     (_select(2, __VA_ARGS__))
#define vect_128_set_flt32bit(...)   _mm_set_ps     (_select(4, __VA_ARGS__))
#define vect_128_set_sint64bit(...)  _mm_set_epi64x (_select(2, __VA_ARGS__))
#define vect_128_set_sint32bit(...)  _mm_set_epi32  (_select(4, __VA_ARGS__))
#define vect_128_set_sint16bit(...)  _mm_set_epi16  (_select(8, __VA_ARGS__))
#define vect_128_set_sint8bit(...)   _mm_set_epi8   (_select(16, __VA_ARGS__))
#define vect_128_set_uint64bit  vect_128_set_sint64bit
#define vect_128_set_uint32bit  vect_128_set_sint32bit
#define vect_128_set_uint16bit  vect_128_set_sint16bit
#define vect_128_set_uint8bit   vect_128_set_sint8bit

#define vect_128_set_(_memb_name) vect_128_set_ ## _memb_name macro_cons_parens

#define vect_128_set(_v, exprs...) (                            \
/*      ^^^^^^^^^^^^ set the components of an internal vect _v(vect_128_*_t
 *               where exprs is a comma seperated list of exprs starting from the most
 *               most significant to least */                   \
    vect_set_native(                                            \
        _v,                                                     \
        macro_apply(                                            \
            scalr_switch,                                       \
            vect_memb_t(_v),                                    \
            MAP_LIST_APPLY_ARG(                                 \
                vect_128_set_,                                  \
                macro_pack_args(exprs, macro_comma_delim_16(0)),\
                scalrs_names                                    \
            ),                                                  \
            ((void)0)                                           \
        )                                                       \
    ), _v)

                                                                                                                                                                                                                                                                                                        
/**  UNARY vector operators  *****************************************************************************/

// broadcast expr into a vector type duplicating as many times as required ...
#define vect_128_broad_cast_flt64bit    _mm_set1_pd
#define vect_128_broad_cast_flt32bit    _mm_set1_ps
#define vect_128_broad_cast_sint8bit    _mm_set1_epi8
#define vect_128_broad_cast_sint16bit   _mm_set1_epi16
#define vect_128_broad_cast_sint32bit   _mm_set1_epi32
#define vect_128_broad_cast_sint64bit   _mm_set1_epi64x
#define vect_128_broad_cast_uint8bit    vect_128_broad_cast_sint8bit
#define vect_128_broad_cast_uint16bit   vect_128_broad_cast_sint16bit
#define vect_128_broad_cast_uint32bit   vect_128_broad_cast_sint32bit
#define vect_128_broad_cast_uint64bit   vect_128_broad_cast_sint64bit



#define vect_128_broad_cast_(_memb_name) vect_128_broad_cast_ ## _memb_name

#define vect_128_map_intrs(expr)

#undef vect_128_broad_cast
#define vect_128_broad_cast(_v, expr) (                                                            \
    vect_set_native(                                                                               \
        _v,                                                                                        \
        macro_apply(                                                                               \
            scalr_switch,                                                                          \
            expr,                                                                                  \
            MAP_LIST_APPLY_ARG(vect_128_broad_cast_, expr, scalrs_names),                          \
            ((void)0)             \
        )), _v)


/** BINARY operators *****************************************************************************/
// if either operand is a scalar of the same type as the others vectors member type it will be broadcasted
// otherwise a compilation error is emitted ...

// Binary Bit intrinsics, either both operands are the same vect_native types (bit_size, memb_type)
//  OR: one of them is scalar type of the same type as the vectors members type memb_type
//  in which case the scalar will be broadcasted before the intrinsic is applied,
// @@>> IN neither case a compilation ERROR is emitted!
//
//  if operands are OK intrisic is applied creating a new vect_t of the same kind as the operands
//      and returned ....
#define vect_128_xor_flt32bit           _mm_xor_ps
#define vect_128_xor_flt64bit           _mm_xor_pd
#define vect_128_xor_intgl              _mm_xor_si128
#define vect_128_xor_sint64bit          vect_128_xor_intgl
#define vect_128_xor_sint32bit          vect_128_xor_intgl
#define vect_128_xor_sint16bit          vect_128_xor_intgl
#define vect_128_xor_sint8bit           vect_128_xor_intgl
#define vect_128_xor_uint64bit          vect_128_xor_intgl
#define vect_128_xor_uint32bit          vect_128_xor_intgl
#define vect_128_xor_uint16bit          vect_128_xor_intgl
#define vect_128_xor_uint8bit           vect_128_xor_intgl
#define _vect_128_xor_(_memb_kind)       vect_128_xor_ ## _memb_kind macro_cons_parens


#define vect_128_or_flt32bit            _mm_or_ps
#define vect_128_or_flt64bit            _mm_or_pd
#define vect_128_or_intgl               _mm_or_si128
#define vect_128_or_sint64bit           vect_128_or_intgl
#define vect_128_or_sint32bit           vect_128_or_intgl
#define vect_128_or_sint16bit           vect_128_or_intgl
#define vect_128_or_sint8bit            vect_128_or_intgl
#define vect_128_or_uint64bit           vect_128_or_intgl
#define vect_128_or_uint32bit           vect_128_or_intgl
#define vect_128_or_uint16bit           vect_128_or_intgl
#define vect_128_or_uint8bit            vect_128_or_intgl
#define _vect_128_or_(_memb_kind)        vect_128_or_ ## _memb_kind macro_cons_parens


#define vect_128_and_flt32bit           _mm_and_ps
#define vect_128_and_flt64bit           _mm_and_pd
#define vect_128_and_intgl              _mm_and_si128
#define vect_128_and_sint64bit          vect_128_and_intgl
#define vect_128_and_sint32bit          vect_128_and_intgl
#define vect_128_and_sint16bit          vect_128_and_intgl
#define vect_128_and_sint8bit           vect_128_and_intgl
#define vect_128_and_uint64bit          vect_128_and_intgl
#define vect_128_and_uint32bit          vect_128_and_intgl
#define vect_128_and_uint16bit          vect_128_and_intgl
#define vect_128_and_uint8bit           vect_128_and_intgl
#define _vect_128_and_(_memb_kind)       vect_128_and_ ## _memb_kind macro_cons_parens

#define vect_128_broad_cast_if_scalr(_opern, _vect_type)  (_opern)
//({         \
//    typeof(_vect_type) _broad_casted_vect;                          \
//    comp_select(                                                    \
//        expr_is_scalr(_opern),                                      \
//        vect_128_broad_cast(_broad_casted_vect, _opern),            \
//        _opern                                                      \
//   ); })

#define vect_128_bitwise_bin_oper(oper, oper_a, oper_b, dest) (         \
    vect_set_native(                                                    \
        dest,                                                           \
        macro_apply(                                                    \
            scalr_switch,                                               \
            vect_memb_t(dest),                                          \
            MAP_LIST_APPLY_ARG(                                         \
                _vect_128_ ## oper ## _,                                \
                macro_pack_args(                                        \
                    vect_native(vect_128_broad_cast_if_scalr(oper_a, dest)),  \
                    vect_native(vect_128_broad_cast_if_scalr(oper_b, dest))  \
                ),                                                      \
                scalrs_names                                            \
            ),                                                          \
            (void)0                                                     \
         )                                                              \
   ), dest)


#undef vect_128_and
#define vect_128_and(a, b, out)  vect_128_bitwise_bin_oper(and, a, b, out)
#undef vect_128_or
#define vect_128_or(a, b, out)   vect_128_bitwise_bin_oper(or, a, b, out)
#undef vect_128_xor
#define vect_128_xor(a, b, out)  vect_128_bitwise_bin_oper(xor, a, b, out)



// add two 128 bit vectors
#define vect_128_add_flt64bit           _mm_add_pd
#define vect_128_add_flt32bit           _mm_add_ps
#define vect_128_add_sint8bit           _mm_add_epi8
#define vect_128_add_sint16bit          _mm_add_epi16
#define vect_128_add_sint32bit          _mm_add_epi32
#define vect_128_add_sint64bit          _mm_add_epi64
#define vect_128_add_uint8bit           vect_128_add_sint8bit
#define vect_128_add_uint16bit          vect_128_add_sint16bit
#define vect_128_add_uint32bit          vect_128_add_sint32bit
#define vect_128_add_uint64bit          vect_128_add_sint64bit


// sub two vectors
#define vect_128_sub_flt64bit           _mm_sub_pd
#define vect_128_sub_flt32bit           _mm_sub_ps
#define vect_128_sub_sint8bit           _mm_sub_epi8
#define vect_128_sub_sint16bit          _mm_sub_epi16
#define vect_128_sub_sint32bit          _mm_sub_epi32
#define vect_128_sub_sint64bit          _mm_sub_epi64
#define vect_128_sub_uint8bit           vect_128_sub_sint8bit
#define vect_128_sub_uint16bit          vect_128_sub_sint16bit
#define vect_128_sub_uint32bit          vect_128_sub_sint32bit
#define vect_128_sub_uint64bit          vect_128_sub_sint64bit



// mul two vectors
#define vect_128_mul_flt64bit       _mm_mul_pd
#define vect_128_mul_flt32bit       _mm_mul_ps

// multiplies the the low and high 32 bits each creating a 64 bit unsigned result ...
#define vect_128_mul_sint32bit(a, b) ({                                         \
        vector_t _a_ = (a), _b_ = (b);                                          \
        _mm_unpacklo_epi32(                                                     \
            _mm_shuffle_epi32(_mm_mul_epu32(_a_, _b_), _MM_SHUFFLE (0,0,2,0)),  \
            _mm_shuffle_epi32(                                                  \
                _mm_mul_epu32(_mm_srli_si128(_a_, 4), _mm_srli_si128(_b_, 4)),  \
                _MM_SHUFFLE(0,0,2,0)                                            \
            )                                                                   \
        );  })
#define vect_128_mul_uint32bit vect_128_mul_sint32bit


#define vect_128_mul_sint16bit      _mm_mullo_epi16
#define vect_128_mul_uint16bit      vect_128_mul_sint16bit



/*
    SSE doesn't support 64 bit multiplication, but it can be emulated assuming a & b vectors with 64 bit numbers
     assume a, b are 64 bit numbers and high/low return the corresponding 32 bits
     then a * b
        == (low(a) + high(a)) * (low(b) + high(b))
        == low(a)*low(b) + low(a)*high(b) + high(a)*low(b) + high(a)*high(b)
        == low(a)*low(b) + high(a)*high(b) + (high(a)*low(b) + high(a)*low(b))
        a * high(x) == a * ((x / 2**32) * 2**32) == (a * (x >> 32)) << 32

        vector_t high_a = _mm_shuffle_epi32(a, _MM_SHUFFLE(2, 3, 0, 1)), high_b = _mm_shuffle_epi32(a, _MM_SHUFFLE(2, 3, 0, 1));
        _mm_mul_epi32(a, b) multiplies the low parts of each 64 bit number.
        + _mm_mul_epi32(high_a, high_b) multiply high parts
        + _mm_mul_epi32(a,  high_b)
        + _mm_mul_epi32(high_a,  b)   // reqs 2 shuffles, 4 mults, 3 adds (9 instrs)
 */

#define vect_128_mul_sint64bit(a, b)  ({                                                 \
        typeof(a)                                                                            \
            _a = (a),                                                                       \
            _b = (b),                                                                       \
            high_a = _mm_shuffle_epi32(_a, _MM_SHUFFLE(2, 3, 0, 1)),                        \
            high_b = _mm_shuffle_epi32(_b, _MM_SHUFFLE(2, 3, 0, 1));                        \
        vect_128_add_sint64bit(                                                              \
            vect_128_add_sint64bit(_mm_mul_epu32(_a, _b),  _mm_mul_epu32(high_a, high_b)),   \
            vect_128_add_sint64bit(_mm_mul_epu32(_a,  high_b), _mm_mul_epu32(high_a,  _b))   \
        ); )}

#define vect_128_mul_uint64bit vect_128_mul_sint64bit


// div two vectors
#define vect_128_div_flt64div   _mm_div_pd
#define vect_128_div_flt32div   _mm_div_ps


// etract member from vectors ...
#define vect_128_extrt_flt64bit(a, _imm) ({                             \
    double _m;                                                          \
    switch (_imm) {                                                     \
        case 0: _m = _mm_cvtsd_f64(a, 0); break ;                       \
        case 1: _m = _mm_cvtsd_f64(_mm_srli_si128(a, 8), 0); break ;    \
        default: assert_with_msg(0, "expected either 0, 1");            \
    }                                                                   \
    _m; })

#define vect_128_extr_flt32bit(a, _imm) ({                                 \
    float _hd;                                                             \
    switch (_imm) {                                                        \
        case 0: _hd = _mm_cvtss_f32(a, _imm); break ;                      \
        case 1: _hd = _mm_cvtss_f32(_mm_srli_si128(a, 4)); break ;         \
        case 2: _hd = _mm_cvtss_f32(_mm_srli_si128(a, 8)); break ;         \
        case 3: _hd = _mm_cvtss_f32(_mm_srli_si128(a, 12)); break ;        \
        default: assert_with_msg(0, "expecting either 0, 1, 2, 3");        \
        }                                                                  \
    _hd; })


#define vect_128_extrt_sint8bit(a, _im) rshift_logcl(_mm_extract_epi16(a, _im >> 1), 8 * (_im & 1))
#define vect_128_extrt_uint8bit(a, _im) ((uint_bit_t(8))vect_128_extrt_8_s_int(a, _im))

#define vect_128_extrt_sint16bit _mm_extract_epi16
#define vect_128_extrt_uint16bit(a, _im) ((uint_bit_t(16))vect_128_extrt_16_s_int(a, _im))

#define vect_128_extrt_sint32bit(_a, _imm) ({                       \
    s _m;                                                               \
    switch (_imm) {                                                     \
        case 0: _m = _mm_cvtsi128_si32(_a); break ;                     \
        case 1: _m = _mm_cvtsi128_si32(_mm_srli_si128(_a, 4)); break ;  \
        case 2: _m = _mm_cvtsi128_si32(_mm_srli_si128(_a, 8)); break ;  \
        case 3: _m = _mm_cvtsi128_si32(_mm_srli_si128(_a, 12)); break ; \
        default: assert_with_msg(0, "expected either 0, 1, 2, 3");      \
    }                                                                   \
_m; })

#define vect_128_extrt_uint32bit(a, _imm) (uint_bit_t(32))(vect_128_extrt_32_s_int(a, _imm))

#define vect_128_extrt_64_s_int(a, _im) ({                                    \
        sint_bit_t(64) _m;                                                        \
        switch (_im) {                                                            \
            case 0: _m = _mm_cvtsi128_si64(a); break ;                            \
            case 1: _m = _mm_cvtsi128_si64(_mm_srli_si128(a, 8));  break ;        \
            default: assert_with_msg(0, "expected either 0 or 1");                \
        } _m; })
#define vect_128_extrt_64_uint(a, _im) ((uint_bit_t(64))vect_128_extrt_64_s_int(a, _im))

// sse2 can only extract the lower 32 bits so we need to either shuffle or shift ...


    #define _mm_mullo_epi32(a, b) ({                                            \
        vector_t _a_ = (a), _b_ = (b);                                          \
        _mm_unpacklo_epi32(                                                     \
            _mm_shuffle_epi32(_mm_mul_epu32(_a_, _b_), _MM_SHUFFLE (0,0,2,0)),  \
            _mm_shuffle_epi32(_mm_mul_epu32(_mm_srli_si128(_a_, 4), _mm_srli_si128(_b_, 4)), _MM_SHUFFLE (0,0,2,0))); })

// sse2 can only extract the lower 64 bit number for the upper we need to either shuffer or shift



#define vector_mul_i(a, b, i) ({\
        vector_t _r; \
        switch (sizeof(i)) {\
            case 2: _r = _mm_mullo_epi16(a, b); break ;\
            case 4: _r = _mm_mullo_epi32(a, b); break ; \
            case 8: {\
                vector_t _a = (a), _b = (b), \
                high_a = _mm_shuffle_epi32(_a, _MM_SHUFFLE(2, 3, 0, 1)), \
                high_b = _mm_shuffle_epi32(_b, _MM_SHUFFLE(2, 3, 0, 1)); \
                _r = vector_add_i(\
                    vector_add_i(_mm_mul_epu32(_a, _b),  _mm_mul_epu32(high_a, high_b), i), \
                    vector_add_i(_mm_mul_epu32(_a,  high_b), _mm_mul_epu32(high_a,  _b), i),\
                    i);}} _r;})

#define vect_128_shft_left_imm_8_s_int(a, i) vect_128_and(vect_128_broad_cast_8_s_int(0xFF << (i))
// SSE doesn't support byte shifts so just do word shifts since it will shift bytes anyway and with byte incase their all zero out, since words won't be ...

#define vect_128_lshft_imm_flt32bit(a, _imm) _mm_castsi128_ps(vect_128_lshft_imm_sint32bit(_mm_castps_si128(a), _imm))
#define vect_128_lshft_imm_flt64bit(a, _imm) _mm_castsi128_pd(vect_128_lshft_imm_sint64bit(_mm_castpd_si128(a), _imm))

#define vect_128_lshft_imm_sint8bit(a, _imm) vect_128_and(_mm_slli_epi16(a, _imm), vect_128_broad_cast_sint16bit((sint16bit_t)-1 << (_imm)))
#define vect_128_lshft_imm_sint16bit    _mm_slli_epi16
#define vect_128_lshft_imm_sint32bit    _mm_slli_epi32
#define vect_128_lshft_imm_sint64bit    _mm_slli_epi64

#define vect_128_lshft_imm_uint8bit     vect_128_lshft_imm_sint8bit
#define vect_128_lshft_imm_uint16bit    vect_128_lshft_imm_sint16bit
#define vect_128_lshft_imm_uint32bit    vect_128_lshft_imm_sint32bit
#define vect_128_lshft_imm_uint64bit    vect_128_lshft_imm_sint64bit


// theres no right 64 bit arithmetic shift we emualted by first doing a logical left shift or it with 1s
// we load the duplicate high 32 bits in each half and check if they are less than 0
// if they are they will be set to -1 if not they will be set to 0, then simply left shift the -1s
// zero(1, 0.3), shuffle(1, 0.5), lt(1, 0.5), sl(2), rsh(1, 1), or(1, 0.33) == 7 instrs

#define vect_128_rshift_logic_imm_sint8bit(a, _imm)  vect_128_and(_mm_srli_epi16(a, _imm), vect_128_broad_cast_sint16bit((sint16bit_t)-1 >> (_imm)))
#define vect_128_rshift_logic_imm_sint16bit _mm_srli_epi16
#define vect_128_rshift_logic_imm_sint32bit _mm_srli_epi32
#define vect_128_rshift_logic_imm_sint64bit _mm_srli_epi64


#define vect_128_rshft_arith_imm_sint8bit(v, _imm) ({   \
    vector_t _t = (v);                              \
    vect_128_or(                                    \
        vect_128_rshift_logic_imm_sint8bit(_t, _imm),        \
        vect_128_lshift_imm_sint8bit(_mm_cmplt_epi8(_t, _mm_setzero_si128()), (8 - _imm)\
    )); })

#define vect_128_rshft_arith_imm_sint16bit _mm_srai_epi16
#define vect_128_rshft_arith_imm_sint32bit _mm_srai_epi32
#define vect_128_rshft_arith_imm_sint64bit(v, _imm) ({                                       \
    vector_t _t = (v);                              \
    vect_128_or(                                    \
        vect_128_rshft_logic_imm_sint64bit(_t, i),        \
        vect_128_lshift_imm_sint64bit(                      \
            _mm_cmplt_epi32(_mm_shuffle_epi32(_t, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128()), \
            (64 - _imm)\
        )\
    ); })

//#define vector_bits_arith_rshft_imm(v, i) ({            \
//        vector_t _r;                                        \
//        switch(sizeof(i)){                                  \
//            case 1: _r = vector_and(vector_broad_cast((char)(-1 >> (i))), _mm_srai_epi32(v, i)); break ;   \
//            case 2: _r = _mm_srai_epi16(v, i); break ;      \
//            case 4: _r = _mm_srai_epi32(v, i); break ;      \
//            case 8: {                                       \
//                vector_t __t__ = (v);                       \
//                _r = vector_or(                             \
//                    vector_bits_logc_rshft_imm(__t__, i),   \
//                    vector_bits_lshft_imm(                  \
//                        _mm_cmplt_epi32(_mm_shuffle_epi32(__t__, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128()), \
//                        (bit_size(i) - i)\
//                    )); \
//            } break ;} \
//        _r; })
//

#define vect_128_sign_ext_sint8bit(a) _mm_cmplt_epi8(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint16bit(a) _mm_cmplt_epi16(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint32bit(a)  _mm_cmplt_epi32(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint64bit(a)  _mm_cmplt_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128())

#define vect_128_sign_ext_uint8bit   vect_128_sign_ext_sint8bit
#define vect_128_sign_ext_uint16bit  vect_128_sign_ext_sint16bit
#define vect_128_sign_ext_uint32bit  vect_128_sign_ext_sint32bit
#define vect_128_sign_ext_uint64bit  vect_128_sign_ext_sint64bit


#define vector_elems_logc_rshft(v, i) _mm_srli_si128(v, sizeof(i))

#define vector_bits_logc_rshft_imm(v, i) ({         \
        vector_t _r;                                    \
        switch(sizeof(i)){                              \
            case 1: _r = vector_and(                    \
                vector_broad_cast((char)(0xFF >> (i))), _mm_srli_epi32(v, i)); break;    \
            case 2: _r = _mm_srli_epi16(v, i); break ;  \
            case 4: _r = _mm_srli_epi32(v, i); break ;  \
            case 8: _r = _mm_srli_epi64(v, i); break ;  \
        } \
    _r;})


// compare vectors
//#define vect_128_is_zeros(a) (_mm_movemask_epi8(_mm_cmpeq_epi8(a, _mm_setzero_si128())) == 0xFFFF)
//#define vect_128_eq(a, b) (_mm_movemask_epi8(_mm_cmpeq_epi8(vector_xor(a, b), vector_zeros())) == 0xFFFF)


//#define vector_store_func(addr) ((((word_t)(addr)) % sizeof(vector_t)) ? &vector_store : &vector_store_algin)
//#define vector_zeros _mm_setzero_si128

#endif

#if defined (__SSE3__)
    #include <pmmintrin.h>

    #undef  vect_128_load_intgl
    #define vect_128_load_intgl(_p) _mm_lddqu_si128((__m128i const *)(_p))

#endif

#if defined (__SSE4_1__)
    #include <smmintrin.h>

    #undef vect_128_mul_sint32bit
    #define vect_128_mul_sint32bit   _mm_mullo_epi32

    #undef vect_128_extrt_sint8bit
    #define vect_128_extrt_sint8bit _mm_extract_epi8

    #undef vect_128_extrt_sint32bit
    #define vect_128_extrt_sint32bit  _mm_extract_epi32

    #undef vect_128_extrt_sint64bit
    #define vect_128_extrt_sint64bit  _mm_extract_epi64

    #undef vect_is_zeros
    #define vect_is_zeros(a) _mm_testz_si128(a, a)

    #undef vect_128_eq
//    #define vect_128_eq(a, b) _mm_testz_si128(vector_xor(a, b), _mm_set1_epi32(-1))
#endif


#endif
