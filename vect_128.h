

#ifndef __VECT_128__
#define __VECT_128__

#include "macro_utils.h"
#include "vect_def.h"

#include "scalr_types.h"
#include "comp_utils.h"

#include <immintrin.h>

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

#define vect_128_t_name(_memb_name) vect_t_name(128, _memb_name)
#define vect_128_types  MAP_LIST(vect_128_t_name, scalrs_names)


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


#define vect_128_set_native(_intrnl_v, expr) vect_set_native(_intrnl_v, expr)


#define vect_128_native_intrs(_oper_name, _memb_kind) _mm_ ## _oper_name


/***** STORE 128 bit vectors *******************************************************************************************/
// store on aligned addrs
#define vect_128_store_align_flt32bit(_p, _nv) 	_mm_store_ps((float *)(_p), _nv)
#define vect_128_store_align_flt64bit(_p, _nv)	_mm_store_pd((double *)(_p), _nv)
#define vect_128_store_align_intgl(_p, _nv)     _mm_store_si128((__m128i *)(_p), _nv)
#define vect_128_store_align_sint64             vect_128_store_align_intgl
#define vect_128_store_align_sint32             vect_128_store_align_intgl
#define vect_128_store_align_sint16             vect_128_store_align_intgl
#define vect_128_store_align_sint8              vect_128_store_align_intgl
#define vect_128_store_align_uint64             vect_128_store_align_intgl
#define vect_128_store_align_uint32             vect_128_store_align_intgl
#define vect_128_store_align_uint16             vect_128_store_align_intgl
#define vect_128_store_align_uint8              vect_128_store_align_intgl
#define _vect_128_store_align_(_memb_kind) vect_128_store_align_ ## _memb_kind  macro_cons_parens


#define vect_128_cast_to_flt32bit_native(expr) ((vect_128_flt32bit_native_t)(expr))

#define vect_128_cast_to_flt64bit_native(expr) ((vect_128_flt64bit_native_t)(expr))

#define vect_128_cast_to_intgl_native(expr) ((vect_128_intgl_native_t)(expr))

// store on any addrs, (safer but slower than aligned)
#define vect_128_store_flt32bit(_p, _nv)    _mm_storeu_ps((float *)(_p), vect_128_cast_to_flt32bit_native(_nv))
#define vect_128_store_flt64bit(_p, _nv)    _mm_storeu_pd((double *)(_p), vect_128_cast_to_flt64bit_native(_nv))
#define vect_128_store_intgl(_p, _nv)		_mm_storeu_si128((__m128i *)(_p), vect_128_cast_to_intgl_native(_nv))
#define vect_128_store_sint64bit            vect_128_store_intgl
#define vect_128_store_sint32bit            vect_128_store_intgl
#define vect_128_store_sint16bit            vect_128_store_intgl
#define vect_128_store_sint8bit             vect_128_store_intgl
#define vect_128_store_uint64bit            vect_128_store_intgl
#define vect_128_store_uint32bit            vect_128_store_intgl
#define vect_128_store_uint16bit            vect_128_store_intgl
#define vect_128_store_uint8bit             vect_128_store_intgl
#define _vect_128_store_(_memb_kind) vect_128_store_ ## _memb_kind  macro_cons_parens


// Store 128 bits to either aligned or unaligned address
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

#ifdef __SSE3__
    #undef  vect_128_load_intgl
    #define vect_128_load_intgl(_p)     _mm_lddqu_si128((__m128i const *)(_p))
#else
    #define vect_128_load_intgl(_p)     _mm_loadu_si128((__m128i const *)(_p))
