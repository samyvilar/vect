

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



//#define FAST_COMPILATION


//#ifdef FAST_COMPILATION
vect_typedef(128, flt64bit);
vect_typedef(128, flt32bit);

vect_typedef(128, sint64bit);
vect_typedef(128, sint32bit);
vect_typedef(128, sint16bit);
vect_typedef(128, sint8bit);

vect_typedef(128, uint64bit);
vect_typedef(128, uint32bit);
vect_typedef(128, uint16bit);
vect_typedef(128, uint8bit);
//#else
//    MAP(vect_128_typedef, scalrs_names
//#endif

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * declare varying internal vect_128_t types to keep track of packed member types
 * in order to determine which intrinsic to apply (@ compile time) ...
 */

#define vect_128_t_name(_memb_name) vect_t_name(128, _memb_name)


#undef _vect_128_t
#undef vect_128_t
//#define vect_128_sel_t(expr_a, _type_a, expr_b) comp_select(expr_a, (_type_a){}, (expr_b))
//#define vect_128_default_t vect_err_memb_no_suppt

extern const vect_128_flt64bit_t vect_128_flt64bit_expr_t;
extern const vect_128_flt32bit_t vect_128_flt32bit_expr_t;

extern const vect_128_sint64bit_t vect_128_sint64bit_expr_t;
extern const vect_128_sint32bit_t vect_128_sint32bit_expr_t;
extern const vect_128_sint16bit_t vect_128_sint16bit_expr_t;
extern const vect_128_sint8bit_t  vect_128_sint8bit_expr_t;

extern const vect_128_uint64bit_t vect_128_uint64bit_expr_t;
extern const vect_128_uint32bit_t vect_128_uint32bit_expr_t;
extern const vect_128_uint16bit_t vect_128_uint16bit_expr_t;
extern const vect_128_uint8bit_t  vect_128_uint8bit_expr_t;

#define _vect_128_t(_memb_name) vect_128_ ## _memb_name ## _t

//#ifdef FAST_COMPILATION
#define vect_128_t(args...) typeof(         \
    scalr_switch(                           \
        macro_arg_0(args),                  \
        vect_128_flt64bit_expr_t,           \
        vect_128_flt32bit_expr_t,           \
        vect_128_sint64bit_expr_t,          \
        vect_128_sint32bit_expr_t,          \
        vect_128_sint16bit_expr_t,          \
        vect_128_sint8bit_expr_t,           \
        vect_128_uint64bit_expr_t,          \
        vect_128_uint32bit_expr_t,          \
        vect_128_uint16bit_expr_t,          \
        vect_128_uint8bit_expr_t,           \
        (macro_arg_1(args, (void)0))        \
      )                                     \
    )
//#define vect_128_t(args...) typeof(                      \
///*      ^^^^^^^^^^ returns an internal vect_128_t type representing
// *                   packed typeof(arg_0) if there is no support than
// *                   either return typeof(arg_1) if giving
// *                   or emit compilation error
// */                                                      \
//    macro_apply(                                         \
//        scalr_switch,                                    \
//        macro_arg_0(args),                               \
//        MAP_LIST(_vect_128_expr, scalrs_names),          \
//        (macro_arg_1(args, (void)0))                     \
//      )                                                  \
//    )


#define vect_128_intrs_name(_kind, _memb_name) vect_128_ ## _kind ## _ ##  _memb_name
//      ^^^^^^^^^^^^^^^^^^^ returns the intrinsic macro name for vect_128 holding packed
//                          _memb_name(flt64bit, flt32bit, uint64bit ....)


#define vect_128_set_native(_intrnl_v, expr) ({vect_set_native(_intrnl_v, expr); _intrnl_v;})

#define _vect_128_native_oper(oper, _memb_kind)     vect_128_ ## oper ## _ ## _memb_kind macro_cons_parens

typedef union {} unable_to_detemine_type_t;
extern void vect_128_unable_to_determine_type(unable_to_detemine_type_t _, ...);

#define vect_128_apply_oper(oper, scalr_expr_t, params...)  \
    scalr_switch(                                           \
        scalr_expr_t,                                       \
        vect_128_ ## oper ## _ ## flt64bit,                 \
        vect_128_ ## oper ## _ ## flt32bit,                 \
        vect_128_ ## oper ## _ ## sint64bit,                \
        vect_128_ ## oper ## _ ## sint32bit,                \
        vect_128_ ## oper ## _ ## sint16bit,                \
        vect_128_ ## oper ## _ ## sint8bit,                 \
        vect_128_ ## oper ## _ ## uint64bit,                \
        vect_128_ ## oper ## _ ## uint32bit,                \
        vect_128_ ## oper ## _ ## uint16bit,                \
        vect_128_ ## oper ## _ ## uint8bit,                 \
        vect_128_unable_to_determine_type                   \
     )(params)

/* @@TODO: check if this indeed will speed up the compilation process ....  ************/
// some operations (load*, store*, xor, or, and) are type oblivious so we can speed up compilation
// by not checking for the type at all, the compiler will emit error if they are inappropriate...
#define vect_128_apply_oblvs_scalr_oper(oper, _, params...)  vect_128_ ## oper ## _scalr_f(params)

/*extern const typeof(scalr_expr_t) _exp_sing_t;*/
// some operations (add, sub, mullo) are sign oblivous
// so we can speed up compilation by only checking for flt and intgl types, for the intgl type we can use their size
#define vect_128_apply_oblvs_sign_oper(oper, scalr_expr_t, params...)   \
    scalr_switch_flt_or_intgl_byte_sizes(       \
        scalr_expr_t,                           \
        vect_128_ ## oper ## _flt64bit_f,       \
        vect_128_ ## oper ## _flt32bit_f,       \
        vect_128_ ## oper ## _intgl64bit_f,     \
        vect_128_ ## oper ## _intgl32bit_f,     \
        vect_128_ ## oper ## _intgl16bit_f,     \
        vect_128_ ## oper ## _intgl8bit_f,      \
        vect_128_unable_to_determine_type       \
    )(params)
/************************************************************************************/

#ifdef __INTEL_COMPILER // icc doesn't support __nodebug__
#define vect_128_intrs_signt_attrs  __attribute__((__always_inline__))
#else
#define vect_128_intrs_signt_attrs  __attribute__((__always_inline__, __nodebug__))
#endif

#define vect_128_intrs_signt(ret_t) static __inline__ ret_t vect_128_intrs_signt_attrs

vect_128_intrs_signt(__m128d) vect_128_to_native_flt64bit(vect_128_flt64bit_t __a)   {return vect_native(__a);}
vect_128_intrs_signt(__m128)  vect_128_to_native_flt32bit(vect_128_flt32bit_t __a)   {return vect_native(__a);}

#define vect_128_to_native_intgl_tmpl(memb_name) \
    vect_128_intrs_signt(__m128i) vect_128_to_native_ ## memb_name(vect_128_ ## memb_name ## _t __a) {return vect_native(__a);}

vect_128_to_native_intgl_tmpl(sint64bit)
vect_128_to_native_intgl_tmpl(sint32bit)
vect_128_to_native_intgl_tmpl(sint16bit)
vect_128_to_native_intgl_tmpl(sint8bit)

