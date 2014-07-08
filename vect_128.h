

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

#define vect_128_lshift          vect_128_no_supprt

#define vect_128_rshift_arith    vect_128_no_supprt
#define vect_128_rshift_logic    vect_128_no_supprt

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


#define FAST_COMPILATION


#ifdef FAST_COMPILATION
    vect_128_typedef(flt64bit)
    vect_128_typedef(flt32bit)

    vect_128_typedef(sint64bit)
    vect_128_typedef(sint32bit)
    vect_128_typedef(sint16bit)
    vect_128_typedef(sint8bit)

    vect_128_typedef(uint64bit)
    vect_128_typedef(uint32bit)
    vect_128_typedef(uint16bit)
    vect_128_typedef(uint8bit)
#else

    MAP(vect_128_typedef, scalrs_names)

#endif

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * declare varying internal vect_128_t types to keep track of packed member types
 * in order to determine which intrinsic to apply (@ compile time) ...
 */

#define vect_128_t_name(_memb_name) vect_t_name(128, _memb_name)


#undef _vect_128_t
#define _vect_128_t(_memb_name) vect_128_ ## _memb_name ## _t
#define vect_128_sel_t(expr_a, _type_a, expr_b) comp_select(expr_a, (_type_a){}, (expr_b))

#undef vect_128_t
#define vect_128_default_t vect_err_memb_no_suppt
#define _vect_128_expr(_memb_name) ((vect_t_name(128, _memb_name)){})

#ifdef FAST_COMPILATION
#define vect_128_t(args...) typeof(         \
    scalr_switch(                           \
        macro_arg_0(args),                  \
        _vect_128_expr(flt64bit),           \
        _vect_128_expr(flt32bit),           \
        _vect_128_expr(sint64bit),          \
        _vect_128_expr(sint32bit),          \
        _vect_128_expr(sint16bit),          \
        _vect_128_expr(sint8bit),           \
        _vect_128_expr(uint64bit),          \
        _vect_128_expr(uint32bit),          \
        _vect_128_expr(uint16bit),          \
        _vect_128_expr(uint8bit),           \
        (macro_arg_1(args, (void)0))          \
      )                                     \
    )
#else
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
#endif


#define vect_128_intrs_name(_kind, _memb_name) vect_128_ ## _kind ## _ ##  _memb_name
//      ^^^^^^^^^^^^^^^^^^^ returns the intrinsic macro name for vect_128 holding packed
//                          _memb_name(flt64bit, flt32bit, uint64bit ....)


#define vect_128_set_native(_intrnl_v, expr) ({vect_set_native(_intrnl_v, expr); _intrnl_v;})


#define _vect_128_native_oper(oper, _memb_kind) \
    vect_128_ ## oper ## _ ## _memb_kind macro_cons_parens

#ifdef FAST_COMPILATION
#define vect_128_apply_oper(oper, scalr_expr_t, params...)      \
    scalr_switch(                                               \
        scalr_expr_t,                                           \
        vect_128_ ## oper ## _ ## flt64bit(params),             \
        vect_128_ ## oper ## _ ## flt32bit(params),             \
        vect_128_ ## oper ## _ ## sint64bit(params),            \
        vect_128_ ## oper ## _ ## sint32bit(params),            \
        vect_128_ ## oper ## _ ## sint16bit(params),            \
        vect_128_ ## oper ## _ ## sint8bit(params),             \
        vect_128_ ## oper ## _ ## uint64bit(params),            \
        vect_128_ ## oper ## _ ## uint32bit(params),            \
        vect_128_ ## oper ## _ ## uint16bit(params),            \
        vect_128_ ## oper ## _ ## uint8bit(params),             \
        (void)0                                                 \
     )
#else
#define vect_128_apply_oper(oper, scalr_expr_t, params...) \
    macro_apply(                                    \
        scalr_switch,                               \
        scalr_expr_t,                               \
        MAP_LIST_APPLY_ARG(                         \
            _vect_128_ ## oper ## _,                \
            macro_pack_args(params),                \
            scalrs_names                            \
        ),                                          \
        (void)0                                     \
     )
#endif


#define vect_128_unr_or_bin(oper_name, args...) \
    macro_arg_2(                        \
        args,                           \
        vect_128_ ## oper_name ## _bin, \
        vect_128_ ## oper_name ## _unr  \
    )(args)

#define vect_128_unr_oper(oper, opernd, dest)           \
    vect_128_set_native(                                \
        dest,                                           \
        vect_128_apply_oper(oper, opernd, opernd)       \
   )

#define vect_128_bin_oper(oper, oper_a, oper_b, dest)   \
    vect_128_set_native(                                \
        dest,                                           \
        vect_128_apply_oper(oper, vect_memb_t(dest), oper_a, oper_b)   \
   )


#define vect_128_cast_to_flt32bit_native(expr)  ((vect_128_flt32bit_native_t)(expr))
#define vect_128_cast_to_flt64bit_native(expr)  ((vect_128_flt64bit_native_t)(expr))
#define vect_128_cast_to_intgl_native(expr)     ((vect_128_intgl_native_t)(expr))

/* Zero operand operations ************************************************************************************/
#define vect_128_set_zero_flt64bit  _mm_setzero_pd
#define vect_128_set_zero_flt32bit  _mm_setzero_ps
#define vect_128_set_zero_intgl     _mm_setzero_si128
#define vect_128_set_zero_sint64bit vect_128_set_zero_intgl
#define vect_128_set_zero_sint32bit vect_128_set_zero_intgl
#define vect_128_set_zero_sint16bit vect_128_set_zero_intgl
#define vect_128_set_zero_sint8bit  vect_128_set_zero_intgl
#define vect_128_set_zero_uint64bit vect_128_set_zero_intgl
#define vect_128_set_zero_uint32bit vect_128_set_zero_intgl
#define vect_128_set_zero_uint16bit vect_128_set_zero_intgl
#define vect_128_set_zero_uint8bit  vect_128_set_zero_intgl
#define _vect_128_set_zero_(_mem_kind) vect_128_set_zero_ ## _mem_kind



