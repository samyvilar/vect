

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


//#define FAST_COMPILATION


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
        (macro_arg_1(args, (void)0))        \
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
        (macro_arg_1(args, (void)0))                     \
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
        vect_128_ ## oper ## _ ## flt64bit  (params),           \
        vect_128_ ## oper ## _ ## flt32bit  (params),           \
        vect_128_ ## oper ## _ ## sint64bit (params),           \
        vect_128_ ## oper ## _ ## sint32bit (params),           \
        vect_128_ ## oper ## _ ## sint16bit (params),           \
        vect_128_ ## oper ## _ ## sint8bit  (params),           \
        vect_128_ ## oper ## _ ## uint64bit (params),           \
        vect_128_ ## oper ## _ ## uint32bit (params),           \
        vect_128_ ## oper ## _ ## uint16bit (params),           \
        vect_128_ ## oper ## _ ## uint8bit  (params),           \
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

/* @@TODO: check if this indeed will speed up the compilation process ....  ************/
// some operations (load*, store*, xor, or, and) are be type oblivious so we can speed up compilation
// by not checking the expression at all ...
#define vect_128_apply_oblvs_scalr_oper(oper, scalr_expr_t, params...)  vect_128_ ## oper ## _scalr(params)

/*extern const typeof(scalr_expr_t) _exp_sing_t;*/
// some operations (add, sub, mullo) are sign oblivous
// so we can speed up compilation by only checking for flt and intgl types, for the intgl type we can use their size
#define vect_128_apply_oblvs_sign_oper(oper, scalr_expr_t, params...) ({\
    extern const typeof(scalr_expr_t) _24_sign_e_t_323_;                \
    vect_128_intgl_native_t _res_sign_bl;                               \
    if (expr_is_flt(_24_sign_e_t_323_))                                 \
        switch (sizeof(_24_sign_e_t_323_)) {                            \
            case 8: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _flt64bit(params); break ;     \
            case 4: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _flt32bit(params); break ;     \
            default: {  extern void invalid_flt_size_error(); invalid_flt_size_error(); }  \
        }                                                               \
    else                                                                \
        switch (sizeof(_24_sign_e_t_323_)) {                            \
            case 8: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _intgl64bit(params); break ;   \
            case 4: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _intgl32bit(params); break ;   \
            case 2: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _intgl16bit(params); break ;   \
            case 1: _res_sign_bl = (vect_128_intgl_native_t)vect_128_ ## oper ## _intgl8bit(params); break ;    \
            default: {extern void invalid_intgl_size_error();  invalid_intgl_size_error(); }  \
        }                                                               \
    (typeof(vect_native((vect_128_t(_24_sign_e_t_323_)){})))_res_sign_bl;   })


//    scalr_switch_flt(                                   \
//        scalr_expr_t,                                    \
//        vect_128_ ## oper ## _flt64bit(params),         \
//        vect_128_ ## oper ## _flt32bit(params),         \
//        scalr_switch_oblvs_sign_intgl(                  \
//            scalr_expr_t,                                \
//            vect_128_ ## oper ## _intgl64bit(params),   \
//            vect_128_ ## oper ## _intgl32bit(params),   \
//            vect_128_ ## oper ## _intgl16bit(params),   \
//            vect_128_ ## oper ## _intgl8bit(params),    \
//            (void)0                                     \
//       ))

/************************************************************************************/



#define vect_128_unr_or_bin(oper_name, args...) \
    macro_arg_2(                        \
        args,                           \
        vect_128_ ## oper_name ## _bin, \
        vect_128_ ## oper_name ## _unr  \
    )(args)

#define vect_128_bin_or_tnr(oper_name, args...) \
    macro_arg_3(                                \
        args,                                   \
        vect_128_ ## oper_name ## _tnr,         \
        vect_128_ ## oper_name ## _bin          \
    )(args)


#define vect_128_bin_oper(oper, oper_a, oper_b, dest, obvls)   \
    vect_128_set_native(                                \
        dest,                                           \
        vect_128_apply ## obvls ## _oper(oper, vect_memb_t(dest), oper_a, oper_b)   \
   )



#define expr_from_possbl_vect(expr, _type)                      \
    comp_select(                                                \
        comp_types_eq(typeof(expr), _type),                     \
        (expr),                                                 \
        ((((union {_type _val; typeof(expr) _e;})(expr)))._val) \
    )

/*((((union {_type _val; typeof(expr) _e;})(expr)))._val)*/
// broadcast scalar to native vect_128 if _opern is an expr with a scalr otherwise try to return the native vector
#define vect_128_broad_cast_to_native_if_scalr(_opern, _vect)                       \
    scalr_switch(                                                                   \
        _opern,                                                                     \
        _mm_set1_pd(expr_from_possbl_vect(_opern,       double)),                   \
        _mm_set1_ps(expr_from_possbl_vect(_opern,       float)),                    \
        _mm_set1_epi64x(expr_from_possbl_vect(_opern,   long long)),                \
        _mm_set1_epi32(expr_from_possbl_vect(_opern,    int)),                      \
        _mm_set1_epi16(expr_from_possbl_vect(_opern,    short)),                    \
        _mm_set1_epi8(expr_from_possbl_vect(_opern,     char)),                     \
        _mm_set1_epi64x(expr_from_possbl_vect(_opern,   unsigned long long)),       \
        _mm_set1_epi32(expr_from_possbl_vect(_opern,    unsigned int)),             \
        _mm_set1_epi16(expr_from_possbl_vect(_opern,    unsigned short)),           \
        _mm_set1_epi8(expr_from_possbl_vect(_opern,     unsigned char)),            \
        vect_native(expr_from_possbl_vect(_opern,       typeof(_vect)))             \
    )

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
    ||  comp_types_eq(typeof(expr), vect_128_uint8bit_t) )       \


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


/***** LOAD 128 bit vectors *******************************************************************************************/
// LOAD 128 bit vector on aligned addresses
#define vect_128_load_align_scalr           vect_128_load_align_intgl
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
#define vect_128_load_scalr             vect_128_load_intgl
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