vect_128_to_native_intgl_tmpl(uint64bit)
vect_128_to_native_intgl_tmpl(uint32bit)
vect_128_to_native_intgl_tmpl(uint16bit)
vect_128_to_native_intgl_tmpl(uint8bit)


/*((((union {_type _val; typeof(expr) _e;})(expr)))._val)*/
// broadcast scalar to native 128 bit intrinsic type if _opern is an expr with a scalr type otherwise try to return the native vector
// from the internal 128 bit intrinsic type ...
#define vect_128_broad_cast_to_native_if_scalr(_opern)  ({  \
    typedef typeof(_opern) brdcst_12d_asd__;    \
    scalr_switch_flt_or_intgl_byte_sizes(       \
        brdcst_12d_asd__,                       \
        _mm_set1_pd,                            \
        _mm_set1_ps,                            \
        _mm_set1_epi64x,                        \
        _mm_set1_epi32,                         \
        _mm_set1_epi16,                         \
        _mm_set1_epi8,                          \
        (comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_flt64bit_t), vect_128_to_native_flt64bit,    \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_flt32bit_t), vect_128_to_native_flt32bit,    \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_sint64bit_t), vect_128_to_native_sint64bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_sint32bit_t), vect_128_to_native_sint32bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_sint16bit_t), vect_128_to_native_sint16bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_sint8bit_t), vect_128_to_native_sint8bit,    \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_uint64bit_t), vect_128_to_native_uint64bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_uint32bit_t), vect_128_to_native_uint32bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_uint16bit_t), vect_128_to_native_uint16bit,  \
        comp_select(comp_types_eq(brdcst_12d_asd__, vect_128_uint8bit_t), vect_128_to_native_uint8bit,    \
            vect_128_unable_to_determine_type)))))))))))) (_opern); })


#define vect_128_cast_to_flt32bit_native(expr)  ((vect_128_flt32bit_native_t)(expr))
#define vect_128_cast_to_flt64bit_native(expr)  ((vect_128_flt64bit_native_t)(expr))
#define vect_128_cast_to_intgl_native(expr)     ((vect_128_intgl_native_t)(expr))


/***** LOAD 128 bit vectors *******************************************************************************************/
// LOAD 128 bit vector on any addresses
#ifdef __SSE3__
    #define vect_128_load_scalr     _mm_lddqu_si128
#else
    #define vect_128_load_scalr     _mm_loadu_si128
#endif
// LOAD 128 bit vector on aligned addresses
#define vect_128_load_align_scalr         _mm_load_si128

#define vect_128_load_unr_(_kind, _p) ({                                \
    typedef typeof((_p)[0]) _load_oprn_t;                               \
    typedef typeof(vect_128_t(_load_oprn_t, (_load_oprn_t){0})) _ld_t;  \
    (_ld_t)(typeof(vect_native((_ld_t){})))vect_128_ ## _kind ## _scalr((__m128i const *)(_p));  \
})

#undef vect_128_load_align
#undef vect_128_load
#define vect_128_load_align(_p)         vect_128_load_unr_(load_align, _p)
#define vect_128_load(_p)               vect_128_load_unr_(load, _p)

/***** STORE 128 bit vectors *******************************************************************************************/    
// store on aligned addrs
#define vect_128_store_align_scalr _mm_store_si128
#define vect_128_store_scalr       _mm_storeu_si128
#define vect_128_store_(_kind, _p, _v)  vect_128_ ## _kind ## _scalr((__m128i *)(_p), (__m128i)vect_native(_v))

#undef  vect_128_store_align
#undef  vect_128_store
#define vect_128_store_align(_p, _v) vect_128_store_(store_align, _p, _v)
#define vect_128_store(_p, _v)       vect_128_store_(store, _p, _v)
                    

/***** SET each component of a vector from most signf to least ....   ************************************/
#define vect_128_set_flt64bit(args...)      _mm_set_pd     (macro_select_args(2, args))
#define vect_128_set_flt32bit(args...)      _mm_set_ps     (macro_select_args(4, args))
#define vect_128_set_intgl64bit(args...)    _mm_set_epi64x (macro_select_args(2, args))
#define vect_128_set_intgl32bit(args...)    _mm_set_epi32  (macro_select_args(4, args))
#define vect_128_set_intgl16bit(args...)    _mm_set_epi16  (macro_select_args(8, args))
#define vect_128_set_intgl8bit(args...)     _mm_set_epi8   (macro_select_args(16, args))

#define vect_128_set(exprs...) ({                       \
    typedef typeof(macro_arg_0(exprs)) _expr_0_t;  \
    (vect_128_t(_expr_0_t))scalr_switch_flt_or_intgl_byte_sizes(    \
        _expr_0_t,                                                  \
        vect_128_set_flt64bit(exprs, macro_comma_delim_16(0)),      \
        vect_128_set_flt32bit(exprs, macro_comma_delim_16(0)),      \
        vect_128_set_intgl64bit(exprs, macro_comma_delim_16(0)),    \
        vect_128_set_intgl32bit(exprs, macro_comma_delim_16(0)),    \
        vect_128_set_intgl16bit(exprs, macro_comma_delim_16(0)),    \
        vect_128_set_intgl8bit(exprs, macro_comma_delim_16(0)),    \
        vect_128_unable_to_determine_type ); })

/*** EXTRACT a component *******************************************************************************/
#ifndef __SSE4_1__
    // _mm_cvtsi128_si64x 1x(2, 0)
    // _mm_srli_si128 !!_imm x(1, 0.5)
    // (2 - 3) cycles ...
    vect_128_intrs_signt(sint_bit_t(64)) _mm_extract_epi64(__m128i a, int _imm)  {
        return _mm_cvtsi128_si64((_imm & 1) ? _mm_srli_si128(a, 8) : a);
    }

    // _mm_cvtsi128_si32: 1x(2, 0.5)
    // _mm_srli_si128 !!_imm x (1, 0.5)
    // (2 - 3) cycles ...
    vect_128_intrs_signt(sint_bit_t(32)) _mm_extract_epi32(__m128i a, int _imm) {
        switch (_imm & 0b11) {
            case 3: return _mm_cvtsi128_si32(_mm_srli_si128(a, 12));
            case 2: return _mm_cvtsi128_si32(_mm_srli_si128(a, 8));
            case 1: return _mm_cvtsi128_si32(_mm_srli_si128(a, 4));
            case 0: return _mm_cvtsi128_si32(a);
//            default: {extern void error_invalid_index(); error_invalid_index(); }
        }
        return 0;
    }

    vect_128_intrs_signt(flt_bit_t(32)) _mm_extract_ps(__m128 a, int _imm) {
        switch (_imm) {
            case 3: return _mm_cvtss_f32(_mm_srli_si128(a, 12));
            case 2: return _mm_cvtss_f32(_mm_srli_si128(a, 8));
            case 1: return _mm_cvtss_f32(_mm_srli_si128(a, 4));
            case 0: return _mm_cvtss_f32(a);
//            default: {extern void error_invalid_index(); error_invalid_index(); }
        }
        return 0;
    }

