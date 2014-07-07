
// AS of 2014:
// Assuming scalars:
//      floats are (32/64 IEEE754 bit floats)
//      Integrals are (64/32/16/8 bit unsigned/signed natural numbers) represented using twos complement
// 128 bit vect_native for (float types) requires at least SSE (extremely common, launched 1999)
// 128 bit vect_native for (all scalars types) requires at least SSE2  (very common, launched 2001), w/ optimal intrns SSE4.1 (somewhat common, launched 2007)
// 256 bit vect_native for (floats types) requires at least AVX (launched 2011, rare)
// 256 bit vect_native for (all scalar) requires at least AVX2 (launched 2013, extremely rare)
// 512 bit vect_native for floats and (only 32/64 integral types) bits requires AVX-512 (to be released in 2015)


#ifndef __VECT__
#define __VECT__

#include "vect_128.h"
#include "vect_256.h"
#include "vect_512.h"

#include "bits.h"
#include "scalr_types.h"

#include "macro_utils.h"


#define _vect_supprt(_vect_bit_size, _memb_kind, _memb_bit_size) vect_ ## _vect_bit_size ## _ ## _memb_kind ## _memb_bit_size ##  bit_supprt
//      ^^^^^^^^^^^^ returns vect_support macro name
//                   _vect_bit_size(512, 256, 128) containing packed
//                  _memb_kind(flt, sint, uint) of
//                  _memb_bit_size(64, 32, 16, 8) is supported

#define __vect_t_1(vect_size, _membname) _vect_ ## vect_size ## _t(_membname)
//      ^^^^^^^^  returns an expression with vect_t if supported otherwise _memb type
#define __vect_t_0(vect_size, _membname) _membname ## _t

#define __vect_t(implemtd, vect_size, _membname) __vect_t_ ## implemtd(vect_size, _membname)

#define _vect_or_memb_expr(_vect_bit_size, _memb_kind, _memb_bit_size) ( \
    macro_apply(                                                         \
        __vect_t,                                                        \
        _vect_supprt(_vect_bit_size, _memb_kind, _memb_bit_size),        \
        _vect_bit_size,                                                  \
        type_bit_name(_memb_kind, _memb_bit_size)                        \
     )                                                                   \
    ){0}
///*      ^^^^^^^^^^^^^^^^^^ returns an expr with either
//                            vect_[(512 || 256 || 128)]_[(flt64bit || flt32bit || sint64bit || sint32bit || sint16bit || sint8bit || uint64bit || uint32bit || uint16bit ||uint8bit)]_t
//                            if supported OR flt64bit_t || flt32bit_t || sint64bit_t || sint32bit_t || sint16bit_t || sint8bit_t || uint64bit_t || uint32bit_t || uint16bit_t ||uint8bit_t)
//                            if NOT supported ... */\
//    __builtin_choose_expr(                                                                      \
//        _vect_supprt(_vect_bit_size, _memb_kind, _memb_bit_size),                               \
//        __vect_t(_vect_bit_size, type_bit_name(_memb_kind, _memb_bit_size)),       \
//        ((type_from_kind_bit_size(_memb_kind, _memb_bit_size)){0})                              \
//    )

#define _type_name_as_string(_type_name) # _type_name


//#define largest_vect_expr(_memb_kind, _memb_bit_mag)      (\
///*      ^^^^^^^^^^ gets an expression with the largest internal vect type [(512, 256, 128) bits]  that supports
//        _memb_kind (flt, sint, uint) containg _mem_bit_mag(64, 32, 16, 8)  bits
//        @@>> OR compilation error if theres none.   */      \
//    comp_select(_vect_supprt(512, _memb_kind, _memb_bit_mag), _vect_or_memb_expr(512, _memb_kind, _memb_bit_mag), \
//    comp_select(_vect_supprt(256, _memb_kind, _memb_bit_mag), _vect_or_memb_expr(256, _memb_kind, _memb_bit_mag), \
//    comp_select(_vect_supprt(128, _memb_kind, _memb_bit_mag), _vect_or_memb_expr(128, _memb_kind, _memb_bit_mag), \
//        vect_comp_err_emit("Theres no internal vect_t support: " \
//        _type_name_as_string(type_bit_name(_memb_kind, _memb_bit_mag))) )))),
//#define _largest_vect_expr_paren_args(args) largest_vect_expr args


#define vect_t_default(args...) (typeof(macro_arg_1(args))){0}

#define consume(arg, rest...) rest