#ifdef FAST_COMPILATION
#define vect_128_load_bin_(_kind, _p, _v)   \
    vect_128_set_native(_v, (typeof(vect_native(_v)))vect_128_ ## _kind ## _scalr(_p))

// @@TODO: CLEAN UP!!!!
#define vect_128_load_unr_(_kind, _p) ({    \
    static const typeof(comp_select(is_vect_128_expr((_p)[0]), (_p)[0], (vect_128_t((_p)[0], (typeof((_p)[0])){0})){0})) _t;\
        (typeof(_t))(typeof(vect_native(_t)))vect_128_ ## _kind ## _scalr(_p);    \
    })
#else
#define vect_128_load_bin_(_kind, _p, _v)   \
    vect_128_set_native(_v, vect_128_apply_oper(_kind, vect_memb_t(_v), _p))

// @@TODO: CLEAN UP!!!!
#define vect_128_load_unr_(_kind, _p) ({    \
    extern const typeof(comp_select(is_vect_128_expr((_p)[0]), (_p)[0], (vect_128_t((_p)[0], (typeof((_p)[0])){0})){0})) _t;\
        (typeof(_t))vect_128_apply_oper(_kind, vect_memb_t(_t), _p);    \
    })
#endif

#undef vect_128_load_align
#undef vect_128_load

#define vect_128_load_align_unr(_p)         vect_128_load_unr_(load_align, _p)
#define vect_128_load_align_bin(_p, _dest)  vect_128_load_bin_(load_align, _p, _dest)
#define vect_128_load_align(args...)        vect_128_unr_or_bin(load_align, args)

#define vect_128_load_bin(_p, _v)           vect_128_load_bin_(load, _p, _v)
#define vect_128_load_unr(_p)               vect_128_load_unr_(load, _p)
#define vect_128_load(args...)              vect_128_unr_or_bin(load, args)



/***** STORE 128 bit vectors *******************************************************************************************/    
// store on aligned addrs
#define vect_128_store_align_scalr              vect_128_store_align_intgl
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
#define vect_128_store_scalr                vect_128_store_intgl
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
#ifdef FAST_COMPILATION
#define vect_128_store_apply_func vect_128_apply_oblvs_scalr_oper
#else
#define vect_128_store_apply_func vect_128_apply_oper
#endif
#define vect_128_store_(_kind, _p, _v)  ({  \
    const typeof(_v) _s_sr_ = (_v);         \
    vect_128_store_apply_func(_kind, vect_memb_t(_s_sr_), _p, vect_native(_s_sr_)); \
    _s_sr_;                                 \
})

#undef  vect_128_store_align
#undef  vect_128_store
#define vect_128_store_align(_p, _v) vect_128_store_(store_align, _p, _v)
#define vect_128_store(_p, _v)       vect_128_store_(store, _p, _v)
                    

/***** SET each component of a vector from most sign to leas ....   ************************************/
#define vect_128_set_flt64bit(args...)      _mm_set_pd     (macro_select_args(2, args))
#define vect_128_set_flt32bit(args...)      _mm_set_ps     (macro_select_args(4, args))
#define vect_128_set_intgl64bit(args...)    _mm_set_epi64x (macro_select_args(2, args))
#define vect_128_set_intgl32bit(args...)    _mm_set_epi32  (macro_select_args(4, args))
#define vect_128_set_intgl16bit(args...)    _mm_set_epi16  (macro_select_args(8, args))
#define vect_128_set_intgl8bit(args...)     _mm_set_epi8   (macro_select_args(16, args))
#define vect_128_set_sint64bit      vect_128_set_intgl64bit
#define vect_128_set_sint32bit      vect_128_set_intgl32bit
#define vect_128_set_sint16bit      vect_128_set_intgl16bit
#define vect_128_set_sint8bit       vect_128_set_intgl8bit
#define vect_128_set_uint64bit      vect_128_set_sint64bit
#define vect_128_set_uint32bit      vect_128_set_sint32bit
#define vect_128_set_uint16bit      vect_128_set_sint16bit
#define vect_128_set_uint8bit       vect_128_set_sint8bit
#define _vect_128_set_(_memb_name) _vect_128_native_oper(set, _memb_name)

#ifdef FAST_COMPILATION
    #define vect_128_set(_v, exprs...) \
        vect_128_set_native(_v, vect_128_apply_oblvs_sign_oper(set, vect_memb_t(_v), exprs, macro_comma_delim_16(0)))
#else
#define vect_128_set(_v, exprs...)                                                  \
/*      ^^^^^^^^^^^^ set the components of an internal vect _v(vect_128_*_t
 *               where exprs is a comma seperated list of exprs starting from the most
 *               most significant to least */                                       \
    vect_128_set_native(_v, vect_128_apply_oper(set, vect_memb_t(_v), exprs, macro_comma_delim_16(0)))
#endif


                                                                                                                                                                                                                                                                                                        
/*****  UNARY vector operators  ****************************************************************************/
// broadcast expr into a vector type duplicating as many times as required ...
#define vect_128_broad_cast_flt64bit     _mm_set1_pd
#define vect_128_broad_cast_flt32bit     _mm_set1_ps
#define vect_128_broad_cast_intgl64bit   _mm_set1_epi64x
#define vect_128_broad_cast_intgl32bit   _mm_set1_epi32
#define vect_128_broad_cast_intgl16bit   _mm_set1_epi16
#define vect_128_broad_cast_intgl8bit    _mm_set1_epi8
#define vect_128_broad_cast_sint64bit   vect_128_broad_cast_intgl64bit
#define vect_128_broad_cast_sint32bit   vect_128_broad_cast_intgl32bit
#define vect_128_broad_cast_sint16bit   vect_128_broad_cast_intgl16bit
#define vect_128_broad_cast_sint8bit    vect_128_broad_cast_intgl8bit
#define vect_128_broad_cast_uint64bit   vect_128_broad_cast_intgl64bit
#define vect_128_broad_cast_uint32bit   vect_128_broad_cast_intgl32bit
#define vect_128_broad_cast_uint16bit   vect_128_broad_cast_intgl16bit
#define vect_128_broad_cast_uint8bit    vect_128_broad_cast_intgl8bit


#define _vect_128_broad_cast_(_memb_name) vect_128_broad_cast_ ## _memb_name