/***** STORE 128 bit vectors *******************************************************************************************/    
// store on aligned addrs
#define vect_128_store_align_flt32bit(_p, _nv) 	_mm_store_ps((float *)(_p), vect_128_cast_to_flt32bit_native(_nv))
#define vect_128_store_align_flt64bit(_p, _nv)	_mm_store_pd((double *)(_p), vect_128_cast_to_flt64bit_native(_nv))
#define vect_128_store_align_intgl(_p, _nv)     _mm_store_si128((__m128i *)(_p), vect_128_cast_to_intgl_native(_nv))
#define vect_128_store_align_sint64bit          vect_128_store_align_intgl
#define vect_128_store_align_sint32bit          vect_128_store_align_intgl
#define vect_128_store_align_sint16bit          vect_128_store_align_intgl
#define vect_128_store_align_sint8bit           vect_128_store_align_intgl
#define vect_128_store_align_uint64bit          vect_128_store_align_intgl
#define vect_128_store_align_uint32bit          vect_128_store_align_intgl
#define vect_128_store_align_uint16bit          vect_128_store_align_intgl
#define vect_128_store_align_uint8bit           vect_128_store_align_intgl
#define _vect_128_store_align_(_memb_kind) _vect_128_native_oper(store_align, _memb_kind)

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
#define _vect_128_store_(_memb_kind) _vect_128_native_oper(store, _memb_kind)


// Store 128 bits to either aligned or unaligned address
#define vect_128_store_(_kind, _p, _v)  ({  \
    const typeof(_v) _src_ = (_v);          \
    const typeof(_p) _dest_ = (_p);         \
    vect_128_apply_oper(                    \
        _kind,                              \
        vect_memb_t(_src_),                 \
        _dest_,                             \
        vect_native(_src_)                  \
    );                                      \
    _src_;                                  \
})

#undef  vect_128_store_align
#define vect_128_store_align(_p, _v) vect_128_store_(store_align, _p, _v)
#undef  vect_128_store
#define vect_128_store(_p, _v)       vect_128_store_(store, _p, _v)
                    
/***** LOAD 128 bit vectors *******************************************************************************************/
// LOAD 128 bit vector on aligned addresses
#define vect_128_load_align_flt32bit(_p)    _mm_load_ps((float const *)(_p))
#define vect_128_load_align_flt64bit(_p)    _mm_load_pd((double const *)(_p))
#define vect_128_load_align_intgl(_p)       _mm_load_si128((__m128i const *)(_p))
#define vect_128_load_align_sint64bit       vect_128_load_align_intgl
#define vect_128_load_align_sint32bit       vect_128_load_align_intgl
#define vect_128_load_align_sint16bit       vect_128_load_align_intgl
#define vect_128_load_align_sint8bit        vect_128_load_align_intgl
#define vect_128_load_align_uint64bit       vect_128_load_align_intgl
#define vect_128_load_align_uint32bit       vect_128_load_align_intgl
#define vect_128_load_align_uint16bit       vect_128_load_align_intgl
#define vect_128_load_align_uint8bit        vect_128_load_align_intgl
#define _vect_128_load_align_(_memb_kind)   _vect_128_native_oper(load_align, _memb_kind)

                    
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
#define _vect_128_load_(_memb_kind)   _vect_128_native_oper(load, _memb_kind)

#define vect_128_load_bin_(_kind, _p, _v) ({\
    const typeof((_p)[0]) *_lsrc = (_p);    \
    vect_128_set_native(                    \
        _v,                                 \
        vect_128_apply_oper(                \
            _kind,                          \
            vect_memb_t(_v),                \
            _lsrc                           \
        )                                   \
    );                                      \
})

#define is_vect_128_expr(expr) (                                 \
        comp_types_eq(typeof(expr), vect_128_flt64bit_t)         \
    ||  comp_types_eq(typeof(expr), vect_128_flt32bit_t)         \
    ||  comp_types_eq(typeof(expr), vect_128_sint64bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_sint32bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_sint16bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_sint8bit_t)         \
    ||  comp_types_eq(typeof(expr), vect_128_uint64bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_uint32bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_uint16bit_t)        \
    ||  comp_types_eq(typeof(expr), vect_128_uint8bit_t) )        \

// TODO: figure out a cleaner and faster solution ...


#define vect_128_load_unr_(_kind, _p) \
    ((typeof(comp_select(is_vect_128_expr((_p)[0]), (_p)[0], (vect_128_t((_p)[0], (typeof((_p)[0])){0})){0})))\
        vect_128_apply_oper(    \
            _kind,              \
            vect_memb_t(comp_select(is_vect_128_expr((_p)[0]), (_p)[0], (vect_128_t((_p)[0], (typeof((_p)[0])){0})){0})),\
            _p))
//    comp_select(                        \
//        bit_size(_p[0]) == 128,         \
//        vect_128_apply_oper(_kind, expr_from_possbl_vect(_p, vect_128_t(_p[0])), _p),\
//        vect_128_apply_oper(_kind, _p[0], _p))

#undef vect_128_load_align
#undef vect_128_load


#define vect_128_load_align_unr(_p)         vect_128_load_unr_(load_align, _p)
#define vect_128_load_align_bin(_p, _dest)  vect_128_load_bin_(load_align, _p, _dest)
#define vect_128_load_align(args...)        vect_128_unr_or_bin(load_align, args)

#define vect_128_load_bin(_p, _v)           vect_128_load_bin_(load, _p, _v)
#define vect_128_load_unr(_p)               vect_128_load_unr_(load, _p)
#define vect_128_load(args...)              vect_128_unr_or_bin(load, args)



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
#define _vect_128_set_(_memb_name) _vect_128_native_oper(set, _memb_name)

