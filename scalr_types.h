
#ifndef __SCALR_TYPES__
#define __SCALR_TYPES__

#include "comp_utils.h"
#include "macro_utils.h"

#if   (UINTPTR_MAX == UINT64_MAX)   // convert void * to integral type so we can apply xor and other operators..
    #define word_t long long int
    #define word_t_size 8
#elif (UINTPTR_MAX == UINT32_MAX)
    #define word_t int
    #define word_t_size 4
#elif (UINTPTR_MAX == UINT16_MAX)
    #define word_t short
    #define word_t_size 2
#elif (UINTPTR_MAX == UINT8_MAX)
    #define word_t char
    #define word_t_size 1
#else
    #error "Unable to determing intergral type for pointer type"
#endif
#define cast_ptr(var) ((word_t)(var)) // cast pointer to integral type ...


#define type_bit_name(_kind, _bit_size) _kind ## _bit_size ## bit

#define sint1byt_t    signed      char
#define uint1byt_t    unsigned    char
#define sint8bit_t    signed      char
#define uint8bit_t    unsigned    char

#define sint2byt_t    signed      short
#define uint2byt_t    unsigned    short
#define sint16bit_t   signed      short
#define uint16bit_t   unsigned    short

#define sint4byt_t    signed      int
#define uint4byt_t    unsigned    int
#define sint32bit_t   signed      int
#define uint32bit_t   unsigned    int

#define sint8byt_t    signed      long long int
#define uint8byt_t    unsigned    long long int

#define sint64bit_t   signed      long long int
#define uint64bit_t   unsigned    long long int

#define SCALR_INTGL_TYPE_CNT 8

#define sint_byt_t(_byt_mag) sint ## _byt_mag ## byt ## _t    // get signed integral type by byte size
#define uint_byt_t(_byt_mag) uint ## _byt_mag ## byt ## _t   // get unsigned integral type with with _byt_mag bytes ..

#define sint_bit_t(_bit_mag) sint ## _bit_mag ## bit ## _t   // get signed integral type by bit size
#define uint_bit_t(_bit_mag) uint ## _bit_mag ## bit ## _t   // get unsigned integral by bit size

#define flt4byt_t    float
#define flt32bit_t   float
#define flt8byt_t    double
#define flt64bit_t   double

#define flt_byt_t(_byt_mag) flt ## _byt_mag ## byt ## _t
#define flt_bit_t(_bit_mag) flt ## _bit_mag ## bit ## _t

#define type_from_kind_bit_size(_kind, _bit_size) _kind ## _bit_t(_bit_size)

//#define is_scalr_t(value)           (__builtin_types_compatible_p(typeof(value), int))

//#define is_real_t(value)            ((typeof(value))0.5 == 0.5) // checks if the type of value is a real type, assuming both float/double have the same mag ...
// expr retuning (float, double)
#define type_is_flt32bit(type) (comp_types_eq(type, flt_bit_t(32)))
#define type_is_flt64bit(type) (comp_types_eq(type, flt_bit_t(64)))
#define type_is_flt(type)     (type_is_flt32bit(type) || type_is_flt64bit(type))
#define expr_is_flt(expr)     type_is_flt(typeof(expr))

#define type_is_uint8bit(type)   comp_types_eq(type, uint_bit_t(8))
#define type_is_uint16bit(type)  comp_types_eq(type, uint_bit_t(16))
#define type_is_uint32bit(type)  comp_types_eq(type, uint_bit_t(32))

#define type_is_uint64bit(type)  (comp_types_eq(type, uint_bit_t(64)) || comp_types_eq(type, unsigned long int))

#define expr_is_(_expr, _kind, _bit_size) type_is_ ## _kind ## _bit_size ## bit(typeof(_expr))
#define type_is_   expr_is_

#define type_is_sint8bit(type)   (comp_types_eq(type, sint_bit_t(8)) || comp_types_eq(type, char))

// very strange ==> __builtin_types_compatible_p(signed char, char) == 0,
// which seems to stem from 3.9.1 Fundamental types [basic.fundamental],
// http://stackoverflow.com/questions/436513/char-signed-char-char-unsigned-char

#define type_is_sint16bit(type)  comp_types_eq(type, sint_bit_t(16))
#define type_is_sint32bit(type)  comp_types_eq(type, sint_bit_t(32))
#define type_is_sint64bit(type)  (comp_types_eq(type, sint_bit_t(64)) || comp_types_eq(type, signed long int))

#define _type_is_int_t(type, int_t_kind)  (      \
    comp_types_eq(type, int_t_kind(8))           \
 || comp_types_eq(type, int_t_kind(16))          \
 || comp_types_eq(type, int_t_kind(32))          \
 || comp_types_eq(type, int_t_kind(64))          \
)