#ifdef __SSSE3__
    // dst[7:0] := (a[127:0] >> (imm[3:0] * 8))[7:0] // 2-3 cycles
    // _mm_extract_epi16 1x(3 [2.5], 1) (SSSE3)
    // _mm_cvtsi128_si32 1x(2, 1)
    // _mm_shuffle_epi8 1x(1, 0.5)
    // about 4 cycles ... (assuming _mm_set_epi8 is 0)
    vect_128_intrs_signt(sint_bit_t(8)) _mm_extract_epi8(__m128i a, int _imm)  {
        switch (_imm & 0b1111) {
            case 8 ... 15:
                return _mm_extract_epi16(
                    _mm_shuffle_epi8(
                        a,
                        _mm_set_epi8(
                            0x80, 15, 0x80, 14, 0x80, 13, 0x80, 12,
                            0x80, 11, 0x80, 10, 0x80, 9,  0x80, 8
                        )
                    ),
                    _imm - 8
                ) & 0xFF;
            case 1 ... 7:
                return _mm_extract_epi16(
                    _mm_shuffle_epi8(
                        a,
                        _mm_set_epi8(
                            0x80, 7, 0x80, 6, 0x80, 5, 0x80, 4,
                            0x80, 3, 0x80, 2, 0x80, 1, 0x80, 0
                        )
                    ),
                    _imm
                ) & 0xFF;
            case 0: return _mm_cvtsi128_si32(a);
        }
        return 0;
//        return
//            comp_select((_imm & 0b1111) == 0, (_mm_cvtsi128_si32(a) & 0xFF), // 3 cycles ...
//            comp_select((_imm & 0b1111) < 8,
//                _mm_extract_epi16(
//                    _mm_shuffle_epi8(a, _mm_set_epi8(0x80, 7, 0x80, 6, 0x80, 5, 0x80, 4, 0x80, 3, 0x80, 2, 0x80, 1, 0x80, 0)),
//                    _imm
//                 ),
//            comp_select((_imm & 0b1111) < 16,
//                _mm_extract_epi16(
//                    _mm_shuffle_epi8(a, _mm_set_epi8(0x80, 15, 0x80, 14, 0x80, 13, 0x80, 12, 0x80, 11, 0x80, 10, 0x80, 9,  0x80, 8)),
//                    _imm - 8
//                ),
//            (void)0
//        )));
    }
#else
    // _mm_cvtsi128_si32:   (2, 0.5)
    // _mm_extract_epi16    (3, 0.5)
    // _mm_unpack*_epi8:    (1, 0.5)
    // _mm_setzero_si128:   (1, 0.33)
    // (about 5 cycles)
    vect_128_intrs_signt(sint_bit_t(8)) _mm_extract_epi8(__m128i a, int _imm)  {
        return (_imm & 0b1111)
                ? (_mm_cvtsi128_si32(_mm_srli_si128(a, _imm & 0b1111)) & 0xFF) // 4 cycles ...
                : (_mm_cvtsi128_si32(a) & 0xFF); // 3 cycles ...
//            comp_select(_imm == 0, (_mm_cvtsi128_si32(a) & 0xFF) // 3 cycles ...
//            (_mm_cvtsi128_si32(_mm_srli_si128(a, _imm & 0b1111)) & 0xFF)
//            // ^^^^^ _mm_cvtsi128_si32: 2 + _mm_srli_si128: 1 + (and r32, r32): 1 == (4 cycles)
//        );
            //comp_select(_imm < 8,   _mm_extract_epi16(_mm_unpacklo_epi8(a, _mm_setzero_si128()), _imm), // 5 cycles ...
            //comp_select(_imm < 16,  _mm_extract_epi16(_mm_unpackhi_epi8(a, _mm_setzero_si128()), _imm - 8), // 5 cycles ..
    }
#endif // __SSSE3__ extract_epi8

#endif

vect_128_intrs_signt(uint_bit_t(64)) _mm_extract_epu64(__m128i a, int _imm) {return (uint_bit_t(64))_mm_extract_epi64(a, _imm);}
vect_128_intrs_signt(uint_bit_t(32)) _mm_extract_epu32(__m128i a, int _imm) {return (uint_bit_t(32))_mm_extract_epi32(a, _imm);}
vect_128_intrs_signt(uint_bit_t(16)) _mm_extract_epu16(__m128i a, int _imm) {return (uint_bit_t(16))_mm_extract_epi16(a, _imm);}
vect_128_intrs_signt(uint_bit_t(8))  _mm_extract_epu8(__m128i a, int _imm) {return (uint_bit_t(8))_mm_extract_epi8(a, _imm);}


// etract member from vectors using an compile time index literal
#define vect_128_extrt_imm_flt64bit     _mm_extract_pd
#define vect_128_extrt_imm_flt32bit     _mm_extract_ps
#define vect_128_extrt_imm_sint64bit    _mm_extract_epi64
#define vect_128_extrt_imm_sint32bit    _mm_extract_epi32

// _mm_extract_epi16 returns an int which can play havoc during bit operations ...
vect_128_intrs_signt(sint_bit_t(16)) vect_128_extrt_imm_sint16bit(__m128i a, int _imm) {
    return (sint_bit_t(16))_mm_extract_epi16(a, _imm);
}

#define vect_128_extrt_imm_sint8bit     _mm_extract_epi8
#define vect_128_extrt_imm_uint64bit    _mm_extract_epu64
#define vect_128_extrt_imm_uint32bit    _mm_extract_epu32
#define vect_128_extrt_imm_uint16bit    _mm_extract_epu16
#define vect_128_extrt_imm_uint8bit     _mm_extract_epu8
#define vect_128_extrt_imm(va, imm)     vect_128_apply_oper(extrt_imm, vect_memb_t(va), vect_native(va), imm)


/*****  UNARY vector operators  ****************************************************************************/
// broadcast expr into a vector type duplicating as many times as required ...
#define vect_128_broad_cast_flt64bit_f     _mm_set1_pd
#define vect_128_broad_cast_flt32bit_f     _mm_set1_ps
#define vect_128_broad_cast_intgl64bit_f   _mm_set1_epi64x
#define vect_128_broad_cast_intgl32bit_f   _mm_set1_epi32
#define vect_128_broad_cast_intgl16bit_f   _mm_set1_epi16
#define vect_128_broad_cast_intgl8bit_f    _mm_set1_epi8

#undef vect_128_broad_cast
#define vect_128_broad_cast(expr) ((vect_128_t(expr))(vect_128_apply_oblvs_sign_oper(broad_cast, expr, expr)))


/** BINARY operators *****************************************************************************/
#define vect_128_xor_scalr_f        _mm_xor_si128
#define vect_128_or_scalr_f         _mm_or_si128
#define vect_128_and_scalr_f        _mm_and_si128

// add two 128 bit vectors
#define vect_128_add_flt64bit_f     _mm_add_pd
#define vect_128_add_flt32bit_f     _mm_add_ps
#define vect_128_add_intgl64bit_f   _mm_add_epi64
#define vect_128_add_intgl32bit_f   _mm_add_epi32
#define vect_128_add_intgl16bit_f   _mm_add_epi16
#define vect_128_add_intgl8bit_f    _mm_add_epi8

// sub two vectors
#define vect_128_sub_flt64bit_f     _mm_sub_pd
#define vect_128_sub_flt32bit_f     _mm_sub_ps
#define vect_128_sub_intgl64bit_f   _mm_sub_epi64
#define vect_128_sub_intgl32bit_f   _mm_sub_epi32
#define vect_128_sub_intgl16bit_f   _mm_sub_epi16
#define vect_128_sub_intgl8bit_f    _mm_sub_epi8