#endif


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
    vect_128_set_native(                                                    \
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

#define vect_128_set_flt64bit(...)  _mm_set_pd     (_select(2, __VA_ARGS__))
#define vect_128_set_flt32bit(...)  _mm_set_ps     (_select(4, __VA_ARGS__))
#define vect_128_set_sint64bit(...) _mm_set_epi64x (_select(2, __VA_ARGS__))
#define vect_128_set_sint32bit(...) _mm_set_epi32  (_select(4, __VA_ARGS__))
#define vect_128_set_sint16bit(...) _mm_set_epi16  (_select(8, __VA_ARGS__))
#define vect_128_set_sint8bit(...)  _mm_set_epi8   (_select(16, __VA_ARGS__))
#define vect_128_set_uint64bit      vect_128_set_sint64bit
#define vect_128_set_uint32bit      vect_128_set_sint32bit
#define vect_128_set_uint16bit      vect_128_set_sint16bit
#define vect_128_set_uint8bit       vect_128_set_sint8bit

#define vect_128_set_(_memb_name) vect_128_set_ ## _memb_name macro_cons_parens

#define vect_128_set(_v, exprs...) (                            \
/*      ^^^^^^^^^^^^ set the components of an internal vect _v(vect_128_*_t
 *               where exprs is a comma seperated list of exprs starting from the most
 *               most significant to least */                   \
    vect_128_set_native(                                        \
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
#define vect_128_broad_cast(_v, expr) (                                                         \
    vect_128_set_native(                                                                        \
        _v,                                                                                     \
        macro_apply(                                                                            \
            scalr_switch,                                                                       \
            expr, MAP_LIST_APPLY_ARG(vect_128_broad_cast_, expr, scalrs_names), ((void)0)       \
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


#define vect_128_bin_cast_to_(a, b, cast_to) \
    (vect_128_cast_to_ ## cast_to ## _native(a), vect_128_cast_to_ ## cast_to ## _native(b))

#define _vect_128_native_bin_oper(oper, _memb_kind) \
    vect_128_ ## oper ## _ ## _memb_kind macro_cons_parens

#define vect_128_xor_flt64bit(a, b)     _mm_xor_pd      vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_xor_flt32bit(a, b)     _mm_xor_ps      vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_xor_intgl(a, b)        _mm_xor_si128   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_xor_sint64bit          vect_128_xor_intgl
#define vect_128_xor_sint32bit          vect_128_xor_intgl
#define vect_128_xor_sint16bit          vect_128_xor_intgl
#define vect_128_xor_sint8bit           vect_128_xor_intgl
#define vect_128_xor_uint64bit          vect_128_xor_intgl
#define vect_128_xor_uint32bit          vect_128_xor_intgl
#define vect_128_xor_uint16bit          vect_128_xor_intgl
#define vect_128_xor_uint8bit           vect_128_xor_intgl
#define _vect_128_xor_(_memb_kind)      _vect_128_native_bin_oper(xor, _memb_kind)


#define vect_128_or_flt64bit(a, b)      _mm_or_pd       vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_or_flt32bit(a, b)      _mm_or_ps       vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_or_intgl(a, b)         _mm_or_si128    vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_or_sint64bit           vect_128_or_intgl
#define vect_128_or_sint32bit           vect_128_or_intgl
#define vect_128_or_sint16bit           vect_128_or_intgl
#define vect_128_or_sint8bit            vect_128_or_intgl
#define vect_128_or_uint64bit           vect_128_or_intgl
#define vect_128_or_uint32bit           vect_128_or_intgl
#define vect_128_or_uint16bit           vect_128_or_intgl
#define vect_128_or_uint8bit            vect_128_or_intgl
#define _vect_128_or_(_memb_kind)       _vect_128_native_bin_oper(or, _memb_kind)


#define vect_128_and_flt64bit(a, b)     _mm_and_pd          vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_and_flt32bit(a, b)     _mm_and_ps          vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_and_intgl(a, b)        _mm_and_si128       vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_and_sint64bit          vect_128_and_intgl
#define vect_128_and_sint32bit          vect_128_and_intgl
#define vect_128_and_sint16bit          vect_128_and_intgl
#define vect_128_and_sint8bit           vect_128_and_intgl
#define vect_128_and_uint64bit          vect_128_and_intgl
#define vect_128_and_uint32bit          vect_128_and_intgl
#define vect_128_and_uint16bit          vect_128_and_intgl
#define vect_128_and_uint8bit           vect_128_and_intgl
#define _vect_128_and_(_memb_kind)       _vect_128_native_bin_oper(and, _memb_kind)

// TODO: figure out a way to detect scalar type and broadcast ...

#define vect_128_broad_cast_if_flt64bit    _mm_set1_pd
#define vect_128_broad_cast_if_flt32bit    _mm_set1_ps
#define vect_128_broad_cast_if_sint8bit    _mm_set1_epi8
#define vect_128_broad_cast_if_sint16bit   _mm_set1_epi16
#define vect_128_broad_cast_if_sint32bit   _mm_set1_epi32
#define vect_128_broad_cast_if_sint64bit   _mm_set1_epi64x
#define vect_128_broad_cast_if_uint8bit    vect_128_broad_cast_sint8bit
#define vect_128_broad_cast_if_uint16bit   vect_128_broad_cast_sint16bit
#define vect_128_broad_cast_if_uint32bit   vect_128_broad_cast_sint32bit
#define vect_128_broad_cast_if_uint64bit   vect_128_broad_cast_sint64bit



#define expr_from_possbl_vect(expr, _type) (((union {_type _val; typeof(expr) _e;}){._e = (expr)})._val)

#define vect_128_broad_cast_if_scalr(_opern, _vect)                     \
    scalr_switch(                                                       \
        _opern,                                                         \
        _mm_set1_pd(expr_from_possbl_vect(_opern,       double)),       \
        _mm_set1_ps(expr_from_possbl_vect(_opern,       float)),        \
        _mm_set1_epi64x(expr_from_possbl_vect(_opern,   long long)),    \
        _mm_set1_epi32(expr_from_possbl_vect(_opern,    int)),          \
        _mm_set1_epi16(expr_from_possbl_vect(_opern,    short)),        \
        _mm_set1_epi8(expr_from_possbl_vect(_opern,     char)),         \
        _mm_set1_epi64x(expr_from_possbl_vect(_opern,   long long)),    \
        _mm_set1_epi32(expr_from_possbl_vect(_opern,    int)),          \
        _mm_set1_epi16(expr_from_possbl_vect(_opern,    short)),        \
        _mm_set1_epi8(expr_from_possbl_vect(_opern,     char)),         \
        vect_native(expr_from_possbl_vect(_opern, typeof(_vect)))       \
    )

#define vect_128_bin_oper(oper, oper_a, oper_b, dest) (                 \
    vect_set_native(                                                    \
        dest,                                                           \
        macro_apply(                                                    \
            scalr_switch,                                               \
            vect_memb_t(dest),                                          \
            MAP_LIST_APPLY_ARG(                                         \
                _vect_128_ ## oper ## _,                                \
                macro_pack_args(                                        \
                    vect_128_broad_cast_if_scalr(oper_a, dest),         \
                    vect_128_broad_cast_if_scalr(oper_b, dest)          \
                ),                                                      \
                scalrs_names                                            \
            ),                                                          \
            (void)0                                                     \
         )                                                              \
   ), dest)



#undef vect_128_and
#define vect_128_and(a, b, out)  vect_128_bin_oper(and, a, b, out)
#undef vect_128_or
#define vect_128_or(a, b, out)   vect_128_bin_oper(or, a, b, out)
#undef vect_128_xor
#define vect_128_xor(a, b, out)  vect_128_bin_oper(xor, a, b, out)



// add two 128 bit vectors
#define vect_128_add_flt64bit(a, b)     _mm_add_pd      vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_add_flt32bit(a, b)     _mm_add_ps      vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_add_sint8bit(a, b)     _mm_add_epi8    vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_sint16bit(a, b)    _mm_add_epi16   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_sint32bit(a, b)    _mm_add_epi32   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_sint64bit(a, b)    _mm_add_epi64   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_uint8bit           vect_128_add_sint8bit
#define vect_128_add_uint16bit          vect_128_add_sint16bit
#define vect_128_add_uint32bit          vect_128_add_sint32bit
#define vect_128_add_uint64bit          vect_128_add_sint64bit
#define _vect_128_add_(_memb_kind)      _vect_128_native_bin_oper(add, _memb_kind)

#undef vect_128_add
#define vect_128_add(a, b, out)        vect_128_bin_oper(add, a, b, out)


// sub two vectors
#define vect_128_sub_flt64bit(a, b)     _mm_sub_pd      vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_sub_flt32bit(a, b)     _mm_sub_ps      vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_sub_sint8bit(a, b)     _mm_sub_epi8    vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_sint16bit(a, b)    _mm_sub_epi16   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_sint32bit(a, b)    _mm_sub_epi32   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_sint64bit(a, b)    _mm_sub_epi64   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_uint8bit           vect_128_sub_sint8bit
#define vect_128_sub_uint16bit          vect_128_sub_sint16bit
#define vect_128_sub_uint32bit          vect_128_sub_sint32bit
#define vect_128_sub_uint64bit          vect_128_sub_sint64bit
#define _vect_128_sub_(_memb_kind)      _vect_128_native_bin_oper(sub, _memb_kind)

#undef vect_128_sub
#define vect_128_sub(a, b, out)     vect_128_bin_oper(sub, a, b, out)



// mul two vectors
#define vect_128_mul_flt64bit(a, b)     _mm_mul_pd  vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_mul_flt32bit(a, b)     _mm_mul_ps  vect_128_bin_cast_to_(a, b, flt32bit)

/*
    SSE doesn't support 64 bit multiplication, but it can be emulated
     assume a, b are 64 bit numbers and high/low are their corresponding bits where low has its upper zerord out
     then a * b
        == (low(a) + high(a)) * (low(b) + high(b))
        == low(a)*low(b) + low(a)*high(b) + high(a)*low(b) + high(a)*high(b)
        == low(a)*low(b) + high(a)*high(b) + (high(a)*low(b) + high(a)*low(b))
        a * high(x) == a * ((x / 2**32) * 2**32) == (a * (x >> 32)) << 32

        high(a) * high(b) == (((a >> 32) * (b >> 32)) << 64) % 2**64 == 0 (so we can remove this one)

        high(a)*low(b) + low(a)*high(b)
        ((a >> 32)*b) << 32 + a*(b >> 32) << 32 == ((a >> 32)*b + (b >> 32)*a) << 32

    _add_64(
        _add_64(_mul_32(high(a), low(b)), _mul_32(low(a), high(b))) << 32,
        _mul_32(low(a), low(b))
    )

        reqs:
        _mm_shuffle_epi32:  2x(1, 0.5)
        _mm_mul_epu32:      3x(3, 1)
        _mm_add_epi64:      2x(1, 0.5)
        _mm_slli_epi64:     1x(1, 1)

        about 14 cycles ...
 */
#define vect_128_mul_sint64bit(a, b)  ({                                \
    vect_128_intgl_native_t                                             \
        low_a = vect_128_cast_to_intgl_native(a),                       \
        low_b = vect_128_cast_to_intgl_native(b),                       \
        high_a = _mm_shuffle_epi32(low_a, _MM_SHUFFLE(2, 3, 0, 1)),     \
        high_b = _mm_shuffle_epi32(low_b, _MM_SHUFFLE(2, 3, 0, 1));     \
        _mm_add_epi64(                          \
            _mm_mul_epu32(low_a, low_b),        \
            _mm_slli_epi64(                     \
                _mm_add_epi64(_mm_mul_epu32(high_a, low_b), _mm_mul_epu32(low_a, high_b)), \
                32                              \
            )                                   \
    ); })

#define vect_128_mul_uint64bit vect_128_mul_sint64bit

#ifdef __SSE4_1__
    #define vect_128_mul_sint32bit _mm_mullo_epi32
#else
// multiplies the the low and high 32 bits each creating a 64 bit unsigned result ...
#define vect_128_mul_sint32bit(a, b) ({               \
        vect_128_intgl_native_t                       \
            va = vect_128_cast_to_intgl_native(a),    \
            vb = vect_128_cast_to_intgl_native(b);    \
        _mm_unpacklo_epi32(                         \
            _mm_shuffle_epi32(                      \
                _mm_mul_epu32(va, vb),              \
                _MM_SHUFFLE (0,0,2,0)               \
            ),                                      \
            _mm_shuffle_epi32(                      \
                _mm_mul_epu32(                      \
                    _mm_srli_si128(va, 4),          \
                    _mm_srli_si128(vb, 4)           \
                ),                                  \
                _MM_SHUFFLE(0,0,2,0)                \
            )                                       \
        );  })