#ifdef FAST_COMPILATION
    #define vect_128_broad_cast_unr(expr) \
        ((vect_128_t(expr))(vect_128_apply_oblvs_sign_oper(broad_cast, expr, expr)))

    #define vect_128_broad_cast_bin(expr, dest) \
        vect_128_set_native(dest, vect_128_apply_oblvs_sign_oper(broad_cast, expr, expr))
#else
    #define vect_128_broad_cast_unr(expr) \
        ((vect_128_t(expr))(vect_128_apply_oper(broad_cast, expr, expr)))

    #define vect_128_broad_cast_bin(expr, dest) \
        vect_128_set_native(dest, vect_128_apply_oper(broad_cast, expr, expr))
#endif


#undef vect_128_broad_cast
#define vect_128_broad_cast(args...) vect_128_unr_or_bin(broad_cast, args)


/** BINARY operators *****************************************************************************/
#define vect_128_bin_cast_to_(_cast_a, _cast_b, cast_to) \
    (vect_128_cast_to_ ## cast_to ## _native(_cast_a), vect_128_cast_to_ ## cast_to ## _native(_cast_b))

#define vect_128_xor_scalr              vect_128_xor_intgl
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

#define vect_128_or_scalr               vect_128_or_intgl
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

#define vect_128_and_scalr              vect_128_and_intgl
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
#define vect_128_add_intgl64bit(a, b)    _mm_add_epi64   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_intgl32bit(a, b)    _mm_add_epi32   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_intgl16bit(a, b)    _mm_add_epi16   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_intgl8bit(a, b)     _mm_add_epi8    vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_add_sint64bit          vect_128_add_intgl64bit
#define vect_128_add_sint32bit          vect_128_add_intgl32bit
#define vect_128_add_sint16bit          vect_128_add_intgl16bit
#define vect_128_add_sint8bit           vect_128_add_intgl8bit
#define vect_128_add_uint64bit          vect_128_add_sint64bit
#define vect_128_add_uint32bit          vect_128_add_sint32bit
#define vect_128_add_uint16bit          vect_128_add_sint16bit
#define vect_128_add_uint8bit           vect_128_add_sint8bit
#define _vect_128_add_(_memb_kind)      _vect_128_native_oper(add, _memb_kind)


// sub two vectors
#define vect_128_sub_flt64bit(a, b)     _mm_sub_pd      vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_sub_flt32bit(a, b)     _mm_sub_ps      vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_sub_intgl64bit(a, b)    _mm_sub_epi64   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_intgl32bit(a, b)    _mm_sub_epi32   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_intgl16bit(a, b)    _mm_sub_epi16   vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_intgl8bit(a, b)     _mm_sub_epi8    vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_sub_sint64bit          vect_128_sub_intgl64bit
#define vect_128_sub_sint32bit          vect_128_sub_intgl32bit
#define vect_128_sub_sint16bit          vect_128_sub_intgl16bit
#define vect_128_sub_sint8bit           vect_128_sub_intgl8bit
#define vect_128_sub_uint64bit          vect_128_sub_intgl64bit
#define vect_128_sub_uint32bit          vect_128_sub_intgl32bit
#define vect_128_sub_uint16bit          vect_128_sub_intgl16bit
#define vect_128_sub_uint8bit           vect_128_sub_intgl8bit
#define _vect_128_sub_(_memb_kind)      _vect_128_native_oper(sub, _memb_kind)


// mul two vectors
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
#ifndef _mm_mullo_epi64
#define _mm_mullo_epi64(a, b)({                         \
    const vect_128_intgl_native_t                       \
        _low_b = vect_128_cast_to_intgl_native(b),      \
        _low_a = vect_128_cast_to_intgl_native(a)       \
        ;                                               \
        _mm_add_epi64(                                  \
            _mm_mul_epu32(_low_a, _low_b),              \
            _mm_slli_epi64(                             \
                _mm_add_epi64(                          \
                    _mm_mul_epu32(                      \
                        _low_b,                         \
                        _mm_shuffle_epi32(              \
                            _low_a,                     \
                            _MM_SHUFFLE(2, 3, 0, 1)     \
                        )                               \
                    ),                                  \
                    _mm_mul_epu32(                      \
                        _low_a,                         \
                        _mm_shuffle_epi32(              \
                            _low_b,                     \
                            _MM_SHUFFLE(2, 3, 0, 1)     \
                        )                               \
                    )                                   \
                ),                                      \
                32                                      \
            )                                           \
    ); })
#endif


#if !defined(__SSE4_1__) &&  !defined(_mm_mullo_epi32)
// multiplies the the low and high 32 bits each creating a 64 bit unsigned result ...
// _mm_unpacklo_epi32:  1x(1, 0.5)
// _mm_shuffle_epi32:   2x(1, 0.5)
// _mm_mul_epu32:       2x(3, 1)
// _mm_srli_si128:      2x(1, 0.5)
// about 10 cycles ...
#define _mm_mullo_epi32(a, b) ({                                \
        const vect_128_intgl_native_t                           \
            _vb_mul32 = vect_128_cast_to_intgl_native(b),       \
            _va_mul32 = vect_128_cast_to_intgl_native(a)        \
            ;                                                   \
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
#define _mm_mullo_epi8_ssse3(_a, _b) ({                          \
    const vect_128_intgl_native_t                                       \
        _vb_mul_8bit = vect_128_cast_to_intgl_native(_b),               \
        _va_mul_8bit = vect_128_cast_to_intgl_native(_a);                \
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
#define _mm_mullo_epi8_sse2(_a, _b) ({                          \
    const vect_128_intgl_native_t                               \
        _vb_mul_8bit_sse2 = vect_128_cast_to_intgl_native(_b),  \
        _va_mul_8bit_sse2 = vect_128_cast_to_intgl_native(_a),  \
        even_entrs = _mm_set_epi8(                              \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF,                 \
            0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF                  \
        );                                                      \
    _mm_or_si128(                                               \
        _mm_slli_epi16(                                         \
            _mm_mullo_epi16(                                    \
                _mm_srli_epi16(_va_mul_8bit_sse2, 8),           \
                _mm_srli_epi16(_vb_mul_8bit_sse2, 8)            \
            ),                                                  \
        8),                                                     \
        _mm_and_si128(                                          \
            _mm_mullo_epi16(                                    \
                _mm_and_si128(_va_mul_8bit_sse2, even_entrs),   \
                _mm_and_si128(_vb_mul_8bit_sse2, even_entrs)    \
            ),                                                  \
            even_entrs                                          \
        )                                                       \
    ); })