// mul two vectors
/*
    SSE doesn't support 64 bit multiplication, but it can be emulated
     assume a, b are 64 bit numbers and high/low are their corresponding bits where low has its upper zero out
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
vect_128_intrs_signt(__m128i) _mm_mullo_epi64(__m128i a, __m128i b) {
    return _mm_add_epi64(
        _mm_mul_epu32(a, b),
        _mm_slli_epi64(
            _mm_add_epi64(
                _mm_mul_epu32(b, _mm_shuffle_epi32(a, _MM_SHUFFLE(2, 3, 0, 1))),
                _mm_mul_epu32(a, _mm_shuffle_epi32(b, _MM_SHUFFLE(2, 3, 0, 1)))
            ),
            32
        )
    );
}
#define _mm_mullo_epi64  _mm_mullo_epi64
#endif


#if !defined(__SSE4_1__) &&  !defined(_mm_mullo_epi32)
// multiplies the the low and high 32 bits each creating a 64 bit unsigned result ...
// _mm_unpacklo_epi32:  1x(1, 0.5)
// _mm_shuffle_epi32:   2x(1, 0.5)
// _mm_mul_epu32:       2x(3, 1)
// _mm_srli_si128:      2x(1, 0.5)
// about 10 cycles ...
vect_128_intrs_signt(__m128i) _mm_mullo_epi32(__m128i a, __m128i b) {
    return _mm_unpacklo_epi32(
        _mm_shuffle_epi32(_mm_mul_epu32(a, b), _MM_SHUFFLE(0,0,2,0)),
        _mm_shuffle_epi32(_mm_mul_epu32(_mm_srli_si128(a, 4), _mm_srli_si128(b, 4)), _MM_SHUFFLE(0,0,2,0))
    );
}
#define _mm_mullo_epi32 _mm_mullo_epi32
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


#ifdef __SSE4_1__
vect_128_intrs_signt(__m128i) _mm_mullo_epi8_sse4_1(__m128i a, __m128i b) { // 13 cycles ...
    return _mm_packs_epi16(
        _mm_mullo_epi16(_mm_cvtepi8_epi16(a), _mm_cvtepi8_epi16(b)), // [0] - [7]
        _mm_mullo_epi16(_mm_cvtepi8_epi16(_mm_srli_si128(a, 8)), _mm_cvtepi8_epi16(_mm_srli_si128(b, 8))) // [8 - 15]
    );
}
#endif

vect_128_intrs_signt(__m128i) _mm_mullo_epi8_ssse3(__m128i a, __m128i b) {
    return _mm_or_si128(
      _mm_shuffle_epi8(
          _mm_mullo_epi16(
              _mm_unpackhi_epi8(a, _mm_setzero_si128()),
              _mm_unpackhi_epi8(b, _mm_setzero_si128())
          ),
          _mm_set_epi8(
              14,   12,   10,   8,    6,    4,    2,    0,
              0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
          )
      ),
      _mm_shuffle_epi8(
          _mm_mullo_epi16(
              vect_128_cvt_uint8bit_to_uint16bit(a),
              vect_128_cvt_uint8bit_to_uint16bit(b)
         ),
         _mm_set_epi8(
              0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
              14,   12,   10,   8,    6,    4,    2,    0
         )
     )
  );
}

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
vect_128_intrs_signt(__m128i) _mm_mullo_epi8_sse2(__m128i __a, __m128i __b) {
    return _mm_or_si128(
        _mm_slli_epi16(_mm_mullo_epi16(_mm_srli_epi16(__a, 8), _mm_srli_epi16(__b, 8)), 8),
        _mm_and_si128(
            _mm_mullo_epi16(
                _mm_and_si128(__a, _mm_set_epi8(0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF)),
                _mm_and_si128(__b, _mm_set_epi8(0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF))
            ),
            _mm_set_epi8(0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF)
        )
    );
}

#ifndef _mm_mullo_epi8
#ifdef __SSE4_1__
    #define _mm_mullo_epi8  _mm_mullo_epi8_sse4_1
#elif defined(__SSSE3__)
    #define _mm_mullo_epi8  _mm_mullo_epi8_ssse3
#else
    #define _mm_mullo_epi8 _mm_mullo_epi8_sse2
#endif
#endif


    // mul two vectors
#define vect_128_mul_flt64bit_f         _mm_mul_pd
#define vect_128_mul_flt32bit_f         _mm_mul_ps
#define vect_128_mul_intgl64bit_f       _mm_mullo_epi64
#define vect_128_mul_intgl32bit_f       _mm_mullo_epi32
#define vect_128_mul_intgl16bit_f       _mm_mullo_epi16
#define vect_128_mul_intgl8bit_f        _mm_mullo_epi8

/************************************************************************************************/

#ifndef __SSE4_1__
    vect_128_intrs_signt(__m128i) _mm_cvtepi16_epi32(__m128i x) { // 2 cycles ...
        return _mm_srai_epi32(_mm_unpacklo_epi16(x, x), 16);
    }

    #define _mm_cvtepu16_epi32(a) _mm_unpacklo_epi16(a, _mm_setzero_si128()) // 2 cycles ..

    vect_128_intrs_signt(__m128i) _mm_cvtepu8_epi32(__m128i a) { // 3 cycles ...
        a = _mm_unpacklo_epi8(a, a); // a0, a0, a1, a1, a2, a2, a3, a3, ....
        return _mm_srli_epi32(_mm_unpacklo_epi16(a, a), 24);
    }

    vect_128_intrs_signt(__m128i) _mm_cvtepi8_epi32(__m128i a) { // 3 cycles ...
        a = _mm_unpacklo_epi8(a, a); // a0, a0, a1, a1, a2, a2, a3, a3, ....
        return _mm_srai_epi32(_mm_unpacklo_epi16(a, a), 24);
    }


//    #endif
#endif

#ifndef __SSE4_1__
static inline int _mm_extract_epi32(__m128i, int);
#endif

// div two vectors
// method 1) unpack each 32 bit number divide and repack ...
//      unpacking the components would take 4 cycles for those at index 0,
//      18 cycles for the rest (22 cycles just to unpack all 8)
//      div r32                  22/11      14/5       17/1 (http://akuvian.org/src/mubench_results.txt)
//      each division would take on avg 18 cycles (72 cycles to divide all 4 components)
//      repacking each component is 2 cycles for a total of 16 cycles ...
//      total: (22 + 72 + 16) == ~110 cycles ....
vect_128_intrs_signt(__m128i) _mm_unpack_div_epi32(__m128i a, __m128i b) {
    return _mm_set_epi32(
        _mm_extract_epi32(a, 3)/_mm_extract_epi32(b, 3),
        _mm_extract_epi32(a, 2)/_mm_extract_epi32(b, 2),
        _mm_extract_epi32(a, 1)/_mm_extract_epi32(b, 1),
        _mm_extract_epi32(a, 0)/_mm_extract_epi32(b, 0)
    );
}


vect_128_intrs_signt(__m128i) _mm_invert_si128(__m128i a) { // 2 cycles ...
    return _mm_xor_si128(a, _mm_cmpeq_epi32(a, a));
}

vect_128_intrs_signt(__m128) _mm_abs_ps(__m128 a) {
    return _mm_xor_ps(a, _mm_set1_ps(-1.0f));
}