#endif
#define vect_128_mul_uint32bit vect_128_mul_sint32bit


#define vect_128_mul_sint16bit(a, b)      _mm_mullo_epi16 vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_mul_uint16bit      vect_128_mul_sint16bit


#ifdef __SSE4_1__
    #define vect_128_cvt_uint8bit_to_uint16bit      _mm_cvtepu8_epi16
#else
    #define vect_128_cvt_uint8bit_to_uint16bit(a)   _mm_unpacklo_epi8(a, _mm_setzero_si128())
#endif

// SSE doesn't support 8 bit multiplication we need to emulate it using 16 bit multiplication
//#ifdef __SSSE3__
/**
    1) spread out each of the upper 8 bits into 16 bits (zero extended) (and multiply)
    2) spread out each of the lower 8 bits into 16 bits (zero extended) (and multiply)
    3) join the solutions by selecting the lower 8 bit results from each 16 bit multiplication
    - _mm_setzero_si128:        2x(1, 0.33)
    - _mm_unpackhi_epi8:        2x(1, 0.5)
    - _mm_mullo_epi16:          2x(3, 1)
    - _mm_set_epi8:             0
    - _mm_shuffle_epi8(SSSE):   2x(1, 0.5)
    - _mm_or_si128:             1x(1, 0.33)

    vect_128_cvt_uint8bit_to_uint16bit:
        - _mm_cvtepu8_epi16(SSE4.1):             2x(1, 0.5)
        - _mm_unpacklo_epi8(1, 0.5), _mm_setzero_si128(1, 0.33)   2x(2, 0.5)


    about 13 cycles (give or take 1-2 cycles depending on SSE4.1 support) vs manually doing 16 muls (manually)
*/
//  requires SSS3 ....
#define vect_128_mul_ssse3_sint8bit(_a, _b) ({                      \
    vect_128_intgl_native_t                                         \
        va = vect_128_cast_to_intgl_native(_a),                     \
        vb = vect_128_cast_to_intgl_native(_b);                     \
    _mm_or_si128(                                                   \
          _mm_shuffle_epi8(                                         \
              _mm_mullo_epi16(                                      \
                  _mm_unpackhi_epi8(va, _mm_setzero_si128()),       \
                  _mm_unpackhi_epi8(vb, _mm_setzero_si128())        \
              ),                                                    \
              _mm_set_epi8(                                         \
                  14,   12,   10,   8,    6,    4,    2,    0,      \
                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80    \
              )                                                     \
          ),                                                        \
          _mm_shuffle_epi8(                                         \
              _mm_mullo_epi16(                                      \
                  vect_128_cvt_uint8bit_to_uint16bit(va),           \
                  vect_128_cvt_uint8bit_to_uint16bit(vb)            \
             ),                                                     \
             _mm_set_epi8(                                          \
                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,   \
                  14,   12,   10,   8,    6,    4,    2,    0       \
             )                                                      \
        )                                                           \
   ); })