#define type_is_uint(type) _type_is_int_t(type, uint_bit_t)
#define type_is_sint(type) (_type_is_int_t(type, sint_bit_t) || type_is_sint8bit(type))

#define scalr_types_eq(type_a, type_b) (                            \
    comp_types_eq(type_a, type_b)                                   \
    || (type_is_sint64bit(type_a) && type_is_sint64bit(type_b))     \
    || (type_is_uint64bit(type_a) && type_is_uint64bit(type_b))     \
    || (type_is_sint8bit(type_a) && type_is_sint8bit(type_b))       \
)// no choice since comp_types_eq doesn't properly handle (signed char, char) and (signed long int, signed long long int)
 // eventhough on most compilers for x86_64 system their pretty much identical ...

#define scalr_types_neq(type_a, type_b) (!(scalr_types_eq(type_a, type_b)))



#define expr_is_uint(expr)  type_is_uint(typeof(expr))
#define expr_is_sint(expr)  type_is_sint(typeof(expr))

#define type_is_intgl(type) (type_is_uint(type) || type_is_sint(type))
//      ^^^^^^^^^^^^^ returns 1 if type is a native integral type, 0 otherwise ....
#define expr_is_intgl(expr) type_is_intgl(typeof(expr))
//      ^^^^^^^^^^^^^ returns 1 if expr returns a native integral type, 0 otherwise ....

#define expr_is_intgl_bit(expr, bit_size) (expr_is_(expr, sint, bit_size) || expr_is_(expr, uint, bit_size))

#define type_is_scalr(_type) (type_is_intgl(_type) || type_is_flt(_type))
#define expr_is_scalr(expr) type_is_scalr(typeof(expr))
//      ^^^^^^^^^^^^^ returns 1 if expr returns a native scalar type, 0 otherwise


#define _interp(e, _from_name, _to_name) (((union {_from_name _f; _to_name _t;}){(e)})._t)
// arithmetic right shift (extending sign bit)


// apply bit operations on scalar expression, if floats reinterpret bits as intgl scalars apply bit operation
// and reinterpret result back as float type ...
#define scalr_bit_oper(a, oper, b, _flt_to_intl_kind)       \
    macro_apply(                                            \
        scalr_switch,                                       \
        (a),                                                \
        _interp(                                            \
            (_interp(a, flt_bit_t(64), _flt_to_intl_kind(64)) oper _interp(b, flt_bit_t(64), _flt_to_intl_kind(64))),     \
            _flt_to_intl_kind(64),                          \
            flt_bit_t(64)                                   \
        ),                                                  \
        _interp(                                            \
            (_interp(a, flt_bit_t(32), _flt_to_intl_kind(32)) oper _interp(b, flt_bit_t(32), _flt_to_intl_kind(32))),     \
            _flt_to_intl_kind(32),                          \
            flt_bit_t(32)                                   \
        ),                                                  \
                                                            \
        ((uint_bit_t(64))(a)    oper (uint_bit_t(64))(b)),  \
        ((uint_bit_t(32))(a)    oper (uint_bit_t(32))(b)),  \
        ((uint_bit_t(16))(a)    oper (uint_bit_t(16))(b)),  \
        ((uint_bit_t(8))(a)     oper (uint_bit_t(8))(b)),   \
                                                            \
        ((sint_bit_t(64))(a)    oper (sint_bit_t(64))(b)),  \
        ((sint_bit_t(32))(a)    oper (sint_bit_t(32))(b)),  \
        ((sint_bit_t(16))(a)    oper (sint_bit_t(16))(b)),  \
        ((sint_bit_t(8))(a)     oper (sint_bit_t(8))(b)),   \
        (void)0                                             \
    )

#define scalr_xor(a, b) scalr_bit_oper(a, ^, b, uint_bit_t)
#define scalr_and(a, b) scalr_bit_oper(a, &, b, uint_bit_t)
#define scalr_or(a, b)  scalr_bit_oper(a, |, b, uint_bit_t)

#define scalr_cmp_bits_eq(a, b)     scalr_bit_oper(a, ==, b, uint_bit_t)
#define scalr_cmp_bits_neq(a, b)    scalr_bit_oper(a, !=, b, uint_bit_t)

#define sclar_shift(shf_sclr_a, shift_oper, _mb, _intgl_kind)           \
    macro_apply(                                                        \
        scalr_switch,                                                   \
        shf_sclr_a,                                                     \
        _interp(                                                        \
            (_interp(shf_sclr_a, flt_bit_t(64), _intgl_kind(64)) shift_oper (_mb)),   \
            _intgl_kind(64),                                            \
            flt_bit_t(64)                                               \
        ),                                                              \
        _interp(                                                        \
            (_interp(shf_sclr_a, flt_bit_t(32), _intgl_kind(32)) shift_oper (_mb)),   \
            _intgl_kind(32),                                            \
            flt_bit_t(32)                                               \
        ),                                                              \
        ((_intgl_kind(64))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(32))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(16))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(8))(shf_sclr_a)     shift_oper (_mb)),            \
                                                                        \
        ((_intgl_kind(64))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(32))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(16))(shf_sclr_a)    shift_oper (_mb)),            \
        ((_intgl_kind(8))(shf_sclr_a)     shift_oper (_mb)),            \
        (void)0                                     \
    )