vect_128_intrs_signt(__m128i) _mm_cmpge_epi32(__m128i a, __m128i b) { // 3 cycles ...
    return _mm_invert_si128(_mm_cmplt_epi32(a, b)); // a >= b == ~(a < b)
}


vect_128_intrs_signt(__m128i) _mm_div_epi64(__m128i a, __m128i b) {
    return _mm_set_epi64x(
        _mm_extract_epi64(a, 1)/_mm_extract_epi64(b, 1),
        _mm_extract_epi64(a, 0)/_mm_extract_epi64(b, 1)
    );
}

vect_128_intrs_signt(__m128i) _mm_div_epu64(__m128i a, __m128i b) {
    return _mm_set_epi64x(
        (uint_bit_t(64))_mm_extract_epi64(a, 1)/(uint_bit_t(64))_mm_extract_epi64(b, 1),
        (uint_bit_t(64))_mm_extract_epi64(a, 0)/(uint_bit_t(64))_mm_extract_epi64(b, 0)
    );
}


vect_128_intrs_signt(__m128i) _mm_div_epi32(__m128i a, __m128i b) {
    return _mm_set_epi32( // this seems to be the fastest/safest method converting to floats give inaccurate results when a|b >= 2**24
        _mm_extract_epi32(a, 3)/_mm_extract_epi32(b, 3),
        _mm_extract_epi32(a, 2)/_mm_extract_epi32(b, 2),
        _mm_extract_epi32(a, 1)/_mm_extract_epi32(b, 1),
        _mm_extract_epi32(a, 0)/_mm_extract_epi32(b, 0)
    );
}

vect_128_intrs_signt(__m128i) _mm_div_epu32(__m128i a, __m128i b) {
    return _mm_set_epi32(
        (uint_bit_t(32))_mm_extract_epi32(a, 3)/(uint_bit_t(32))_mm_extract_epi32(b, 3),
        (uint_bit_t(32))_mm_extract_epi32(a, 2)/(uint_bit_t(32))_mm_extract_epi32(b, 2),
        (uint_bit_t(32))_mm_extract_epi32(a, 1)/(uint_bit_t(32))_mm_extract_epi32(b, 1),
        (uint_bit_t(32))_mm_extract_epi32(a, 0)/(uint_bit_t(32))_mm_extract_epi32(b, 0)
    );
}



// method 1)
//    unpack all 16 shorts 3*16 = 48 cycles
//      dividing each 16 bit would take on avg 22 cycles ... (8*22) = 176
//    repacking each component is 2 cycles 2*16 = 32
//      (48 + 176 + 32) = ~256 cycles total ...
vect_128_intrs_signt(__m128i) _mm_unpack_div_epi16(__m128i a, __m128i b) {
    return _mm_set_epi16(
        (short)_mm_extract_epi16(a, 7)/(short)_mm_extract_epi16(b, 7),
        (short)_mm_extract_epi16(a, 6)/(short)_mm_extract_epi16(b, 6),
        (short)_mm_extract_epi16(a, 5)/(short)_mm_extract_epi16(b, 5),
        (short)_mm_extract_epi16(a, 4)/(short)_mm_extract_epi16(b, 4),
        (short)_mm_extract_epi16(a, 3)/(short)_mm_extract_epi16(b, 3),
        (short)_mm_extract_epi16(a, 2)/(short)_mm_extract_epi16(b, 2),
        (short)_mm_extract_epi16(a, 1)/(short)_mm_extract_epi16(b, 1),
        (short)_mm_extract_epi16(a, 0)/(short)_mm_extract_epi16(b, 0)
    );
}

// method 2)
//      convert to floats divide convert back to shorts ...
//      _mm_cvtepi16_epi32  4x(1, 0.5) // if SSE4.1 else 4x(2, 1)
//      _mm_cvtepi32_ps     4x(3, 1)
//      _mm_div_ps          2x(14, 14)
//      _mm_cvttps_epi32    2x(3, 1)
//      _mm_srli_si128      2x(1, 0.5)
//      _mm_packs_epi32     1x(1, 0.5)
//          4 + 12 + 28 + 6 + 2 + 1 = w/ SSE 4.1 53 cycles +8 without sse4.1
// note that _mm_set_epi8 with -O0 produces very BAD CODE over 20 cycles!!
vect_128_intrs_signt(__m128i) _mm_div_epi16(__m128i a, __m128i b) {
    // gcc -msse4.1 -Ofast: 4.8219s, gcc a.c -Ofast: 4.8657s // icc SVML: 5.6750s
    return _mm_packs_epi32(
        _mm_cvttps_epi32(
            _mm_div_ps(
                _mm_cvtepi32_ps(_mm_cvtepi16_epi32(a)),
                _mm_cvtepi32_ps(_mm_cvtepi16_epi32(b))
            )
        ),
        _mm_cvttps_epi32(
            _mm_div_ps(
                _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm_srli_si128(a, 8))),
                _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm_srli_si128(b, 8)))
            )
        )
    );
}

vect_128_intrs_signt(__m128i) _mm_div_epu16(__m128i a, __m128i b) {

#ifdef __SSE4_1__
    return _mm_packus_epi32(
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(_mm_cvtepu16_epi32(a)), _mm_cvtepi32_ps(_mm_cvtepu16_epi32(b)))),
        _mm_cvttps_epi32(
            _mm_div_ps(
                _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_srli_si128(a, 8))),
                _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_srli_si128(b, 8)))
            )
        )
    );
#else
    return _mm_or_si128(
        _mm_cvttps_epi32(_mm_div_ps(
             _mm_cvtepi32_ps(_mm_srli_epi32(_mm_slli_epi32(a, 16), 16)),
             _mm_cvtepi32_ps(_mm_srli_epi32(_mm_slli_epi32(b, 16), 16))
         )),
          _mm_slli_epi32(
            _mm_cvttps_epi32(
                _mm_div_ps(_mm_cvtepi32_ps(_mm_srli_epi32(a, 16)), _mm_cvtepi32_ps(_mm_srli_epi32(b, 16)))
            ),
            16
        )
    );

//#elif defined(__SSSE3__)
//    return _mm_unpacklo_epi64(
//        _mm_shuffle_epi8(
//            _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(_mm_cvtepu16_epi32(a)), _mm_cvtepi32_ps(_mm_cvtepu16_epi32(b)))),
//            _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 13, 12, 9, 8, 5, 4, 1, 0)
//        ),
//        _mm_shuffle_epi8(
//            _mm_cvttps_epi32(
//                _mm_div_ps(
//                    _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_srli_si128(a, 8))),
//                    _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm_srli_si128(b, 8)))
//                )
//            ),
//            _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 13, 12, 9, 8, 5, 4, 1, 0)
//        )
//    );

#endif
}




#ifndef __SSSE3__
vect_128_intrs_signt(__m128i) _mm_abs_epi8(__m128i a) { // 5 cycles ...
    return _mm_add_epi8(
        _mm_xor_si128(_mm_cmplt_epi8(a, _mm_setzero_si128()), a),
        _mm_and_si128(_mm_cmplt_epi8(a, _mm_setzero_si128()), _mm_set1_epi8(1))
    );
}
#endif