#define vect_128_set(_v, exprs...)                                                  \
/*      ^^^^^^^^^^^^ set the components of an internal vect _v(vect_128_*_t
 *               where exprs is a comma seperated list of exprs starting from the most
 *               most significant to least */                                       \
    vect_128_set_native(                                                            \
        _v,                                                                         \
        vect_128_apply_oper(set, vect_memb_t(_v), exprs, macro_comma_delim_16(0))   \
    )

                                                                                                                                                                                                                                                                                                        
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
#define _vect_128_broad_cast_(_memb_name) vect_128_broad_cast_ ## _memb_name


#define expr_from_possbl_vect(expr, _type)                  \
    comp_select(comp_types_eq(typeof(expr), _type), expr,   \
    ((((union {_type _val; typeof(expr) _e;})(expr)))._val))


#undef vect_128_broad_cast
#define vect_128_broad_cast_unr(expr) \
    ((vect_128_t(expr))(vect_128_apply_oper(broad_cast, expr, expr)))

#define vect_128_broad_cast_bin(expr, dest) \
    vect_128_set_native(dest, vect_128_apply_oper(broad_cast, expr, expr))

#define vect_128_broad_cast(args...) vect_128_unr_or_bin(broad_cast, args)


/** BINARY operators *****************************************************************************/
/*((((union {_type _val; typeof(expr) _e;})(expr)))._val)*/

    // broadcast scalar if _opern is an expr with a scalr eitherwise try to return the native vector
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
        vect_native(expr_from_possbl_vect(_opern,      typeof(_vect)))       \
    )

// if either or both operands is a scalar then they will be broadcasted based on the dest vector
// before the operation is applied ...
#define vect_128_bin_oper_broad_casted_scalrs(oper, oper_a, oper_b, dest) \
    vect_128_bin_oper(                                  \
        oper,                                           \
        vect_128_broad_cast_if_scalr(oper_a, dest),     \
        vect_128_broad_cast_if_scalr(oper_b, dest),     \
        dest                                            \
    )

#define vect_128_bin_cast_to_(_cast_a, _cast_b, cast_to) \
    (vect_128_cast_to_ ## cast_to ## _native(_cast_a), vect_128_cast_to_ ## cast_to ## _native(_cast_b))


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
#define _vect_128_xor_(_memb_kind)      _vect_128_native_oper(xor, _memb_kind)


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
#define _vect_128_or_(_memb_kind)       _vect_128_native_oper(or, _memb_kind)


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
#define _vect_128_and_(_memb_kind)       _vect_128_native_oper(and, _memb_kind)


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
#define _vect_128_add_(_memb_kind)      _vect_128_native_oper(add, _memb_kind)


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
#define _vect_128_sub_(_memb_kind)      _vect_128_native_oper(sub, _memb_kind)


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
#define vect_128_mul_sint64bit(a, b)  ({                \
    const vect_128_intgl_native_t                       \
        _low_a = vect_128_cast_to_intgl_native(a),      \
        _low_b = vect_128_cast_to_intgl_native(b);      \
        _mm_add_epi64(                                  \
            _mm_mul_epu32(_low_a, _low_b),              \
            _mm_slli_epi64(                             \
                _mm_add_epi64(                          \
                    _mm_mul_epu32(                      \
                        _low_b,                         \
                        _mm_shuffle_epi32(_low_a, _MM_SHUFFLE(2, 3, 0, 1))\
                    ),                                  \
                    _mm_mul_epu32(                      \
                        _low_a,                         \
                        _mm_shuffle_epi32(_low_b, _MM_SHUFFLE(2, 3, 0, 1))\
                    )                                   \
                ),                                      \
                32                                      \
            )                                           \
    ); })

#define vect_128_mul_uint64bit vect_128_mul_sint64bit

#ifdef __SSE4_1__
    #define vect_128_mul_sint32bit _mm_mullo_epi32
#else
// multiplies the the low and high 32 bits each creating a 64 bit unsigned result ...
// _mm_unpacklo_epi32:  1x(1, 0.5)
// _mm_shuffle_epi32:   2x(1, 0.5)
// _mm_mul_epu32:       2x(3, 1)
// _mm_srli_si128:      2x(1, 0.5)
// about 10 cycles ...
#define vect_128_mul_sint32bit(a, b) ({                         \
        const vect_128_intgl_native_t                           \
            _va_mul32 = vect_128_cast_to_intgl_native(a),       \
            _vb_mul32 = vect_128_cast_to_intgl_native(b);       \
        _mm_unpacklo_epi32(                                     \
            _mm_shuffle_epi32(                                  \
                _mm_mul_epu32(_va_mul32, _vb_mul32),            \
                _MM_SHUFFLE (0,0,2,0)                           \
            ),                                                  \
            _mm_shuffle_epi32(                                  \
                _mm_mul_epu32(                                  \
                    _mm_srli_si128(_va_mul32, 4),               \
                    _mm_srli_si128(_vb_mul32, 4)                \
                ),                                              \
                _MM_SHUFFLE(0,0,2,0)                            \
            )                                                   \
        );  })
#endif
#define vect_128_mul_uint32bit vect_128_mul_sint32bit