// mul_ssse3_sint8bit seems slightly slower ...
#ifndef _mm_mullo_epi8
#define _mm_mullo_epi8 _mm_mullo_epi8_sse2
#endif


    // mul two vectors
#define vect_128_mul_flt64bit(a, b)     _mm_mul_pd  vect_128_bin_cast_to_(a, b, flt64bit)
#define vect_128_mul_flt32bit(a, b)     _mm_mul_ps  vect_128_bin_cast_to_(a, b, flt32bit)
#define vect_128_mul_intgl64bit         _mm_mullo_epi64
#define vect_128_mul_intgl32bit         _mm_mullo_epi32
#define vect_128_mul_intgl16bit(a, b)   _mm_mullo_epi16 vect_128_bin_cast_to_(a, b, intgl)
#define vect_128_mul_intgl8bit          _mm_mullo_epi8
#define vect_128_mul_sint64bit          vect_128_mul_intgl64bit
#define vect_128_mul_sint32bit          vect_128_mul_intgl32bit
#define vect_128_mul_sint16bit          vect_128_mul_intgl16bit
#define vect_128_mul_sint8bit           vect_128_mul_intgl8bit
#define vect_128_mul_uint64bit          vect_128_mul_intgl64bit
#define vect_128_mul_uint32bit          vect_128_mul_intgl32bit
#define vect_128_mul_uint16bit          vect_128_mul_intgl16bit
#define vect_128_mul_uint8bit           vect_128_mul_intgl8bit
#define _vect_128_mul_(_kind)           _vect_128_native_oper(mul, _kind)




// div two vectors
#define vect_128_div_flt64div   _mm_div_pd
#define vect_128_div_flt32div   _mm_div_ps
// @@TODO: Implmenet integral division (test whether multithreaded code may be faster) ...


#define vect_128_apply_bin(oper_name, a, b)     \
    vect_128_apply_oper(oper_name, vect_memb_t(a), vect_native(a), vect_native(b))   


#define get_vect_128_apply_func(oblvs...)     vect_128_apply ## oblvs ## _oper
#define vect_128_unr_broad_cast_scalrs(oper, oper_a, oblvs...) ({       \
    extern const vect_128_t(oper_a, (typeof(oper_a)){0}) _unr_asdt;     \
    (typeof(_unr_asdt))(typeof(vect_native(_unr_asdt)))(                \
        get_vect_128_apply_func(oblvs) (                                \
            oper, vect_memb_t(_unr_asdt), vect_128_broad_cast_to_native_if_scalr(oper_a, _unr_asdt)\
        )                                                               \
    ); })

// @@TODO: clean up this MESS!!!!
//vect_128_apply_oblvs_scalr_oper
#define vect_128_bin_broad_cast_scalrs(oper, oper_a, oper_b, oblvs...) ({       \
    extern const vect_128_t(oper_a, (typeof(oper_a)){0}) _bin_ad_da1_t;         \
    (typeof(_bin_ad_da1_t))(typeof(vect_native(_bin_ad_da1_t)))(get_vect_128_apply_func(oblvs)(\
        oper,                                                                   \
        vect_memb_t(_bin_ad_da1_t),                                             \
        vect_128_broad_cast_to_native_if_scalr(oper_a, _bin_ad_da1_t),          \
        vect_128_broad_cast_to_native_if_scalr(oper_b, _bin_ad_da1_t))); })


#define vect_128_tnr_oper_broad_casted_scalrs(oper, oper_a, oper_b, dest, oblvs...) \
    vect_128_bin_oper(                                          \
        oper,                                                   \
        vect_128_broad_cast_to_native_if_scalr(oper_a, dest),   \
        vect_128_broad_cast_to_native_if_scalr(oper_b, dest),   \
        dest,                                                   \
        oblvs                                                   \
    )

#ifdef FAST_COMPILATION
#define _apply_oblvs_scalr_oper _oblvs_scalr
#define _apply_oblvs_sign_oper _oblvs_sign
#else
#define _apply_oblvs_scalr_oper
#define _apply_oblvs_sign_oper
#endif


#define vect_128_and_bin(args...)   vect_128_bin_broad_cast_scalrs(and, args, _apply_oblvs_scalr_oper)
#define vect_128_and_tnr(args...)   vect_128_tnr_oper_broad_casted_scalrs(and, args, _apply_oblvs_scalr_oper)

#define vect_128_or_bin(args...)    vect_128_bin_broad_cast_scalrs(or, args, _apply_oblvs_scalr_oper)
#define vect_128_or_tnr(args...)    vect_128_tnr_oper_broad_casted_scalrs(or, args, _apply_oblvs_scalr_oper)

#define vect_128_xor_bin(args...)   vect_128_bin_broad_cast_scalrs(xor, args, _apply_oblvs_scalr_oper)
#define vect_128_xor_tnr(args...)   vect_128_tnr_oper_broad_casted_scalrs(xor, args, _apply_oblvs_scalr_oper)

#define vect_128_add_bin(args...)   vect_128_bin_broad_cast_scalrs(add, args, _apply_oblvs_sign_oper)
#define vect_128_add_tnr(args...)   vect_128_tnr_oper_broad_casted_scalrs(add, args, _apply_oblvs_sign_oper)

#define vect_128_sub_bin(args...)   vect_128_bin_broad_cast_scalrs(sub, args, _apply_oblvs_sign_oper)
#define vect_128_sub_tnr(args...)   vect_128_tnr_oper_broad_casted_scalrs(sub, args, _apply_oblvs_sign_oper)

#define vect_128_mul_bin(args...)   vect_128_bin_broad_cast_scalrs(mul, args, _apply_oblvs_sign_oper)
#define vect_128_mul_tnr(args...)   vect_128_tnr_oper_broad_casted_scalrs(mul, args, _apply_oblvs_sign_oper)


#undef vect_128_and
#undef vect_128_or
#undef vect_128_xor
#define vect_128_and(args...)       vect_128_bin_or_tnr(and, args)
#define vect_128_or(args...)        vect_128_bin_or_tnr(or, args)
#define vect_128_xor(args...)       vect_128_bin_or_tnr(xor, args)