/*
    1) multiply all the odd indexed 8 bit components
        (by doing a logical 8 bit right shift on 16 bit words)
    2) multiply all the even index 8 bit components
        (zero upper half by applying and mask)
    3) shift odd indexed reslt to the left by doing an 8 bit left shift on 16 bit words
    4) apply mask to even indexed results
    5) or both results together ...
    - _mm_srli_epi16:   2x(1, 1)
    - _mm_slli_epi16:   1x(1, 0.5)
    - _mm_mullo_epi16:  2x(3, 1)
    - _mm_and_si128:    3x(1, 0.33)
    - _mm_set_epi8:     ...
    - _mm_or_si128:     1x(1, 0.33)

    about 13 cycles
 */
#define vect_128_mul_sse2_sint8bit(_a, _b) ({           \
    vect_128_intgl_native_t                             \
        va = vect_128_cast_to_intgl_native(_a),         \
        vb = vect_128_cast_to_intgl_native(_b);         \
    const vect_128_intgl_native_t even_entrs            \
        = _mm_set_epi8(                                 \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF,         \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF          \
        );                                              \
    _mm_or_si128(                                       \
        _mm_slli_epi16(                                 \
            _mm_mullo_epi16(                            \
                _mm_srli_epi16(va, 8),                  \
                _mm_srli_epi16(vb, 8)                   \
            ),                                          \
        8),                                             \
        _mm_and_si128(                                  \
            _mm_mullo_epi16(                            \
                _mm_and_si128(va, even_entrs),          \
                _mm_and_si128(vb, even_entrs)           \
            ),                                          \
            even_entrs                                  \
        )                                               \
    ); })