#define vect_128_mul_sint16bit(a, b)    _mm_mullo_epi16 vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_mul_uint16bit          vect_128_mul_sint16bit


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
#define vect_128_mul_ssse3_sint8bit(_a, _b) ({                          \
    const vect_128_intgl_native_t                                       \
        _va_mul_8bit = vect_128_cast_to_intgl_native(_a),               \
        _vb_mul_8bit = vect_128_cast_to_intgl_native(_b);               \
    _mm_or_si128(                                                       \
          _mm_shuffle_epi8(                                             \
              _mm_mullo_epi16(                                          \
                  _mm_unpackhi_epi8(_va_mul_8bit, _mm_setzero_si128()), \
                  _mm_unpackhi_epi8(_vb_mul_8bit, _mm_setzero_si128())  \
              ),                                                        \
              _mm_set_epi8(                                             \
                  14,   12,   10,   8,    6,    4,    2,    0,          \
                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80        \
              )                                                         \
          ),                                                            \
          _mm_shuffle_epi8(                                             \
              _mm_mullo_epi16(                                          \
                  vect_128_cvt_uint8bit_to_uint16bit(_va_mul_8bit),     \
                  vect_128_cvt_uint8bit_to_uint16bit(_vb_mul_8bit)      \
             ),                                                         \
             _mm_set_epi8(                                              \
                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,       \
                  14,   12,   10,   8,    6,    4,    2,    0           \
             )                                                          \
        )                                                               \
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
    const vect_128_intgl_native_t                       \
        _va_mul_8bit_sse2 = vect_128_cast_to_intgl_native(_a),         \
        _vb_mul_8bit_sse2 = vect_128_cast_to_intgl_native(_b),         \
        even_entrs = _mm_set_epi8(                                 \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF,         \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF          \
        );                                              \
    _mm_or_si128(                                       \
        _mm_slli_epi16(                                 \
            _mm_mullo_epi16(                            \
                _mm_srli_epi16(_va_mul_8bit_sse2, 8),   \
                _mm_srli_epi16(_vb_mul_8bit_sse2, 8)    \
            ),                                          \
        8),                                             \
        _mm_and_si128(                                  \
            _mm_mullo_epi16(                            \
                _mm_and_si128(_va_mul_8bit_sse2, even_entrs),          \
                _mm_and_si128(_vb_mul_8bit_sse2, even_entrs)           \
            ),                                          \
            even_entrs                                  \
        )                                               \
    ); })

// mul_ssse3_sint8bit seems slightly slower ...
#define vect_128_mul_sint8bit vect_128_mul_sse2_sint8bit
#define vect_128_mul_uint8bit vect_128_mul_sint8bit
#define _vect_128_mul_(_memb_kind) _vect_128_native_oper(mul, _memb_kind)


// div two vectors
#define vect_128_div_flt64div   _mm_div_pd
#define vect_128_div_flt32div   _mm_div_ps
// @@TODO: Implmenet integral division (test whether multithreaded code may be faster) ...


#define vect_128_apply_bin(oper_name, a, b)     \
    vect_128_apply_oper(oper_name, vect_memb_t(a), vect_native(a), vect_native(b))

#undef vect_128_and
#define vect_128_and(a, b, out)  vect_128_bin_oper_broad_casted_scalrs(and, a, b, out)
#define vect_128_and_bin(a, b)  vect_128_apply_bin(add, a, b)

#undef vect_128_or
#define vect_128_or(a, b, out)   vect_128_bin_oper_broad_casted_scalrs(or, a, b, out)
#define vect_128_or_bin(a, b)  vect_128_apply_bin(or, a, b)

#undef vect_128_xor
#define vect_128_xor(a, b, out)  vect_128_bin_oper_broad_casted_scalrs(xor, a, b, out)
#define vect_128_xor_bin(a, b)  vect_128_apply_bin(xor, a, b)

#undef vect_128_add
#define vect_128_add(a, b, out)  vect_128_bin_oper_broad_casted_scalrs(add, a, b, out)
#define vect_128_add_bin(a, b)   vect_128_apply_bin(add, a, b)

#undef vect_128_sub
#define vect_128_sub(a, b, out)  vect_128_bin_oper_broad_casted_scalrs(sub, a, b, out)
#undef vect_128_mul
#define vect_128_mul(a, b, out)  vect_128_bin_oper_broad_casted_scalrs(mul, a, b, out)


/**************************************************************************************************/