#undef vect_128_add
#define vect_128_add(args...)       vect_128_bin_or_tnr(add, args)

#undef vect_128_sub
#define vect_128_sub(args...)       vect_128_bin_or_tnr(sub, args)

#undef vect_128_mul
#define vect_128_mul(args...)       vect_128_bin_or_tnr(mul, args)


/** vect_128 right shift by immediate ... ********************************************************/

#ifndef _mm_slli_epi8
// theres no 8 bit left shift but we can simulated by doing a 16 bit left shift
// and zeroing out the appropriate top bits ...
// reqs:
//  _mm_and_si128: 1x(1, 0.33)
//  _mm_slli_epi16: 1x(1, 1)
// _mm_set1_epi16: ~ 1x(1, 0) (so about 2-3 cycles)
#define _mm_slli_epi8(a, _mag_imm)                                      \
    _mm_and_si128(                                                      \
        _mm_slli_epi16(a, _mag_imm),                                    \
        _mm_set1_epi8((unsigned char)(0xFF << ((_mag_imm) & 0b111)))    \
    )
#endif

#ifndef _mm_sll_epi8
// (3-4 cycles)
#define _mm_sll_epi8(a, b) ({                           \
    const typeof(b) _opern_b = (b);                     \
    _mm_and_si128(                                      \
        _mm_sll_epi16(a, _opern_b),                     \
        _mm_set1_epi8(0xFF << _mm_cvtsi128_si64(_opern_b)) \
    ); })
#endif

#ifndef _mm_srli_epi8
// theres no 8 bit logical right shift but we can simulated by doing
// a 16 bit logical right shift and zero out the appropriate parts
// reqs:
//      _mm_and_si128   1x(1, 0.33)
//      _mm_srli_epi16  1x(1, 1)
//      _mm_set1_epi16  1x(1, 0) (so about 2-3 cycles)
#define _mm_srli_epi8(a, b) _mm_and_si128(_mm_srli_epi16(a, b), _mm_set1_epi8(0xFF >> ((b) & 0b111)))
#endif

#ifndef _mm_srl_epi8
// (3-4) cycles ...
#define _mm_srl_epi8(a, b) ({                                   \
    const typeof(b) _shft_mag = (b);                            \
    _mm_and_si128(                                              \
        _mm_srl_epi16(a, _shft_mag),                            \
        _mm_set1_epi8(0xFFU >> _mm_cvtsi128_si64(_shft_mag))    \
    ); })
#endif


#ifndef _mm_srai_epi8
// 6-7 cycles ..
#define _mm_srai_epi8(a, _imm) ({ \
    vect_128_intgl_native_t _rash8b_t = vect_128_cast_to_intgl_native(a);                   \
    _mm_or_si128(                                       \
        _mm_and_si128(                                  \
            _mm_srai_epi16(_rash8b_t, _imm),            \
            _mm_set_epi8(                               \
                255, 0, 255, 0, 255, 0, 255, 0,         \
                255, 0, 255, 0, 255, 0, 255, 0          \
            )                                           \
        ),                                              \
        _mm_srli_epi16(                                 \
            _mm_srai_epi16(_mm_slli_epi16(_rash8b_t, 8), _imm), \
            8                                           \
        )                                               \
    ); })
#endif


#ifndef _mm_sra_epi8
// 6-7 cycles ..
#define _mm_sra_epi8(a, b) ({ \
    vect_128_intgl_native_t                             \
        _23_rash8b_t = vect_128_cast_to_intgl_native(b),   \
        _23_rash8a_t = vect_128_cast_to_intgl_native(a);   \
    _mm_or_si128(                                       \
        _mm_and_si128(                                  \
            _mm_sra_epi16(_23_rash8a_t, _23_rash8b_t),            \
            _mm_set_epi8(                               \
                255, 0, 255, 0, 255, 0, 255, 0,         \
                255, 0, 255, 0, 255, 0, 255, 0          \
            )                                           \
        ),                                              \
        _mm_srli_epi16(                                 \
            _mm_sra_epi16(_mm_slli_epi16(_23_rash8a_t, 8), _23_rash8b_t), \
            8                                           \
        )                                               \
    ); })
#endif




#ifndef _mm_srai_epi64
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
#define _mm_srai_epi64(v, _imm) ({             \
    const vect_128_intgl_native_t _rash_t = vect_128_cast_to_intgl_native(v);  \
    _mm_or_si128(                                                   \
        _mm_srli_epi64(_rash_t, _imm),                              \
        _mm_slli_epi64(                                             \
            _mm_cmplt_epi32(                                        \
                _mm_shuffle_epi32(_rash_t, _MM_SHUFFLE(3, 3, 1, 1)),\
                _mm_setzero_si128()                                 \
            ),                                                      \
            (64 - (_imm))                                           \
        )                                                           \
    ); })
#endif

#ifndef _mm_sra_epi64
// (6 - 8) cycles ...
#define _mm_sra_epi64(a, b)   ({                                    \
    const vect_128_intgl_native_t                                   \
        _rs_arth_vb = vect_128_cast_to_intgl_native(b),             \
        _rs_arth_va = vect_128_cast_to_intgl_native(a);             \
    _mm_or_si128(                                                   \
        _mm_srl_epi64(_rs_arth_va, _rs_arth_vb),                    \
        _mm_sll_epi64(                                              \
            _mm_cmplt_epi32(                                        \
                _mm_shuffle_epi32(                                  \
                    _rs_arth_va,                                    \
                    _MM_SHUFFLE(3, 3, 1, 1)                         \
               ),                                                   \
                _mm_setzero_si128()                                 \
            ),                                                      \
            _mm_sub_epi64(_mm_set1_epi64x(64), _rs_arth_vb)         \
        )                                                           \
    );                                                              \
})
#endif