// mul_ssse3_sint8bit slightly slower ...
#define vect_128_mul_sint8bit vect_128_mul_sse2_sint8bit
#define vect_128_mul_uint8bit vect_128_mul_sint8bit

#define _vect_128_mul_(_memb_kind) _vect_128_native_bin_oper(mul, _memb_kind)

#undef vect_128_mul
#define vect_128_mul(a, b, out) vect_128_bin_oper(mul, a, b, out)


// div two vectors
#define vect_128_div_flt64div   _mm_div_pd
#define vect_128_div_flt32div   _mm_div_ps

// TODO: Implmenet integral division using multithreaded code ...
/**************************************************************************************************/

// SSE supports shifts either by immediates or scalars

#define vect_128_lshft_imm_flt32bit(a, _imm) _mm_castsi128_ps(vect_128_lshft_imm_sint32bit(_mm_castps_si128(a), _imm))
#define vect_128_lshft_imm_flt64bit(a, _imm) _mm_castsi128_pd(vect_128_lshft_imm_sint64bit(_mm_castpd_si128(a), _imm))

// theres no 8 bit left shift but we can simulated by doing a 16 bit left shift
// and zeroing out the appropriate bits ...
// reqs:
//  _mm_and_si128: 1x(1, 0.33)
//  _mm_slli_epi16: 1x(1, 1)
// _mm_set1_epi16: ~ 1x(1, 0) (so about 2-3 cycles)
#define vect_128_lshft_imm_sint8bit(a, _imm) _mm_and_si128(_mm_slli_epi16(a, _imm), _mm_set1_epi16((short)((short)-1 << (_imm))))