#define scalr_lshift(a, b)  sclar_shift(a, <<, b, uint_bit_t)
#define scalr_lshift_imm    scalr_lshift
#define scalr_lshift_scalr  scalr_lshift

#define scalr_rshift_logic(a, b)  sclar_shift(a, >>, b, uint_bit_t)
#define scalr_rshift_logic_imm    scalr_rshift_logic
#define scalr_rshift_logic_scalr  scalr_rshift_logic

#define scalr_rshift_arith(a, b)  sclar_shift(a, >>, b, sint_bit_t)
#define scalr_rshift_arith_imm    scalr_rshift_arith
#define scalr_rshift_arith_scalr  scalr_rshift_arith

#define scalr_add(a, b) ((a) + (b))
#define scalr_sub(a, b) ((a) - (b))
#define scalr_mul(a, b) ((a) * (b))
#define scalr_div(a, b) ((a) / (b))

#define scalr_sign_ext(a)                                       \
    scalr_switch(                                               \
        a,                                                      \
        _interp((_interp(a, flt_bit_t(64), sint_bit_t(64)) >> 63),  sint_bit_t(64), flt_bit_t(64)),    \
        _interp((_interp(a, flt_bit_t(32), sint_bit_t(32)) >> 31),  sint_bit_t(32), flt_bit_t(32)),    \
        ((sint_bit_t(64))(a)  >> 63),       \
        ((sint_bit_t(32))(a)  >> 31),       \
        ((sint_bit_t(16))(a)  >> 15),       \
        ((sint_bit_t(8))(a)   >> 7),        \
        ((sint_bit_t(64))(a)  >> 63),       \
        ((sint_bit_t(32))(a)  >> 31),       \
        ((sint_bit_t(16))(a)  >> 15),       \
        ((sint_bit_t(8))(a)   >>  7),       \
        (void)0                             \
    )


/** SELECT based on type of expression ****/
#define scalr_switch_sint(expr, if_sint64bit, if_sint32bit, if_sint16bit, if_sint8bit, if_no_match)   \
    (comp_select(expr_is_(expr, sint, 64), if_sint64bit,  \
     comp_select(expr_is_(expr, sint, 32), if_sint32bit,  \
     comp_select(expr_is_(expr, sint, 16), if_sint16bit,  \
     comp_select(expr_is_(expr, sint, 8),  if_sint8bit,   \
        if_no_match)))))

#define scalr_switch_uint(expr, if_uint64bit, if_uint32bit, if_uint16bit, if_uint8bit, if_no_match)   \
    (comp_select(expr_is_(expr, uint, 64), if_uint64bit, \
    comp_select(expr_is_(expr, uint, 32), if_uint32bit,  \
    comp_select(expr_is_(expr, uint, 16), if_uint16bit,  \
    comp_select(expr_is_(expr, uint, 8),  if_uint8bit,   \
        if_no_match)))))


#define scalr_switch_oblvs_sign_intgl(expr, if_intgl64bit, if_intgl32bit, if_intgl16bit, if_intgl8bit, if_no_match)  \
    comp_select(expr_is_intgl_bit(expr, 64), if_intgl64bit, \
    comp_select(expr_is_intgl_bit(expr, 32), if_intgl32bit, \
    comp_select(expr_is_intgl_bit(expr, 16), if_intgl16bit, \
    comp_select(expr_is_intgl_bit(expr, 8),  if_intgl8bit,  \
        if_no_match))))


// select expression on floats
#define scalr_switch_flt(expr, if_flt64bit, if_flt32bit, if_no_match) \
    comp_select(expr_is_(expr, flt, 64), if_flt64bit,       \
    comp_select(expr_is_(expr, flt, 32), if_flt32bit,       \
        if_no_match))

// select expression on integrals ...
#define scalr_switch_intgl(         \
    expr,                           \
                                    \
    if_sint64bit,                   \
    if_sint32bit,                   \
    if_sint16bit,                   \
    if_sint8bit,                    \
                                    \
    if_uint64bit,                   \
    if_uint32bit,                   \
    if_uint16bit,                   \
    if_uint8bit,                    \
                                    \
    if_no_match                     \
)                                   \
    scalr_switch_sint(              \
        expr,                       \
        if_sint64bit,               \
        if_sint32bit,               \
        if_sint16bit,               \
        if_sint8bit,                \
        scalr_switch_uint(          \
            expr,                   \
            if_uint64bit,           \
            if_uint32bit,           \
            if_uint16bit,           \
            if_uint8bit,            \
                                    \
            if_no_match             \
        )                           \
    )