// shifting by an immediate ...
#define vect_128_lshift_imm_flt64bit(a, _mag_imm)   _mm_castsi128_pd(_mm_slli_epi64(vect_128_cast_to_intgl_native(a), _mag_imm))
#define vect_128_lshift_imm_flt32bit(a, _mag_imm)   _mm_castsi128_ps(_mm_slli_epi32(vect_128_cast_to_intgl_native(a), _mag_imm))
#define vect_128_lshift_imm_intgl64bit              _mm_slli_epi64
#define vect_128_lshift_imm_intgl32bit              _mm_slli_epi32
#define vect_128_lshift_imm_intgl16bit              _mm_slli_epi16
#define vect_128_lshift_imm_intgl8bit               _mm_slli_epi8
#define vect_128_lshift_imm_sint64bit               vect_128_lshift_imm_intgl64bit
#define vect_128_lshift_imm_sint32bit               vect_128_lshift_imm_intgl32bit
#define vect_128_lshift_imm_sint16bit               vect_128_lshift_imm_intgl16bit
#define vect_128_lshift_imm_sint8bit                vect_128_lshift_imm_intgl8bit
#define vect_128_lshift_imm_uint64bit               vect_128_lshift_imm_intgl64bit
#define vect_128_lshift_imm_uint32bit               vect_128_lshift_imm_intgl32bit
#define vect_128_lshift_imm_uint16bit               vect_128_lshift_imm_intgl16bit
#define vect_128_lshift_imm_uint8bit                vect_128_lshift_imm_intgl8bit
#define _vect_128_lshift_imm_(_memb_kind) _vect_128_native_oper(lshift_imm, _memb_kind)

// shifting by a non immediate ...
#define vect_128_lshift_scalr_flt64bit(a, b)    _mm_castsi128_pd(vect_128_lshift_scalr_sint64bit(vect_128_cast_to_intgl_native(a), b))
#define vect_128_lshift_scalr_flt32bit(a, b)    _mm_castsi128_ps(vect_128_lshift_scalr_sint32bit(a, b))
#define vect_128_lshift_scalr_intgl64bit        _mm_sll_epi64
#define vect_128_lshift_scalr_intgl32bit        _mm_sll_epi32
#define vect_128_lshift_scalr_intgl16bit        _mm_sll_epi16
#define vect_128_lshift_scalr_intgl8bit         _mm_sll_epi8
#define vect_128_lshift_scalr_sint64bit         vect_128_lshift_scalr_intgl64bit
#define vect_128_lshift_scalr_sint32bit         vect_128_lshift_scalr_intgl32bit
#define vect_128_lshift_scalr_sint16bit         vect_128_lshift_scalr_intgl16bit
#define vect_128_lshift_scalr_sint8bit          vect_128_lshift_scalr_intgl8bit
#define vect_128_lshift_scalr_uint64bit         vect_128_lshift_scalr_intgl64bit
#define vect_128_lshift_scalr_uint32bit         vect_128_lshift_scalr_intgl32bit
#define vect_128_lshift_scalr_uint16bit         vect_128_lshift_scalr_intgl16bit
#define vect_128_lshift_scalr_uint8bit          vect_128_lshift_scalr_intgl8bit
#define _vect_128_lshift_scalr_(_memb_kind) _vect_128_native_oper(lshift_scalr, _memb_kind)


#define vect_128_rshift_logic_imm_flt64bit(a, _imm)     _mm_castsi128_pd(vect_128_rshift_logic_imm_sint64bit(a, _imm))
#define vect_128_rshift_logic_imm_flt32bit(a, _imm)     _mm_castsi128_ps(vect_128_rshift_logic_imm_sint32bit(a, _imm))
#define vect_128_rshift_logic_imm_intgl64bit        _mm_srli_epi64
#define vect_128_rshift_logic_imm_intgl32bit        _mm_srli_epi32
#define vect_128_rshift_logic_imm_intgl16bit        _mm_srli_epi16
#define vect_128_rshift_logic_imm_intgl8bit         _mm_srli_epi8
#define vect_128_rshift_logic_imm_sint64bit         vect_128_rshift_logic_imm_intgl64bit
#define vect_128_rshift_logic_imm_sint32bit         vect_128_rshift_logic_imm_intgl32bit
#define vect_128_rshift_logic_imm_sint16bit         vect_128_rshift_logic_imm_intgl16bit
#define vect_128_rshift_logic_imm_sint8bit          vect_128_rshift_logic_imm_intgl8bit
#define vect_128_rshift_logic_imm_uint64bit         vect_128_rshift_logic_imm_intgl64bit
#define vect_128_rshift_logic_imm_uint32bit         vect_128_rshift_logic_imm_intgl32bit
#define vect_128_rshift_logic_imm_uint16bit         vect_128_rshift_logic_imm_intgl16bit
#define vect_128_rshift_logic_imm_uint8bit          vect_128_rshift_logic_imm_intgl8bit
#define _vect_128_rshift_logic_imm_(_memb_kind)     _vect_128_native_oper(rshift_logic_imm, _memb_kind)


#define vect_128_rshift_logic_scalr_flt64bit(a, scalr_b)    _mm_castsi128_pd(vect_128_rshift_logic_scalr_sint64bit(a, scalr_b))
#define vect_128_rshift_logic_scalr_flt32bit(a, scalr_b)    _mm_castsi128_ps(vect_128_rshift_logic_scalr_sint32bit(a, scalr_b))
#define vect_128_rshift_logic_scalr_intgl64bit  _mm_srl_epi64
#define vect_128_rshift_logic_scalr_intgl32bit  _mm_srl_epi32
#define vect_128_rshift_logic_scalr_intgl16bit  _mm_srl_epi16
#define vect_128_rshift_logic_scalr_intgl8bit   _mm_srl_epi8
#define vect_128_rshift_logic_scalr_sint64bit   vect_128_rshift_logic_scalr_intgl64bit
#define vect_128_rshift_logic_scalr_sint32bit   vect_128_rshift_logic_scalr_intgl32bit
#define vect_128_rshift_logic_scalr_sint16bit   vect_128_rshift_logic_scalr_intgl16bit
#define vect_128_rshift_logic_scalr_sint8bit    vect_128_rshift_logic_scalr_intgl8bit
#define vect_128_rshift_logic_scalr_uint64bit   vect_128_rshift_logic_scalr_intgl64bit
#define vect_128_rshift_logic_scalr_uint32bit   vect_128_rshift_logic_scalr_intgl32bit
#define vect_128_rshift_logic_scalr_uint16bit   vect_128_rshift_logic_scalr_intgl16bit
#define vect_128_rshift_logic_scalr_uint8bit    vect_128_rshift_logic_scalr_intgl8bit
#define _vect_128_rshift_logic_scalr_(_memb_kind)   _vect_128_native_oper(rshift_logic_scalr, _memb_kind)