#ifndef __SSE4_1__
vect_128_intrs_signt(sint_bit_t(8)) _mm_extract_epi8(__m128i a, int _imm);
#endif
// method 1)
//  unpack all 32 components (total: 64 cycles), divide each (total: 176 cycles), repack vector (total: 64 cycles) ~304 cycles
vect_128_intrs_signt(__m128i) _mm_unpack_div_epi8(__m128i a, __m128i b) {
#define _div_char_vect_comp(a, b, index) ((char)_mm_extract_epi8(a, index)/(char)_mm_extract_epi8(b, index))
    return _mm_set_epi8( // 29.561s, , icc 29.154s
        _div_char_vect_comp(a, b, 15),
        _div_char_vect_comp(a, b, 14),
        _div_char_vect_comp(a, b, 13),
        _div_char_vect_comp(a, b, 12),
        _div_char_vect_comp(a, b, 11),
        _div_char_vect_comp(a, b, 10),
        _div_char_vect_comp(a, b, 9),
        _div_char_vect_comp(a, b, 8),
        _div_char_vect_comp(a, b, 7),
        _div_char_vect_comp(a, b, 6),
        _div_char_vect_comp(a, b, 5),
        _div_char_vect_comp(a, b, 4),
        _div_char_vect_comp(a, b, 3),
        _div_char_vect_comp(a, b, 2),
        _div_char_vect_comp(a, b, 1),
        _div_char_vect_comp(a, b, 0)
    );
}

#ifndef __SSSE3__
// negate a if b is negative, zero out if b is zero, do nothing if b is positive non-zero
// 6-8 cycles ...
vect_128_intrs_signt(__m128i) _mm_sign_epi8(__m128i a, __m128i b) {
    return _mm_andnot_si128(
        _mm_cmpeq_epi8(b, _mm_setzero_si128()),
        _mm_add_epi8(_mm_xor_si128(a, _mm_cmplt_epi8(b, _mm_setzero_si128())), _mm_srli_epi8(b, 7))
    );
}
#endif
// method 2)
//  convert to floats divide convert back ...

// _mm_cvtepi8_epi32: 8x(1, 0.5) w/ SSE4.1 otherwise (2, 1)
// _mm_cvtepi32_ps:   8x(3, 1)
// _mm_div_ps:        4x(14, 14)
// _mm_rcp_ps:        (5, 1) or (3, 2)
// _mm_cvttps_epi32:  4x(3, 1)
// _mm_srli_si128:    6x(1, 0.5)
// _mm_shuffle_epi8:  4x(1, 1)
// _mm_set_epi8:      4x(2, 1)
// _mm_or_si128:      3x(1, 0.33)
//      8 + 24 + 56 + 12 + 6 + 4 + 8 + 3 ~121 cycles ...
vect_128_intrs_signt(__m128i) _mm_div_epi8(__m128i a, __m128i b) {
#define _mm_div_low_4_bytes(a, b) \
    _mm_cvttps_epi32(_mm_mul_ps(_mm_cvtepi32_ps(_mm_cvtepu8_epi32(a)), _mm_rcp_ps(_mm_cvtepi32_ps(_mm_cvtepu8_epi32(b)))   \
        )) // 21 cycles ...

//    $ icc a.c -Ofast -msse4.1   -Wfatal-errors  && ./a.out total time 14.6392s
    register __m128i
        abs_a = _mm_abs_epi8(a), // 1
        abs_b = _mm_abs_epi8(b), // 1
        res = // 20.863, //icc a.c -Ofast -msse4.1   -Wfatal-errors  && ./a.out total time 14.6702s
        _mm_packs_epi16(
            _mm_packs_epi32(
                _mm_div_low_4_bytes(abs_a, abs_b),
                _mm_div_low_4_bytes(_mm_srli_si128(abs_a, 4), _mm_srli_si128(abs_b, 4))
            ),
            _mm_packs_epi32(
                _mm_div_low_4_bytes(_mm_srli_si128(abs_a, 8), _mm_srli_si128(abs_b, 8)),
                _mm_div_low_4_bytes(_mm_srli_si128(abs_a, 12), _mm_srli_si128(abs_b, 12))
            )
        ); // 84 + 9 = 93 cycles ...

#ifdef __SSSE3__
    return _mm_sign_epi8(_mm_sign_epi8( //  14.2664s
        _mm_sub_epi8( // (corrections due to recp approx, 17 cycles ...) add 1 if the remainder (a*q) equals b
            res,
            _mm_cmpeq_epi8(_mm_sub_epi8(abs_a, _mm_mullo_epi8(abs_b, res)), abs_b)
         ),
        b), a); // calculate sign, 2 cycles ...
#else
    // calculate sign of quotient // 3-4 cycles
    __m128i sign = _mm_xor_si128(_mm_cmplt_epi8(a, _mm_setzero_si128()), _mm_cmplt_epi8(b, _mm_setzero_si128()));
    // apply sign using twos complement to those results, 3 cycles ..
    return _mm_add_epi8( // 14.5480s
        _mm_xor_si128(
            sign,
            _mm_add_epi8( // add 1 if the remainder (a*q) equals b
                _mm_and_si128(
                    _mm_cmpeq_epi8(_mm_sub_epi8(abs_a, _mm_mullo_epi8(abs_b, res)), abs_b),
                    _mm_set1_epi8(1)
                ),
                res
            )
        ),
        _mm_and_si128(sign, _mm_set1_epi8(1))
    );
#endif
}


vect_128_intrs_signt(__m128i) _mm_div_epu8(__m128i a, __m128i b) {
    register
    __m128i
        res =
        _mm_packus_epi16(
            _mm_packs_epi32(
                _mm_div_low_4_bytes(a, b),
                _mm_div_low_4_bytes(_mm_srli_si128(a, 4), _mm_srli_si128(b, 4))
            ),
            _mm_packs_epi32(
                _mm_div_low_4_bytes(_mm_srli_si128(a, 8), _mm_srli_si128(b, 8)),
                _mm_div_low_4_bytes(_mm_srli_si128(a, 12), _mm_srli_si128(b, 12))
            )
        ); // 84 + 9 = 93 cycles ...
    return _mm_sub_epi8(res, _mm_cmpeq_epi8(_mm_sub_epi8(a, _mm_mullo_epi8(b, res)), b));
}


#define vect_128_div_flt64bit   _mm_div_pd // 20 cycles ...
#define vect_128_div_flt32bit   _mm_div_ps // 14 cycles ...
// @@TODO: Implmenet integral division (test whether multithreaded code may be faster) ...
#define vect_128_div_sint64bit _mm_div_epi64
#define vect_128_div_sint32bit _mm_div_epi32
#define vect_128_div_sint16bit _mm_div_epi16
#define vect_128_div_sint8bit  _mm_div_epi8

#define vect_128_div_uint64bit _mm_div_epu64
#define vect_128_div_uint32bit _mm_div_epu32
#define vect_128_div_uint16bit _mm_div_epu16
#define vect_128_div_uint8bit  _mm_div_epu8




#define get_vect_128_apply_func(oblvs...)     vect_128_apply ## oblvs ## _oper
// oper_a has is either a vect_128_* or scalr type ...
#define vect_128_unr_broad_cast_scalrs(oper, oper_a, oblvs...) ({       \
    typedef typeof(oper_a) _vbr_unr_a_t;                                \
    typedef vect_128_t(_vbr_unr_a_t, (_vbr_unr_a_t){0}) _unr_asdt;      \
    (_unr_asdt)(typeof(vect_native((_unr_asdt){})))(                    \
        get_vect_128_apply_func(oblvs) (                                \
            oper,                                                       \
            vect_memb_t((_unr_asdt){}),                                 \
            vect_128_broad_cast_to_native_if_scalr(oper_a)              \
        )                                                               \
    ); })