// @@>> DO NOT CHANGE THIS ORDER!!!!
//#define flts_sizes     (flt, 64), (flt, 32)
//#define sints_sizes    (sint, 64), (sint, 32), (sint, 16), (sint, 8)
//#define uints_sizes    (uint, 64), (uint, 32), (uint, 16), (uint, 8)
//#define scalr_intlg_cnt 8

//#define intgls_sizes   sints_sizes, uints_sizes
//#define scalrs_params_kinds_sizes   flts_sizes, intgls_sizes
/**************************************************************************/

//#define type_bit_name_list(_kind_and_size) type_bit_name _kind_and_size
//#define scalrs_names MAP_LIST(type_bit_name_list, scalrs_params_kinds_sizes)

// select expression on scalars
#define scalr_switch(               \
    expr,                           \
                                    \
    if_flt64bit,                    \
    if_flt32bit,                    \
                                    \
    if_sint64bit,                   \
    if_sint32bit,                   \
    if_sint16bit,                   \
    if_sint8bit,                    \
                                    \
    if_uint64bit,                   \
    if_uint32bit,                   \
    if_uint16bit,                   \
    if_uint8bit,                    \
                                    \
    if_no_match                     \
) ({                                \
    typedef typeof(expr) _expr_scalr_switch_t; \
    scalr_switch_flt(               \
        _expr_scalr_switch_t,       \
        if_flt64bit,                \
        if_flt32bit,                \
        scalr_switch_sint(          \
            _expr_scalr_switch_t,   \
            if_sint64bit,           \
            if_sint32bit,           \
            if_sint16bit,           \
            if_sint8bit,            \
            scalr_switch_uint(      \
                _expr_scalr_switch_t,\
                if_uint64bit,       \
                if_uint32bit,       \
                if_uint16bit,       \
                if_uint8bit,        \
                                    \
                if_no_match         \
            )                       \
        )                           \
    ); })

#define scalr_switch_on_byte_size(expr, if_8bytes, if_4bytes, if_2bytes, if_1bytes, if_no_match) \
    comp_select(sizeof(expr) == 8, if_8bytes,   \
    comp_select(sizeof(expr) == 4, if_4bytes,   \
    comp_select(sizeof(expr) == 2, if_2bytes,   \
    comp_select(sizeof(expr) == 1, if_1bytes,   \
        if_no_match))))

#define scalr_switch_flt_or_intgl_byte_sizes(expr, if_flt8bytes, if_flt4bytes, if_8bytes, if_4bytes, if_2bytes, if_1bytes, if_no_match) ({\
    typedef typeof(expr) _exprscalr_intf_byt_size_t;                             \
    comp_select(expr_is_(_exprscalr_intf_byt_size_t, flt, 64), if_flt8bytes,   \
    comp_select(expr_is_(_exprscalr_intf_byt_size_t, flt, 32), if_flt4bytes,   \
        scalr_switch_on_byte_size(_exprscalr_intf_byt_size_t, if_8bytes, if_4bytes, if_2bytes, if_1bytes, if_no_match))); })


#include <stdio.h>
#define scalr_str(buffer, _expr) ({             \
    typeof(buffer[0]) *_temp = (buffer);        \
    snprintf(                                   \
        _temp,                                  \
        sizeof(buffer),                         \
        scalr_switch(                           \
            _expr,                              \
            "%f", "%f",                         \
            "%lli", "%i", "%hi", "%hhi",        \
            "%llu", "%u", "%hu", "%hhu",        \
            (void)0                             \
        ),                                      \
        (typeof(scalr_switch(_expr,             \
            (double)0, (double)0,               \
            (signed long long int)0, (int)0, (short)0, (char)0,     \
            (unsigned long long int)0, (unsigned)0, (unsigned short)0, (unsigned char)0,   \
            (void)0)))(_expr)                   \
    ); _temp; })


#define _xor_symbl  ^
#define _or_symbl   |
#define _and_symbl  &
#define _add_symbl  +
#define _sub_symbl  -
#define _mul_symbl  *
#define _lshift_symbl <<
#define _rshift_symbl >>

#define _lshift_imm_symbl   _lshift_symbl
#define _lshift_scalr       _lshift_symbl

#define _rshift_arith_symbl _rshift_symbl
#define _rshift_logic_symbl _rshift_symbl

#define oper_symbl(name) _ ## name ## _symbl
#define token_str(_t) #_t

#define scalr_oper(oper) scalr_ ## oper



#endif