#define vect_128_rshift_arith_imm_flt64bit(a, _imm)     _mm_castsi128_pd(vect_128_rshift_arith_imm_sint64bit(a, _imm))
#define vect_128_rshift_arith_imm_flt32bit(a, _imm)     _mm_castsi128_ps(vect_128_rshift_arith_imm_sint32bit(a, _imm))
#define vect_128_rshift_arith_imm_intgl64bit             _mm_srai_epi64
#define vect_128_rshift_arith_imm_intgl32bit             _mm_srai_epi32
#define vect_128_rshift_arith_imm_intgl16bit             _mm_srai_epi16
#define vect_128_rshift_arith_imm_intgl8bit              _mm_srai_epi8
#define vect_128_rshift_arith_imm_sint64bit             vect_128_rshift_arith_imm_intgl64bit
#define vect_128_rshift_arith_imm_sint32bit             vect_128_rshift_arith_imm_intgl32bit
#define vect_128_rshift_arith_imm_sint16bit             vect_128_rshift_arith_imm_intgl16bit
#define vect_128_rshift_arith_imm_sint8bit              vect_128_rshift_arith_imm_intgl8bit
#define vect_128_rshift_arith_imm_uint64bit             vect_128_rshift_arith_imm_intgl64bit
#define vect_128_rshift_arith_imm_uint32bit             vect_128_rshift_arith_imm_intgl32bit
#define vect_128_rshift_arith_imm_uint16bit             vect_128_rshift_arith_imm_intgl16bit
#define vect_128_rshift_arith_imm_uint8bit              vect_128_rshift_arith_imm_intgl8bit
#define _vect_128_rshift_arith_imm_(_memb_kind) _vect_128_native_oper(rshift_arith_imm, _memb_kind)


#define vect_128_rshift_arith_scalr_flt64bit(a, b)   _mm_castsi128_pd(vect_128_rshift_arith_scalr_sint64bit(a, b))
#define vect_128_rshift_arith_scalr_flt32bit(a, b)   _mm_castsi128_ps(vect_128_rshift_arith_scalr_sint32bit(a, b))
#define vect_128_rshift_arith_scalr_intgl64bit              _mm_sra_epi64
#define vect_128_rshift_arith_scalr_intgl32bit              _mm_sra_epi32
#define vect_128_rshift_arith_scalr_intgl16bit              _mm_sra_epi16
#define vect_128_rshift_arith_scalr_intgl8bit               _mm_sra_epi8
#define vect_128_rshift_arith_scalr_sint64bit               vect_128_rshift_arith_scalr_intgl64bit
#define vect_128_rshift_arith_scalr_sint32bit               vect_128_rshift_arith_scalr_intgl32bit
#define vect_128_rshift_arith_scalr_sint16bit               vect_128_rshift_arith_scalr_intgl16bit
#define vect_128_rshift_arith_scalr_sint8bit                vect_128_rshift_arith_scalr_intgl8bit
#define vect_128_rshift_arith_scalr_uint64bit               vect_128_rshift_arith_scalr_intgl64bit
#define vect_128_rshift_arith_scalr_uint32bit               vect_128_rshift_arith_scalr_intgl32bit
#define vect_128_rshift_arith_scalr_uint16bit               vect_128_rshift_arith_scalr_intgl16bit
#define vect_128_rshift_arith_scalr_uint8bit                vect_128_rshift_arith_scalr_intgl8bit
#define _vect_128_rshift_arith_scalr_(_memb_kind) _vect_128_native_oper(rshift_arith_scalr, _memb_kind)


// Check: whether this are too many features?
// 1) try to either broadcast operand 0 if its a scalar, or retrive its native type
// 2) check whether operand 1 is either an (imm, scalr, vect_128)
// 3) if operand 3 is present apply tnr operator otherwise apply binary operator ...

#ifdef FAST_COMPILATION
#define vect_128_apply_bin_shift_oper(shift_oper, a, b) ({              \
    const typeof(a) _expr_a_sh_bin_ = (a);                              \
    extern const vect_128_t(_expr_a_sh_bin_, (typeof(_expr_a_sh_bin_)){0}) _t_binr_sdh;                      \
    vect_128_intgl_native_t _shftbrd_a = vect_128_broad_cast_to_native_if_scalr(_expr_a_sh_bin_, _t_binr_sdh);         \
    switch (sizeof(vect_memb_t(_t_binr_sdh))) {                                                          \
        case 8: _shftbrd_a = vect_128_ ## shift_oper ## _intgl64bit(_shftbrd_a, b); break ;   \
        case 4: _shftbrd_a = vect_128_ ## shift_oper ## _intgl32bit(_shftbrd_a, b); break ;   \
        case 2: _shftbrd_a = vect_128_ ## shift_oper ## _intgl16bit(_shftbrd_a, b); break ;   \
        case 1: _shftbrd_a = vect_128_ ## shift_oper ## _intgl8bit(_shftbrd_a, b); break ;    \
        default: {extern void invalid_operand_size(); invalid_operand_size();  break ;} \
    } (typeof(_t_binr_sdh))(typeof(vect_native(_t_binr_sdh)))_shftbrd_a; })