#ifdef __INTEL_COMPILER
#define vect_128_bin_oper_select_scalr_imm_oper(oper, a, _sclar_or_imm, dest) ( \
         (comp_expr_is_imm(_sclar_or_imm))                                      \
        ? vect_128_bin_oper(oper ## _imm, a, _sclar_or_imm, dest)               \
        : vect_128_bin_oper(oper ## _scalr, a, _sclar_or_imm, dest)             \
    )

#else
#define vect_128_bin_oper_select_scalr_imm_oper(oper, a, _sclar_or_imm, dest)       \
    comp_select(                                                                    \
        comp_expr_is_imm(_sclar_or_imm),                                            \
        vect_128_bin_oper(oper ## _imm, a, _sclar_or_imm, dest),                    \
        vect_128_bin_oper(oper ## _scalr, a, _sclar_or_imm, dest)                   \
    )
#endif


/** vect_128 right shift by immediate ... ********************************************************/

#define _vect_128_shift_native(shift_dirctn, shift_kind, shift_mag_kind, opern_bit_size, a, b) \
    _mm_s ## shift_dirctn ## shift_kind ## shift_mag_kind ## _epi ## opern_bit_size(vect_128_cast_to_intgl_native(a), b)

#define _vect_128_logic_left_shift_imm_native(bit_size, __va, _imm)    _vect_128_shift_native(l, l, i, bit_size, __va, _imm)
#define _vect_128_logic_right_shift_imm_native(bit_size, __va, _imm)   _vect_128_shift_native(r, l, i, bit_size, __va, _imm)
#define _vect_128_arith_right_shift_imm_native(bit_size, __va, _imm)   _vect_128_shift_native(r, a, i, bit_size, __va, _imm)

#define _vect_128_logic_left_shift_scalr_native(bit_size, __va, scalr_b)   _vect_128_shift_native(l, l, ,bit_size, __va, _mm_set1_epi64x(scalr_b))
#define _vect_128_logic_right_shift_scalr_native(bit_size, __va, scalr_b)  _vect_128_shift_native(r, l, ,bit_size, __va, _mm_set1_epi64x(scalr_b))
#define _vect_128_arith_right_shift_scalr_native(bit_size, __va, scalr_b)  _vect_128_shift_native(r, a, ,bit_size, __va, _mm_set1_epi64x(scalr_b))


#define vect_128_lshift_imm_flt64bit(a, _mag_imm)   _mm_castsi128_pd(_mm_slli_epi64(vect_128_cast_to_intgl_native(a), _mag_imm))
#define vect_128_lshift_imm_flt32bit(a, _mag_imm)   _mm_castsi128_ps(_mm_slli_epi32(vect_128_cast_to_intgl_native(a), _mag_imm))
#define vect_128_lshift_imm_sint64bit(a, _mag_imm)  _mm_slli_epi64(vect_128_cast_to_intgl_native(a), _mag_imm)
#define vect_128_lshift_imm_sint32bit(a, _mag_imm)  _mm_slli_epi32(vect_128_cast_to_intgl_native(a), _mag_imm)
#define vect_128_lshift_imm_sint16bit(a, _mag_imm)  _mm_slli_epi16(vect_128_cast_to_intgl_native(a), _mag_imm)
// theres no 8 bit left shift but we can simulated by doing a 16 bit left shift
// and zeroing out the appropriate top bits ...
// reqs:
//  _mm_and_si128: 1x(1, 0.33)
//  _mm_slli_epi16: 1x(1, 1)
// _mm_set1_epi16: ~ 1x(1, 0) (so about 2-3 cycles)
#define vect_128_lshift_imm_sint8bit(a, _mag_imm)                       \
    _mm_and_si128(                                                      \
        _mm_slli_epi16(vect_128_cast_to_intgl_native(a), _mag_imm),     \
        _mm_set1_epi8((unsigned char)(0xFF << ((_mag_imm) & 0b111)))    \
    )

#define vect_128_lshift_imm_uint64bit               vect_128_lshift_imm_sint64bit
#define vect_128_lshift_imm_uint32bit               vect_128_lshift_imm_sint32bit
#define vect_128_lshift_imm_uint16bit               vect_128_lshift_imm_sint16bit
#define vect_128_lshift_imm_uint8bit                vect_128_lshift_imm_sint8bit
#define _vect_128_lshift_imm_(_memb_kind) _vect_128_native_oper(lshift_imm, _memb_kind)


#define vect_128_lshift_scalr_flt64bit(a, b)    _mm_castsi128_pd(vect_128_lshift_scalr_sint64bit(vect_128_cast_to_intgl_native(a), b))
#define vect_128_lshift_scalr_flt32bit(a, b)    _mm_castsi128_ps(vect_128_lshift_scalr_sint32bit(a, b))
#define vect_128_lshift_scalr_sint64bit(a, b)   _vect_128_logic_left_shift_scalr_native(64, a, b)
#define vect_128_lshift_scalr_sint32bit(a, b)   _vect_128_logic_left_shift_scalr_native(32, a, b)
#define vect_128_lshift_scalr_sint16bit(a, b)   _vect_128_logic_left_shift_scalr_native(16, a, b)
#define vect_128_lshift_scalr_sint8bit(a, b)    ({  \
    const typeof(b) _sclrb = (b);                   \
    _mm_and_si128(                                  \
        _mm_sll_epi16(                              \
            vect_128_cast_to_intgl_native(a),       \
            _mm_set1_epi64x(_sclrb)                 \
        ),                                          \
        _mm_set1_epi8(0xFF << (_sclrb))             \
    ); })
#define vect_128_lshift_scalr_uint64bit         vect_128_lshift_scalr_sint64bit
#define vect_128_lshift_scalr_uint32bit         vect_128_lshift_scalr_sint32bit
#define vect_128_lshift_scalr_uint16bit         vect_128_lshift_scalr_sint16bit
#define vect_128_lshift_scalr_uint8bit          vect_128_lshift_scalr_sint8bit
#define _vect_128_lshift_scalr_(_memb_kind) _vect_128_native_oper(lshift_scalr, _memb_kind)


#define vect_128_rshift_logic_imm_flt64bit(a, _imm)     _mm_castsi128_pd(vect_128_rshift_logic_imm_sint64bit(a, _imm))
#define vect_128_rshift_logic_imm_flt32bit(a, _imm)     _mm_castsi128_ps(vect_128_rshift_logic_imm_sint32bit(a, _imm))
#define vect_128_rshift_logic_imm_sint64bit(a, _imm)    _vect_128_logic_right_shift_imm_native(64, a, _imm)
#define vect_128_rshift_logic_imm_sint32bit(a, _imm)    _vect_128_logic_right_shift_imm_native(32, a, _imm)
#define vect_128_rshift_logic_imm_sint16bit(a, _imm)    _vect_128_logic_right_shift_imm_native(16, a, _imm)
// theres no 8 bit logical right shift but we can simulated by doing
// a 16 bit logical right shift and zero out the appropriate parts
// reqs:
//      _mm_and_si128   1x(1, 0.33)
//      _mm_srli_epi16  1x(1, 1)
//      _mm_set1_epi16  1x(1, 0) (so about 2-3 cycles)
#define vect_128_rshift_logic_imm_sint8bit(a, _imm)  \
    _mm_and_si128(_mm_srli_epi16(vect_128_cast_to_intgl_native(a), _imm), _mm_set1_epi8(0xFF >> ((_imm) & 0b111)))
#define vect_128_rshift_logic_imm_uint64bit         vect_128_rshift_logic_imm_sint64bit
#define vect_128_rshift_logic_imm_uint32bit         vect_128_rshift_logic_imm_sint32bit
#define vect_128_rshift_logic_imm_uint16bit         vect_128_rshift_logic_imm_sint16bit
#define vect_128_rshift_logic_imm_uint8bit          vect_128_rshift_logic_imm_sint8bit
#define _vect_128_rshift_logic_imm_(_memb_kind)     _vect_128_native_oper(rshift_logic_imm, _memb_kind)


#define vect_128_rshift_logic_scalr_flt64bit(a, scalr_b)    _mm_castsi128_pd(vect_128_rshift_logic_scalr_sint64bit(a, scalr_b))
#define vect_128_rshift_logic_scalr_flt32bit(a, scalr_b)    _mm_castsi128_ps(vect_128_rshift_logic_scalr_sint32bit(a, scalr_b))
#define vect_128_rshift_logic_scalr_sint64bit(a, scalr_b)   _vect_128_logic_right_shift_scalr_native(64, a, scalr_b)
#define vect_128_rshift_logic_scalr_sint32bit(a, scalr_b)   _vect_128_logic_right_shift_scalr_native(32, a, scalr_b)
#define vect_128_rshift_logic_scalr_sint16bit(a, scalr_b)   _vect_128_logic_right_shift_scalr_native(16, a, scalr_b)
// 3-4 cycles ...
#define vect_128_rshift_logic_scalr_sint8bit(a, scalr_b)    ({\
    const typeof(scalr_b) shft_mag = (scalr_b); \
    _mm_and_si128(                              \
        _mm_srl_epi16(                          \
            vect_128_cast_to_intgl_native(a),   \
            _mm_set1_epi64x(shft_mag)           \
        ),                                      \
        _mm_set1_epi8(0xFFU >> shft_mag)        \
    );                                          \
})
#define vect_128_rshift_logic_scalr_uint64bit   vect_128_rshift_logic_scalr_sint64bit
#define vect_128_rshift_logic_scalr_uint32bit   vect_128_rshift_logic_scalr_sint32bit
#define vect_128_rshift_logic_scalr_uint16bit   vect_128_rshift_logic_scalr_sint16bit
#define vect_128_rshift_logic_scalr_uint8bit    vect_128_rshift_logic_scalr_sint8bit
#define _vect_128_rshift_logic_scalr_(_memb_kind)   _vect_128_native_oper(rshift_logic_scalr, _memb_kind)