// @@TODO: clean up this MESS!!!!
// oper_a/oper_b are either a vect_128_* or scalr type(s) ...
#define vect_128_bin_broad_cast_scalrs(oper, oper_a, oper_b, oblvs...) ({       \
    typedef vect_128_t(oper_a, (typeof(oper_a)){0}) _bin_ad_da1_t;              \
    (_bin_ad_da1_t)(typeof(vect_native((_bin_ad_da1_t){})))(get_vect_128_apply_func(oblvs)(\
        oper,                                                                   \
        vect_memb_t((_bin_ad_da1_t){0}),                                             \
        vect_128_broad_cast_to_native_if_scalr(oper_a),          \
        vect_128_broad_cast_to_native_if_scalr(oper_b))); })


#define _apply_oblvs_scalr_oper _oblvs_scalr
#define _apply_oblvs_sign_oper _oblvs_sign

#undef vect_128_and
#undef vect_128_or
#undef vect_128_xor
#undef vect_128_add
#undef vect_128_sub
#undef vect_128_mul
#undef vect_128_div

#define vect_128_and(a, b)    vect_128_bin_broad_cast_scalrs(and, a, b, _apply_oblvs_scalr_oper)
#define vect_128_or(a, b)     vect_128_bin_broad_cast_scalrs(or, a, b,  _apply_oblvs_scalr_oper)
#define vect_128_xor(a, b)    vect_128_bin_broad_cast_scalrs(xor, a, b, _apply_oblvs_scalr_oper)

#define vect_128_add(a, b)    vect_128_bin_broad_cast_scalrs(add, a, b, _apply_oblvs_sign_oper)
#define vect_128_sub(a, b)    vect_128_bin_broad_cast_scalrs(sub, a, b, _apply_oblvs_sign_oper)
#define vect_128_mul(a, b)    vect_128_bin_broad_cast_scalrs(mul, a, b, _apply_oblvs_sign_oper)

#define vect_128_div(a, b)    vect_128_bin_broad_cast_scalrs(div, a, b)


/** vect_128 right shift by immediate ... ********************************************************/

#ifndef _mm_slli_epi8
// theres no 8 bit left shift but we can simulated by doing a 16 bit left shift
// and zeroing out the appropriate top bits ...
// reqs:
//  _mm_and_si128: 1x(1, 0.33)
//  _mm_slli_epi16: 1x(1, 1)
// _mm_set1_epi16: ~ 1x(1, 0) (so about 2-3 cycles)
vect_128_intrs_signt(__m128i) _mm_slli_epi8(__m128i a, int _mag_imm) {
    return _mm_and_si128(
        _mm_slli_epi16(a, _mag_imm),
        _mm_set1_epi8((unsigned char)(0xFF << ((_mag_imm) & 0b1111)))
    );
}
#define _mm_slli_epi8 _mm_slli_epi8
#endif

#ifndef _mm_sll_epi8
// (3-4 cycles)
vect_128_intrs_signt(__m128i) _mm_sll_epi8(__m128i a, __m128i b) {
    return _mm_and_si128(_mm_sll_epi16(a, b), _mm_set1_epi8(0xFF << _mm_cvtsi128_si64(b)));
}
#define _mm_sll_epi8 _mm_sll_epi8
#endif

#ifndef _mm_srli_epi8
// theres no 8 bit logical right shift but we can simulated by doing
// a 16 bit logical right shift and zero out the appropriate parts
// reqs:
//      _mm_and_si128   1x(1, 0.33)
//      _mm_srli_epi16  1x(1, 1)
//      _mm_set1_epi16  1x(1, 0) (so about 2-3 cycles)
vect_128_intrs_signt(__m128i) _mm_srli_epi8(__m128i a, int b) {
    return _mm_and_si128(_mm_srli_epi16(a, b), _mm_set1_epi8(0xFF >> (b & 0b111)));
}
#define _mm_srli_epi8 _mm_srli_epi8
#endif

#ifndef _mm_srl_epi8
// (3-4) cycles ...
vect_128_intrs_signt(__m128i) _mm_srl_epi8(__m128i a, __m128i b) {
    return _mm_and_si128(_mm_srl_epi16(a, b), _mm_set1_epi8(0xFFU >> _mm_cvtsi128_si64(b)));
}
#define _mm_srl_epi8 _mm_srl_epi8
#endif


#ifndef _mm_srai_epi8
// 6-7 cycles ..
vect_128_intrs_signt(__m128i) _mm_srai_epi8(__m128i a, int b) {
    return _mm_or_si128(
        _mm_and_si128(
            _mm_srai_epi16(a, b),
            _mm_set_epi8(
                255, 0, 255, 0, 255, 0, 255, 0,
                255, 0, 255, 0, 255, 0, 255, 0
            )
        ),
        _mm_srli_epi16(_mm_srai_epi16(_mm_slli_epi16(a, 8), b), 8)
    );
}
#define _mm_srai_epi8 _mm_srai_epi8
#endif


#ifndef _mm_sra_epi8
// 6-7 cycles ..
vect_128_intrs_signt(__m128i) _mm_sra_epi8(__m128i a, __m128i b) {
    return _mm_or_si128(
        _mm_and_si128(
            _mm_sra_epi16(a, b),
            _mm_set_epi8(
                255, 0, 255, 0, 255, 0, 255, 0,
                255, 0, 255, 0, 255, 0, 255, 0
            )
        ),
        _mm_srli_epi16(_mm_sra_epi16(_mm_slli_epi16(a, 8), b), 8)
    );
}
#define _mm_sra_epi8 _mm_sra_epi8
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
vect_128_intrs_signt(__m128i) _mm_srai_epi64(__m128i a, int _imm) {
    return _mm_or_si128(
        _mm_srli_epi64(a, _imm),
        _mm_slli_epi64(
            _mm_cmplt_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128()),
            (64 - (_imm))
        )
    );
}
#define _mm_srai_epi64 _mm_srai_epi64
#endif

#ifndef _mm_sra_epi64
// (6 - 8) cycles ...
vect_128_intrs_signt(__m128i) _mm_sra_epi64(__m128i a, __m128i  b) {
    return _mm_or_si128(
        _mm_srl_epi64(a, b),
        _mm_sll_epi64(
            _mm_cmplt_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 1, 1)), _mm_setzero_si128()),
            _mm_sub_epi64(_mm_set1_epi64x(64), b)
        )
    );
}
#define _mm_sra_epi64 _mm_sra_epi64
#endif


#define vect_128_lshift_imm_intgl64bit          _mm_slli_epi64
#define vect_128_lshift_imm_intgl32bit          _mm_slli_epi32
#define vect_128_lshift_imm_intgl16bit          _mm_slli_epi16
#define vect_128_lshift_imm_intgl8bit           _mm_slli_epi8

#define vect_128_lshift_scalr_intgl64bit        _mm_sll_epi64
#define vect_128_lshift_scalr_intgl32bit        _mm_sll_epi32
#define vect_128_lshift_scalr_intgl16bit        _mm_sll_epi16
#define vect_128_lshift_scalr_intgl8bit         _mm_sll_epi8