#define vect_128_apply_tnr_shift_oper(shift_oper, a, b, dest) ({            \
    const typeof(a) _expr_a_sh_tnr_ = (a);                                  \
    extern const vect_128_t(_expr_a_sh_tnr_, (typeof(_expr_a_sh_tnr_)){0}) __t_tnr_sh;                 \
    const vect_128_intgl_native_t _shftbrd_tnr_a = vect_128_broad_cast_to_native_if_scalr(_expr_a_sh_tnr_, __t_tnr_sh);                              \
    switch (sizeof(vect_memb_t(__t_tnr_sh))) {                                                \
        case 8: vect_set_native(dest, vect_128_ ## shift_oper ## _intgl64bit(_shftbrd_tnr_a, b)); break ;   \
        case 4: vect_set_native(dest, vect_128_ ## shift_oper ## _intgl32bit(_shftbrd_tnr_a, b)); break ;   \
        case 2: vect_set_native(dest, vect_128_ ## shift_oper ## _intgl16bit(_shftbrd_tnr_a, b)); break ;   \
        case 1: vect_set_native(dest, vect_128_ ## shift_oper ## _intgl8bit(_shftbrd_tnr_a, b)); break ;    \
        default: {extern void invalid_operand_size(); invalid_operand_size();  break ;}     \
    } dest; })


#else
#define vect_128_apply_bin_shift_oper(shift_kind, a, b)  ({         \
    extern const vect_128_t(a, (typeof(a)){0}) _41_4t;              \
    (typeof(_41_4t))vect_128_apply_oper(                            \
        shift_kind,                                                 \
        vect_memb_t(_41_4t),                                        \
        vect_128_broad_cast_to_native_if_scalr(a, _41_4t),          \
        b                                                           \
    ); })

#define vect_128_apply_tnr_shift_oper(shift_kind, a, b, dest) ({    \
    extern const vect_128_t(a, (typeof(a)){0}) _21_t;               \
    vect_128_set_native(                                            \
        dest,                                                       \
        vect_128_apply_oper(                                        \
            shift_kind,                                             \
            vect_memb_t(_21_t),                                     \
            vect_128_broad_cast_to_native_if_scalr(a, _21_t),       \
            b                                                       \
        )                                                           \
    ); })
#endif


#define vect_128_apply_bin_shift_scalr(shift_oper, a, b)    \
    vect_128_apply_bin_shift_oper(shift_oper ## _scalr, a, vect_128_broad_cast_to_native_if_scalr((long)b, vect_128_t(long)))
#define vect_128_apply_tnr_shift_scalr(shift_oper, a, b, dest)    \
    vect_128_apply_tnr_shift_oper(shift_oper ## _scalr, a, vect_128_broad_cast_to_native_if_scalr((long)b, vect_128_t(long)), dest)

// Left Shift
#define vect_128_lshift_bin_imm(args...)            vect_128_apply_bin_shift_oper(lshift_imm,   args)
#define vect_128_lshift_bin_scalr(args...)          vect_128_apply_bin_shift_scalr(lshift, args)

#define vect_128_lshift_tnr_imm(args...)            vect_128_apply_tnr_shift_oper(lshift_imm, args)
#define vect_128_lshift_tnr_scalr(args...)          vect_128_apply_tnr_shift_scalr(lshift, args)


// Logical Right Shift
#define vect_128_rshift_logic_bin_imm(args...)      vect_128_apply_bin_shift_oper(rshift_logic_imm, args)
#define vect_128_rshift_logic_bin_scalr(args...)    vect_128_apply_bin_shift_scalr(rshift_logic, args)

#define vect_128_rshift_logic_tnr_imm(args...)      vect_128_apply_tnr_shift_oper(rshift_logic_imm, args)
#define vect_128_rshift_logic_tnr_scalr(args...)    vect_128_apply_tnr_shift_scalr(rshift_logic, args)
// Arithmetic Right Shift
#define vect_128_rshift_arith_bin_imm(args...)      vect_128_apply_bin_shift_oper(rshift_arith_imm, args)
#define vect_128_rshift_arith_bin_scalr(args...)    vect_128_apply_bin_shift_scalr(rshift_arith, args)

#define vect_128_rshift_arith_tnr_imm(args...)      vect_128_apply_tnr_shift_oper(rshift_arith_imm, args)
#define vect_128_rshift_arith_tnr_scalr(args...)    vect_128_apply_tnr_shift_scalr(rshift_arith, args)


#ifdef __INTEL_COMPILER
#define vect_128_bin_oper_select_scalr_imm_oper(oper, e, args...) ( \
         (comp_expr_is_imm(e)) ? vect_128_ ## oper ## _imm (args) : vect_128_ ## oper ## _scalr(args)   \
    )

#else
#define vect_128_bin_oper_select_scalr_imm_oper(oper, e, args...)   \
    comp_select(comp_expr_is_imm(e), vect_128_ ## oper ## _imm (args), vect_128_ ## oper ## _scalr(args))
#endif

#define vect_128_select_bin_or_tnr_shift(shift_name, args...) \
    vect_128_bin_oper_select_scalr_imm_oper(shift_name, macro_arg_1(args), args)

#define vect_128_lshift_bin(args...) vect_128_select_bin_or_tnr_shift(lshift_bin, args)
#define vect_128_lshift_tnr(args...) vect_128_select_bin_or_tnr_shift(lshift_tnr, args)
#undef  vect_128_lshift
#define vect_128_lshift(args...) vect_128_bin_or_tnr(lshift, args)

#define vect_128_rshift_logic_bin(args...)  vect_128_select_bin_or_tnr_shift(rshift_logic_bin, args)
#define vect_128_rshift_logic_tnr(args...)  vect_128_select_bin_or_tnr_shift(rshift_logic_tnr, args)
#undef vect_128_rshift_logic
#define vect_128_rshift_logic(args...)  vect_128_bin_or_tnr(rshift_logic, args)

#define vect_128_rshift_arith_bin(args...)  vect_128_select_bin_or_tnr_shift(rshift_arith_bin, args)
#define vect_128_rshift_arith_tnr(args...)  vect_128_select_bin_or_tnr_shift(rshift_arith_tnr, args)
#undef vect_128_rshift_arith
#define vect_128_rshift_arith(args...)  vect_128_bin_or_tnr(rshift_arith, args)



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
#define vect_128_sign_ext_unr(args...) vect_128_unr_broad_cast_scalrs(sign_ext, args)
#define vect_128_sign_ext_bin(a, dest) vect_128_set_native( \
    dest,                                                   \
    vect_128_apply_oper(sign_ext, vect_memb_t(dest), vect_128_broad_cast_to_native_if_scalr(a, dest))\
)
#define vect_128_sign_ext(args...) vect_128_unr_or_bin(sign_ext, args)



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

#define vect_128_extrt_imm(va, imm) vect_128_apply_oper(extrt_imm, vect_memb_t(va), vect_native(va), imm)


#endif // __SSE2__


#endif // __VECT_128__