#define vect_128_rshift_arith_imm_flt64bit(a, _imm)     _mm_castsi128_pd(vect_128_rshift_arith_imm_sint64bit(a, _imm))
#define vect_128_rshift_arith_imm_flt32bit(a, _imm)     _mm_castsi128_ps(vect_128_rshift_arith_imm_sint32bit(a, _imm))

// theres no right 64 bit arithmetic shift we emualted by first doing a logical left shift or it with 1s
// we load the duplicate high 32 bits in each half and check if they are less than 0
// if they are they will be set to -1 if not they will be set to 0, then simply left shift the -1s
// reqs:
//      _mm_setzero_si128   1x(1, 0.3),
//      _mm_shuffle_epi32   1x(1, 0.5),
//      _mm_cmplt_epi32     1x(1, 0.5),
//      _mm_slli_epi64      1x(1, 1),
//      _mm_srli_epi64      1x(1, 1),
//      _mm_or_si128        1x(1, 0.33) (about 6 cycles)
#define vect_128_rshift_arith_imm_sint64bit(v, _imm) ({             \
    const vect_128_intgl_native_t _t = vect_128_cast_to_intgl_native(v);  \
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

#define vect_128_rshift_arith_imm_sint32bit(a, _imm)    _vect_128_arith_right_shift_imm_native(32, a, _imm)
#define vect_128_rshift_arith_imm_sint16bit(a, _imm)    _vect_128_arith_right_shift_imm_native(16, a, _imm)
// 6-7 cycles ..
#define vect_128_rshift_arith_imm_sint8bit(_t, _imm) ({ \
    vect_128_intgl_native_t v = vect_128_cast_to_intgl_native(_t);                   \
    _mm_or_si128(                                       \
        _mm_and_si128(                                  \
            _mm_srai_epi16(v, _imm),                    \
            _mm_set_epi8(                               \
                255, 0, 255, 0, 255, 0, 255, 0,         \
                255, 0, 255, 0, 255, 0, 255, 0          \
            )                                           \
        ),                                              \
        _mm_srli_epi16(                                 \
            _mm_srai_epi16(_mm_slli_epi16(v, 8), _imm), \
            8                                           \
        )                                               \
    );                                                  \
})
#define vect_128_rshift_arith_imm_uint64bit             vect_128_rshift_arith_imm_sint64bit
#define vect_128_rshift_arith_imm_uint32bit             vect_128_rshift_arith_imm_sint32bit
#define vect_128_rshift_arith_imm_uint16bit             vect_128_rshift_arith_imm_sint16bit
#define vect_128_rshift_arith_imm_uint8bit              vect_128_rshift_arith_imm_sint8bit
#define _vect_128_rshift_arith_imm_(_memb_kind) _vect_128_native_oper(rshift_arith_imm, _memb_kind)


#define vect_128_rshift_arith_scalr_flt64bit(_shift_a, m_scalr_b)    \
    _mm_castsi128_pd(vect_128_rshift_arith_scalr_sint64bit(_shift_a, m_scalr_b))

#define vect_128_rshift_arith_scalr_flt32bit(a, scalr_b)    \
    _mm_castsi128_ps(vect_128_rshift_arith_scalr_sint32bit(a, scalr_b))