#define vect_128_rshift_logic_imm_intgl64bit    _mm_srli_epi64
#define vect_128_rshift_logic_imm_intgl32bit    _mm_srli_epi32
#define vect_128_rshift_logic_imm_intgl16bit    _mm_srli_epi16
#define vect_128_rshift_logic_imm_intgl8bit     _mm_srli_epi8

#define vect_128_rshift_logic_scalr_intgl64bit  _mm_srl_epi64
#define vect_128_rshift_logic_scalr_intgl32bit  _mm_srl_epi32
#define vect_128_rshift_logic_scalr_intgl16bit  _mm_srl_epi16
#define vect_128_rshift_logic_scalr_intgl8bit   _mm_srl_epi8

#define vect_128_rshift_arith_imm_intgl64bit    _mm_srai_epi64
#define vect_128_rshift_arith_imm_intgl32bit    _mm_srai_epi32
#define vect_128_rshift_arith_imm_intgl16bit    _mm_srai_epi16
#define vect_128_rshift_arith_imm_intgl8bit     _mm_srai_epi8

#define vect_128_rshift_arith_scalr_intgl64bit  _mm_sra_epi64
#define vect_128_rshift_arith_scalr_intgl32bit  _mm_sra_epi32
#define vect_128_rshift_arith_scalr_intgl16bit  _mm_sra_epi16
#define vect_128_rshift_arith_scalr_intgl8bit   _mm_sra_epi8

#define vect_128_apply_bin_shift_oper(shift_oper, a, b) ({                              \
    typedef typeof(a) _expr_a_sh_bin_t;                                                 \
    typedef vect_128_t(_expr_a_sh_bin_t, (_expr_a_sh_bin_t){0}) _t_binr_sdh_t;          \
    vect_128_intgl_native_t _shftbrd_a                                                  \
        = (vect_128_intgl_native_t)vect_128_broad_cast_to_native_if_scalr(a);           \
    (_t_binr_sdh_t)(typeof(vect_native((_t_binr_sdh_t){0})))scalr_switch_on_byte_size(  \
        vect_memb_t((_t_binr_sdh_t){0}),        \
        vect_128_ ## shift_oper ## _intgl64bit, \
        vect_128_ ## shift_oper ## _intgl32bit, \
        vect_128_ ## shift_oper ## _intgl16bit, \
        vect_128_ ## shift_oper ## _intgl8bit,  \
        vect_128_unable_to_determine_type       \
    )(_shftbrd_a, b);                                    })

#define vect_128_apply_bin_shift_scalr(shift_oper, a, b)    \
    vect_128_apply_bin_shift_oper(shift_oper ## _scalr, a, vect_128_broad_cast_to_native_if_scalr((long)b))

#define vect_128_lshift_bin_imm(args...)            vect_128_apply_bin_shift_oper(lshift_imm, args)
#define vect_128_lshift_bin_scalr(args...)          vect_128_apply_bin_shift_scalr(lshift, args)

#define vect_128_rshift_logic_bin_imm(args...)      vect_128_apply_bin_shift_oper(rshift_logic_imm, args)
#define vect_128_rshift_logic_bin_scalr(args...)    vect_128_apply_bin_shift_scalr(rshift_logic, args)

#define vect_128_rshift_arith_bin_imm(args...)      vect_128_apply_bin_shift_oper(rshift_arith_imm, args)
#define vect_128_rshift_arith_bin_scalr(args...)    vect_128_apply_bin_shift_scalr(rshift_arith, args)

#undef vect_128_lshift
#undef vect_128_rshift_logic
#undef vect_128_rshift_arith

#define vect_128_lshift(a, b)       vect_128_bin_oper_select_scalr_imm_oper(lshift_bin,  b, a, b)
#define vect_128_rshift_logic(a, b) vect_128_bin_oper_select_scalr_imm_oper(rshift_logic_bin, b, a, b)
#define vect_128_rshift_arith(a, b) vect_128_bin_oper_select_scalr_imm_oper(rshift_arith_bin, b, a, b)

#ifdef __INTEL_COMPILER
#define vect_128_bin_oper_select_scalr_imm_oper(oper, e, args...) ( \
         (comp_expr_is_imm(e)) ? vect_128_ ## oper ## _imm (args) : vect_128_ ## oper ## _scalr(args)   \
    )

#else
#define vect_128_bin_oper_select_scalr_imm_oper(oper, e, args...)   \
    comp_select(comp_expr_is_imm(e), vect_128_ ## oper ## _imm (args), vect_128_ ## oper ## _scalr(args))
#endif


/* Extends the sign bit, results in either all zeros or all ones depending on most significant bit ...... */
vect_128_intrs_signt(__m128i) vect_128_sign_ext_intgl64bit_f(__m128i a) {return _mm_srai_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 1, 1)), 32); } // copy the high 32 bits and right shift (2 cycles) ...
vect_128_intrs_signt(__m128i) vect_128_sign_ext_intgl32bit_f(__m128i a) {return _mm_srai_epi32(a, 32); }

vect_128_intrs_signt(__m128i) vect_128_sign_ext_intgl16bit_f(__m128i a) {return _mm_srai_epi16(a, 16); }
vect_128_intrs_signt(__m128i) vect_128_sign_ext_intgl8bit_f(__m128i a)  {return _mm_cmplt_epi8(a, _mm_setzero_si128()); } // 2 cycles ...

vect_128_intrs_signt(__m128d) vect_128_sign_ext_flt64bit_f(__m128d a) {return _mm_castsi128_pd(vect_128_sign_ext_intgl64bit_f(_mm_castpd_si128(a))); }
vect_128_intrs_signt(__m128)  vect_128_sign_ext_flt32bit_f(__m128 a)  {return _mm_castsi128_ps(vect_128_sign_ext_intgl32bit_f(_mm_castps_si128(a))); }

#undef vect_128_sign_ext
#define vect_128_sign_ext(a) vect_128_unr_broad_cast_scalrs(sign_ext, a, _apply_oblvs_sign_oper)


// Extract components by immediate index ...
// SSE* doesn't support extraction of doubles...
// 1 - 2 cycles ...
vect_128_intrs_signt(flt_bit_t(64)) _mm_extract_pd(__m128d a, int _imm) {
    return _mm_cvtsd_f64((_imm & 1) ? (__m128d)_mm_srli_si128((__m128i)a, 8) : a);
}


// extract member from vectors using a scalar (non-immediate) ...


#define vect_128_extrt_scalr_flt64bit
#define vect_128_extrt_scalr_flt32bit
#define vect_128_extrt_scalr_sint64bit
#define vect_128_extrt_scalr_sint32bit
#define vect_128_extrt_scalr_sint16bit
#define vect_128_extrt_scalr_sint8bit
#define vect_128_extrt_scalr_uint64bit
#define vect_128_extrt_scalr_uint32bit
#define vect_128_extrt_scalr_uint16bit
#define vect_128_extrt_scalr_uint8bit



#ifndef __SSE4_1__
vect_128_intrs_signt(int) _mm_test_all_ones(__m128i a) {
    return (_mm_cvtsi128_si64(a) & _mm_cvtsi128_si64(_mm_srli_si128(a, 8))) == (long)-1;
}
#endif



#endif // __SSE2__


#endif // __VECT_128__