#if defined(__AVX512PF__)
    #define largest_vect_flt        vect_512_t
    #define largest_vect_intgl      vect_512_t
#elif defined(__AVX2__)
    #define largest_vect_flt        vect_256_t
    #define largest_vect_intgl      vect_256_t
#elif defined(__AVX__)
    #define largest_vect_flt        vect_256_t
    #define largest_vect_intgl      vect_128_t
#elif defined(__SSE2__)
    #define largest_vect_flt        vect_128_t
    #define largest_vect_intgl      vect_128_t
#else
    #define largest_vect_flt        vect_not_supprtd
    #define largest_vect_intgl      vect_not_supprtd
#endif

#define largest_vect(_kind) largest_vect_ ## _kind

#define vect_t(args...) typeof(                                                                  \
    comp_select(expr_is_flt(macro_arg_0(args)), (largest_vect(flt)(macro_arg_0(args))){0},       \
    comp_select(expr_is_intgl(macro_arg_0(args)), (largest_vect(intgl)(macro_arg_0(args))){0},   \
    macro_arg_1(args, (void)"Expected a scalar type...")))                                       \
)
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
returns the largest internal vect_t type that supports _memb,
    _memb: can either be a type or an expr assuming typeof(_type) == _type,
    @@>> if theres no internal vect type supports typeof(_memb),
        than either: return typeof(arg_1) if giving OR compilation ERROR
*/

#define intrs(vect_bit_size, intrs_name) vect_ ## vect_bit_size ## _ ## intrs_name
#if defined(__AVX512PF__)
    #define vect_apply_intrs(intrs_name, _vect_apply_v, ...) \
        comp_select(bit_size(_vect_apply_v) == 512, intrs(256, intrs_name)(__VA_ARGS__),  \
        comp_select(bit_size(_vect_apply_v) == 256, intrs(128, intrs_name)(__VA_ARGS__),  \
        comp_select(bit_size(_vect_apply_v) == 128, intrs(256, intrs_name)(__VA_ARGS__),  \
            (void)"Unable to determine vector type." )))
#elif defined(__AVX2__) || defined(__AVX__)
    #define vect_apply_intrs(intrs_name, _vect_apply_v, ...) \
        comp_select(bit_size(_vect_apply_v) == 128, intrs(128, intrs_name)(__VA_ARGS__),  \
        comp_select(bit_size(_vect_apply_v) == 256, intrs(256, intrs_name)(__VA_ARGS__),  \
            (void)"Unable to determine vector type." ))
#elif defined(__SSE2__)
    #define vect_apply_intrs(intrs_name, _vect_apply_v, ...) \
        comp_select(bit_size(_vect_apply_v) == 128, intrs(128, intrs_name)(__VA_ARGS__),    \
            (void)"Unable to determine vector type.")
#else
    #define vect_apply_intrs vect_not_supprtd
#endif



#define vect_load(_vect_ptr, args...)        vect_apply_intrs(load,         *(_vect_ptr), _vect_ptr, args)
#define vect_load_align(_vect_ptr, args...)  vect_apply_intrs(load_align,   *(_vect_ptr), _vect_ptr, args)
#define vect_store(_vect_ptr, args...)       vect_apply_intrs(store,        *(_vect_ptr), _vect_ptr, args)
#define vect_store_align(_vect_ptr, args...) vect_apply_intrs(store_align,  *(_vect_ptr), _vect_ptr, args)


#define vect_broad_cast(_expr, _dest)        vect_apply_intrs(broad_cast, _dest, _expr, args)

#define vect_and(va, args...)                vect_apply_intrs(and,          va, va, args)
#define vect_xor(va, args...)                vect_apply_intrs(xor,          va, va, args)
#define vect_or(va, args...)                 vect_apply_intrs(or,           va, va, args)
#define vect_add(va, args...)                vect_apply_intrs(add,          va, va, args)
#define vect_sub(va, args...)                vect_apply_intrs(sub,          va, va, args)
#define vect_mul(va, args...)                vect_apply_intrs(mul,          va, va, args)
#define vect_lshift(va, args...)             vect_apply_intrs(lshift,       va, va, args)
#define vect_rshift_logic(va, args...)       vect_apply_intrs(rshift_logic, va, va, args)
#define vect_rshift_arith(va, args...)       vect_apply_intrs(rshift_arith, va, va, args)
#define vect_sign_ext(va, args...)           vect_apply_intrs(sign_ext,     va, va, args)


#endif