// 6 - 8 cycles ...
#define vect_128_rshift_arith_scalr_sint64bit(_shift_a, _scalr_mag_b)   ({   \
    const typeof(_scalr_mag_b) shift_mag = (_scalr_mag_b);          \
    const vect_128_intgl_native_t                                   \
        _rs_arth_va = vect_128_cast_to_intgl_native(_shift_a);      \
    _mm_or_si128(                                                   \
        _mm_srl_epi64(_rs_arth_va, _mm_set1_epi64x(shift_mag)),     \
        _mm_sll_epi64(                                              \
            _mm_cmplt_epi32(                                        \
                _mm_shuffle_epi32(                                  \
                    _rs_arth_va,                                    \
                    _MM_SHUFFLE(3, 3, 1, 1)                         \
               ),                                                   \
                _mm_setzero_si128()                                 \
            ),                                                      \
            _mm_set1_epi64x(64 - shift_mag)                         \
        )                                                           \
    );                                                              \
})
#define vect_128_rshift_arith_scalr_sint32bit(a, scalr_b)   _vect_128_arith_right_shift_scalr_native(32, a, scalr_b)
#define vect_128_rshift_arith_scalr_sint16bit(a, scalr_b)   _vect_128_arith_right_shift_scalr_native(16, a, scalr_b)
// 6-7 cycles ...
#define vect_128_rshift_arith_scalr_sint8bit(a, scalr_b)    ({      \
    const vect_128_intgl_native_t                                   \
        _rsh_arith_v8bit = vect_128_cast_to_intgl_native(a),        \
        shift_mag_v = _mm_set1_epi64x(scalr_b);                     \
    _mm_or_si128(                                                   \
        _mm_and_si128(                                              \
            _mm_sra_epi16(_rsh_arith_v8bit, shift_mag_v),           \
            _mm_set_epi8(                                           \
                0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0,                 \
                0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0                  \
            )                                                       \
        ),                                                          \
        _mm_srli_epi16(                                             \
            _mm_sra_epi16(                                          \
                _mm_slli_epi16(_rsh_arith_v8bit, 8),                \
                shift_mag_v                                         \
            ),                                                      \
            8                                                       \
        )                                                           \
    );                                                              \
})
#define vect_128_rshift_arith_scalr_uint64bit               vect_128_rshift_arith_scalr_sint64bit
#define vect_128_rshift_arith_scalr_uint32bit               vect_128_rshift_arith_scalr_sint32bit
#define vect_128_rshift_arith_scalr_uint16bit               vect_128_rshift_arith_scalr_sint16bit
#define vect_128_rshift_arith_scalr_uint8bit                vect_128_rshift_arith_scalr_sint8bit
#define _vect_128_rshift_arith_scalr_(_memb_kind) _vect_128_native_oper(rshift_arith_scalr, _memb_kind)


// Left Shift
#define vect_128_lshift_scalr(a, _scalr_b, dest)        vect_128_bin_oper(lshift_scalr, vect_native(a), _scalr_b, dest)
#define vect_128_lshift_imm(a, _imm, _dest)             vect_128_bin_oper(lshift_imm,   vect_native(a), _imm, _dest)
// Logical Right Shift
#define vect_128_rshift_logic_scalr(a, _scalr_b, dest)  vect_128_bin_oper(rshift_logic_scalr, vect_native(a), _scalr_b, dest)
#define vect_128_rshift_logic_imm(a, _imm_b, dest)      vect_128_bin_oper(rshift_logic_imm, vect_native(a), _imm_b, dest)

// Arithmetic Right Shift
#define vect_128_rshift_arith_scalr(a, _scalr_b, dest)  vect_128_bin_oper(rshift_arith_scalr, vect_native(a), _scalr_b, dest)
#define vect_128_rshift_arith_imm(a, _imm_b, dest)      vect_128_bin_oper(rshift_arith_imm, vect_native(a), _imm_b, dest)


#undef  vect_128_lshift
#define vect_128_lshift(_ia, __shft_mag, dest)                     \
    vect_128_bin_oper_select_scalr_imm_oper(lshift, vect_native(_ia), __shft_mag, dest)

#undef vect_128_rshift_logic
#define vect_128_rshift_logic(a, b, dest)               \
    vect_128_bin_oper_select_scalr_imm_oper(rshift_logic, vect_native(a), b, dest)

#undef vect_128_rshift_arith
#define vect_128_rshift_arith(a, b, dest)               \
    vect_128_bin_oper_select_scalr_imm_oper(rshift_arith, vect_native(a), b, dest)



/* Extends the sign bit result in either all zeros or all ones depending on most significant bit ...... */
#define vect_128_sign_ext_flt64bit(a)   _mm_castsi128_pd(vect_128_sign_ext_sint64bit(a))
#define vect_128_sign_ext_flt32bit(a)   _mm_castsi128_ps(vect_128_sign_ext_sint32bit(a))

#define vect_128_sign_ext_sint64bit(a) _mm_srai_epi32(_mm_shuffle_epi32(vect_128_cast_to_intgl_native(a), _MM_SHUFFLE(3, 3, 1, 1)), 32)
// ^^^^^^^^^^ copy the high 32 bits and right shift (2 cycles) ...
#define vect_128_sign_ext_sint32bit(a)  vect_128_rshift_arith_imm_sint32bit(a, 32)
#define vect_128_sign_ext_sint16bit(a)  vect_128_rshift_arith_imm_sint16bit(a, 16)
#define vect_128_sign_ext_sint8bit(a)   _mm_cmplt_epi8(vect_128_cast_to_intgl_native(a), _mm_setzero_si128()) // 2 cycles ...

#define vect_128_sign_ext_uint64bit  vect_128_sign_ext_sint64bit
#define vect_128_sign_ext_uint32bit  vect_128_sign_ext_sint32bit
#define vect_128_sign_ext_uint16bit  vect_128_sign_ext_sint16bit
#define vect_128_sign_ext_uint8bit   vect_128_sign_ext_sint8bit
#define _vect_128_sign_ext_(_memb_kind) _vect_128_native_oper(sign_ext, _memb_kind)

#undef vect_128_sign_ext
#define vect_128_sign_ext(a, dest) ({       \
    const typeof(a) _sign_ext_src = (a);    \
    vect_128_set_native(                    \
        dest,                               \
        vect_128_apply_oper(                \
            sign_ext,                       \
            vect_memb_t(_sign_ext_src),     \
            vect_native(_sign_ext_src)      \
        )                                   \
    ); })


// Extract components by immediate index ...