#define vect_128_lshft_imm_sint16bit    _mm_slli_epi16
#define vect_128_lshft_imm_sint32bit    _mm_slli_epi32
#define vect_128_lshft_imm_sint64bit    _mm_slli_epi64

#define vect_128_lshft_imm_uint8bit     vect_128_lshft_imm_sint8bit
#define vect_128_lshft_imm_uint16bit    vect_128_lshft_imm_sint16bit
#define vect_128_lshft_imm_uint32bit    vect_128_lshft_imm_sint32bit
#define vect_128_lshft_imm_uint64bit    vect_128_lshft_imm_sint64bit

// theres no 8 bit logical right shift but we can simulated by doing
// a 16 bit logical right shift and zero out the appropriate parts
// reqs:
//      _mm_and_si128   1x(1, 0.33)
//      _mm_srli_epi16  1x(1, 1)
//      _mm_set1_epi16  1x(1, 0) (so about 2-3 cycles)
#define vect_128_rshift_logic_imm_sint8bit(a, _imm)  _mm_and_si128(_mm_srli_epi16(a, _imm), _mm_set1_epi16((sint16bit_t)-1 >> (_imm)))
#define vect_128_rshift_logic_imm_sint16bit _mm_srli_epi16
#define vect_128_rshift_logic_imm_sint32bit _mm_srli_epi32
#define vect_128_rshift_logic_imm_sint64bit _mm_srli_epi64