#ifndef __SSE4_1__
    #define _mm_extract_epi64(a, _imm)  ({                                                  \
        const vect_128_intgl_native_t _extrt_64bit_va                                       \
            = vect_128_cast_to_intgl_native(a);                                             \
        comp_select((_imm) == 0, _mm_cvtsi128_si64(_extrt_64bit_va),                        \
        comp_select((_imm) == 1, _mm_cvtsi128_si64(_mm_srli_si128(_extrt_64bit_va, 8)),     \
            _mm_cvtsi128_si64(_mm_srli_si128(_extrt_64bit_va, ((_imm & 0b1) << 3))))); })

    #define _mm_extract_epi32(a, _imm) ({                                                   \
        const vect_128_intgl_native_t _extrt_32bit_va                                       \
            = vect_128_cast_to_intgl_native(a);                                             \
        comp_select((_imm) == 0, _mm_cvtsi128_si32(a),                                      \
        comp_select((_imm) == 1, _mm_cvtsi128_si32(_mm_srli_si128(_extrt_32bit_va, 4)),     \
        comp_select((_imm) == 2, _mm_cvtsi128_si32(_mm_srli_si128(_extrt_32bit_va, 8)),     \
        comp_select((_imm) == 4, _mm_cvtsi128_si32(_mm_srli_si128(_extrt_32bit_va, 12)),    \
            _mm_cvtsi128_si32(_mm_srli_si128(_extrt_32bit_va, ((_imm) & 0b11) << 2)))))); })

    #define _mm_extract_ps(a, _imm) \
        _interp(_mm_extract_epi32(vect_128_cast_to_intgl_native(a), _imm), sint_bit_t(32), flt_bit_t(32))

    // _mm_extract_epi16 1x(3, 1)
    // shuffle 1x(1, 0.5)
    // about 2 cycles ...
    #define _mm_extract_epi8_ssse3(_va, _imm_)  ({              \
        const vect_128_intgl_native_t _va_extr_8bit_sse3        \
            = vect_128_cast_to_intgl_native(_va);               \
        comp_select(                                            \
            (_imm_) < 8,                                        \
            _mm_extract_epi16(                                  \
                _mm_shuffle_epi8(                               \
                    _va_extr_8bit_sse3,                         \
                    _mm_set_epi8(                               \
                        0x80, 7, 0x80, 6, 0x80, 5, 0x80, 4,     \
                        0x80, 3, 0x80, 2, 0x80, 1, 0x80, 0      \
                    )                                           \
                ),                                              \
                _imm_                                           \
             ),                                                 \
        comp_select(                                            \
            (_imm_) < 16,                                       \
            _mm_extract_epi16(                                  \
                _mm_shuffle_epi8(                               \
                    _va_extr_8bit_sse3,                         \
                    _mm_set_epi8(                               \
                        0x80, 15, 0x80, 14, 0x80, 13, 0x80, 12, \
                        0x80, 11, 0x80, 10, 0x80, 9, 0x80, 8    \
                    )                                           \
               ),                                               \
               (_imm_) - 8                                      \
            ),                                                  \
        _mm_cvtsi128_si32(_mm_srli_si128(_va_extr_8bit_sse3, (_imm_) & 15)) & 0xFF)); })

    // _mm_extract_epi16 1x(1, 0.5)
    // _mm_unpack*_epi8: 1x(1, 0.5)
    // _mm_setzero_si128: 1x(1, 0.33)  (about 3 cycles)
    #define _mm_extract_epi8_sse2(va, _imm)  ({                     \
        const vect_128_intgl_native_t _va_extrt_8bit_sse2           \
            vect_128_cast_to_intgl_native(va);                      \
        comp_select(                                                \
            (_imm) < 8,                                             \
            _mm_extract_epi16(                                      \
                _mm_unpacklo_epi8(                                  \
                    _va_extrt_8bit_sse2,                            \
                    _mm_setzero_si128()                             \
                ),                                                  \
                _imm                                                \
             ),                                                     \
        comp_select(                                                \
            (_imm) < 16,                                            \
            _mm_extract_epi16(                                      \
                _mm_unpackhi_epi8(                                  \
                    _va_extrt_8bit_sse2,                            \
                    _mm_setzero_si128()                             \
                ),                                                  \
                (_imm) - 8                                          \
            ),                                                      \
        _mm_cvtsi128_si32(                                          \
            _mm_srli_si128(_va_extrt_8bit_sse2, (_imm) & 15)        \
        ) & 0xFF )); })

    #ifdef __SSSE3__
        #define _mm_extract_epi8 _mm_extract_epi8_ssse3
    #else
        #define _mm_extract_epi8 _mm_extract_epi8_sse2
    #endif


#endif


// etract member from vectors ...
#define vect_128_extrt_imm_flt64bit(va_, _imm)      _interp(vect_128_extrt_imm_sint64bit(va_, _imm), sint_bit_t(64), flt_bit_t(64))
#define vect_128_extrt_imm_flt32bit(va_, _imm)      _mm_extract_ps(va_, _imm)
#define vect_128_extrt_imm_sint64bit(va_, _imm)     _mm_extract_epi64(vect_128_cast_to_intgl_native(va_), _imm)
#define vect_128_extrt_imm_sint32bit(va_, _imm)     _mm_extract_epi32(vect_128_cast_to_intgl_native(va_), _imm)
#define vect_128_extrt_imm_sint16bit(va_, _imm)     ((sint_bit_t(16))_mm_extract_epi16(vect_128_cast_to_intgl_native(va_), _imm))
#define vect_128_extrt_imm_sint8bit(va_, _imm)      ((sint_bit_t(8))_mm_extract_epi8(vect_128_cast_to_intgl_native(va_), _imm))
#define vect_128_extrt_imm_uint64bit(va_, _imm)     ((uint_bit_t(64))vect_128_extrt_imm_sint64bit(va_, _imm))
#define vect_128_extrt_imm_uint32bit(va_, _imm)     ((uint_bit_t(32))vect_128_extrt_imm_sint32bit(va_, _imm))
#define vect_128_extrt_imm_uint16bit(va_, _imm)     ((uint_bit_t(16))vect_128_extrt_imm_sint16bit(va_, _imm))
#define vect_128_extrt_imm_uint8bit(va_, _imm)      ((uint_bit_t(8))vect_128_extrt_imm_sint8bit(va_, _imm))
#define _vect_128_extrt_imm_(_memb_kind) _vect_128_native_oper(extrt_imm, _memb_kind)

#define vect_128_extrt_imm(va, imm) ({  \
    const typeof(va) _src_extrt = (va); \
    vect_128_apply_oper(extrt_imm, vect_memb_t(_src_extrt), vect_native(_src_extrt), imm); })


#endif // __SSE2__


#endif // __VECT_128__