// theres no 8 bit arithmetic right shift, but we can simulated.
// reqs:
//      _mm_or_si128: 1x                    1x(1, 0.33)
//      vect_128_rshift_logic_imm_sint8bit: 1x(3, 1)
//      vect_128_lshift_imm_sint8bit:       1x(3, 1)
//      _mm_cmplt_epi8:                     1x(1, 0.5)
//      _mm_setzero_si128:                  1x(1, 0.33) (so about 9 cycles)
#define vect_128_rshft_arith_imm_sint8bit_0(v, _imm) ({           \
    vect_128_intgl_native_t _t = (v);                           \
    _mm_or_si128(                                               \
        vect_128_rshift_logic_imm_sint8bit(_t, _imm),           \
        vect_128_lshift_imm_sint8bit(_mm_cmplt_epi8(_t, _mm_setzero_si128()), (8 - _imm)\
    )); })

// requires about 7 cycles ...
#define vect_128_rshft_arith_imm_sint8bit_1(v, _imm) ({                     \
    vect_128_intgl_native_t _t = (v);                                       \
    _mm_or_si128(                                                           \
        _mm_and_si128(                                                      \
            _mm_srai_epi16(_t, _imm),                                       \
            _mm_set1_epi8(                                                  \
                255, 0, 255, 0, 255, 0, 255, 0,                             \
                255, 0, 255, 0, 255, 0, 255, 0                              \
            )                                                               \
        ),                                                                  \
        _mm_srli_epi16(_mm_srai_epi16(_mm_slli_epi16(v, 8), imm), 8));      \
    })

#define vect_128_rshft_arith_imm_sint8bit   vect_128_rshft_arith_imm_sint8bit_1
#define vect_128_rshft_arith_imm_sint16bit _mm_srai_epi16
#define vect_128_rshft_arith_imm_sint32bit _mm_srai_epi32

// theres no right 64 bit arithmetic shift we emualted by first doing a logical left shift or it with 1s
// we load the duplicate high 32 bits in each half and check if they are less than 0
// if they are they will be set to -1 if not they will be set to 0, then simply left shift the -1s
// reqs:
//      _mm_setzero_si128   1x(1, 0.3),
//      _mm_shuffle_epi32   1x(1, 0.5),
//      _mm_cmplt_epi32     1x(1, 0.5),
//      _mm_slli_epi64      1x(1, 1),
//      _mm_srli_epi64      1x(1, 1),
//      _mm_or_si128        1x(1, 0.33) == 6 instrs

#define vect_128_rshft_arith_imm_sint64bit(v, _imm) ({              \
    vect_128_intgl_native_t _t = (v);                               \
    _mm_or_si128(                                                   \
        _mm_srli_epi64(_t, _imm),                                   \
        _mm_slli_epi64(                                             \
            _mm_cmplt_epi32(                                        \
                _mm_shuffle_epi32(_t, _MM_SHUFFLE(3, 3, 1, 1)),     \
                _mm_setzero_si128()                                 \
            ),                                                      \
            (64 - (_imm))                                           \
        )                                                           \
    ); })









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

// sse2 can only extract the lower 64 bit number for the upper we need to either shuffer or shift



#define vect_128_sign_ext_sint8bit(a)   _mm_cmplt_epi8(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint16bit(a)  _mm_cmplt_epi16(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint32bit(a)  _mm_cmplt_epi32(a, _mm_setzero_si128())
#define vect_128_sign_ext_sint64bit(a)  _mm_cmplt_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128())

#define vect_128_sign_ext_uint8bit   vect_128_sign_ext_sint8bit
#define vect_128_sign_ext_uint16bit  vect_128_sign_ext_sint16bit
#define vect_128_sign_ext_uint32bit  vect_128_sign_ext_sint32bit
#define vect_128_sign_ext_uint64bit  vect_128_sign_ext_sint64bit


#define vector_elems_logc_rshft(v, i) _mm_srli_si128(v, sizeof(i))


#endif // __SSE2__


#endif
