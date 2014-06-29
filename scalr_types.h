
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

#define type_is_scalr(_type) (type_is_intgl(_type) || type_is_flt(_type))
#define expr_is_scalr(expr) type_is_scalr(typeof(expr))
//      ^^^^^^^^^^^^^ returns 1 if expr returns a native scalar type, 0 otherwise

// scalar type ids ...
// prefix 0 for unsigned integral, 1 for sign int, 2 for float, with the second digit being their byte size ...
// suffix is expected byte size ...
#define uint1byt_id 1
#define uint2byt_id 2
#define uint4byt_id 4
#define uint8byt_id 8

#define sint1byt_id 11
#define sint2byt_id 12
#define sint4byt_id 14
#define sint8byt_id 18

#define flt4byt_id  24
#define flt8byt_id  28

#define flt_byt_id(_byt_siz)    flt ## _byt_siz ## byt_id
#define uint_byt_id(_byt_siz)   uint ## _byt_siz ## byt_id
#define sint_byt_id(_byt_siz)   sint ## _byt_siz ## byt_id
// ^^^^^^^^^^ returns the corresponding type id contaiting _byt_size bytes

#define uint8bit_id     uint1byt_id
#define uint16bit_id    uint2byt_id
#define uint32bit_id    uint4byt_id
#define uint64bit_id    uint8byt_id

#define sint8bit_id     sint1byt_id
#define sint16bit_id    sint2byt_id
#define sint32bit_id    sint4byt_id
#define sint64bit_id    sint8byt_id

#define flt32bit_id     flt4byt_id
#define flt64bit_id     flt8byt_id

#define flt_bit_id(_bit_siz) flt ## _bit_siz ## bit_id
#define uint_bit_id(_bit_siz) uint ## _bit_siz ## bit_id
#define sint_bit_id(_bit_siz) sint ## _bit_siz ## bit_id
// ^^^^^^^^^^ returns the corresponding type id contaiting _bit_siz bits


#define error_no_t_id(_byt_siz) ({ /*switch (_byt_siz) { }*/ assert_with_msg(0, "unable to determine type_id"); })

#define INVALID_TYPE_ID -1

#define flt_type_id_from_expr(expr)                                                 \
    __builtin_choose_expr(expr_is_(expr, flt, 32), flt_bit_id(32),    \
    __builtin_choose_expr(expr_is_(expr, flt, 64), flt_bit_id(64),    \
        INVALID_TYPE_ID ))

#define intgl_type_id_from_expr(expr, intgl_kind) \
    __builtin_choose_expr(expr_is_(expr, intgl_kind, 8),  intgl_kind ## _bit_id(8),     \
    __builtin_choose_expr(expr_is_(expr, intgl_kind, 16), intgl_kind ## _bit_id(16),    \
    __builtin_choose_expr(expr_is_(expr, intgl_kind, 32), intgl_kind ## _bit_id(32),    \
    __builtin_choose_expr(expr_is_(expr, intgl_kind, 64), intgl_kind ## _bit_id(64),    \
        INVALID_TYPE_ID ))))

#define uint_type_id_from_expr(expr) intgl_type_id_from_expr(expr, uint)
#define sint_type_id_from_expr(expr) intgl_type_id_from_expr(expr, sint)

#define type_id_from_expr(expr)                                             \
    __builtin_choose_expr(expr_is_flt(expr), flt_type_id_from_expr(expr),   \
    __builtin_choose_expr(expr_is_uint(expr), uint_type_id_from_expr(expr), \
    __builtin_choose_expr(expr_is_sint(expr), sint_type_id_from_expr(expr), \
    INVALID_TYPE_ID )))


typedef union { // union of all types, allowing us to interpret the bits from one scalar type to any other scalar type ...
    uint_byt_t(8) _max_type;

    uint_byt_t(8) u_long;
    sint_byt_t(8) s_long;

    uint_byt_t(4) u_int;
    sint_byt_t(4) s_int;

    uint_byt_t(2) u_short;
    sint_byt_t(2) s_short;

    uint_byt_t(1) u_char;
    sint_byt_t(1) s_char;

    flt_byt_t(4) real_4;
    flt_byt_t(8) real_8;

    void *ptr;
} types_t;

#define types_init(_t, value) ({                                             \
    if (is_real_type(value))                                                 \
        switch (sizeof(value)) {                                             \
            case 4: _t.real_4   = (typeof(_t.real_4))(value);   break ;      \
            case 8: _t.real_8   = (typeof(_t.real_8))(value);   break ;      \
        }                                                                    \
    else                                                                     \
        switch (sizeof(value)) {                     					     \
            case 1: _t.u_char   = (typeof(_t.u_char))(value);   break ;  	 \
            case 2: _t.u_short  = (typeof(_t.u_short))(value);  break ;      \
            case 4: _t.u_int    = (typeof(_t.u_int))(value);    break ;      \
            case 8: _t.u_long   = (typeof(_t.u_long))(value);   break ;      \
        }                                                                    \
})



// right shift an intgl type or emit compilation error on ...
#define _rshift_(a, _mag, _type)                                                \
    __builtin_choose_expr(sizeof(a) == 1, ((_type(1))(a)) >> (_mag),            \
    __builtin_choose_expr(sizeof(a) == 2, ((_type(2))(a)) >> (_mag),            \
    __builtin_choose_expr(sizeof(a) == 4, ((_type(4))(a)) >> (_mag),            \
    __builtin_choose_expr(sizeof(a) == 8, ((_type(8))(a)) >> (_mag),            \
        comp_error_init("Unable to apply rshift_" #_type )                      \
    ))))


#define _interp(e, _from_name, _to_name) (((union {_from_name _f; _to_name _t;}){(e)})._t)
// arithmetic right shift (extending sign bit)

#define flt_rshift(a, _flt_byt_mag, _interp_as, _shft_mag)    \
    _interp(             \
        _rshift_(        \
            _interp(a, flt_byt_t(_flt_byt_mag), _interp_as(_flt_byt_mag)), \
            _shft_mag,                      \
            _interp_as                      \
        ),                                  \
        _interp_as(_flt_byt_mag),           \
        _flt_byt_mag(_flt_byt_mag)          \
    )

#define flt_rshift_arith(a, _byt_mag, shft_mag)    flt_rshift(a, _byt_mag, uint_byt_t, shft_mag)
#define flt_rshift_logic(a, _byt_mag, shft_mag)    flt_rshift(a, _byt_mag, sint_byt_t, shft_mag)


#define scalr_apply_intrs(intrs_name, _s, ...)

#define scalr_bit_oper(a, oper, b)  \
    macro_apply(                    \
        scalr_switch,               \
        (a),                        \
        _interp(                    \
            (_interp(a, flt_bit_t(64), uint_bit_t(64)) oper _interp(b, flt_bit_t(64), uint_bit_t(64))),     \
            uint_bit_t(64),         \
            flt_bit_t(64)           \
        ),                          \
        _interp(                    \
            (_interp(a, flt_bit_t(32), uint_bit_t(32)) oper _interp(b, flt_bit_t(32), uint_bit_t(32))),     \
            uint_bit_t(32),         \
            flt_bit_t(32)           \
        ),                          \
        macro_comma_delim_8(((uint_bit_t(64))(a) oper (uint_bit_t(64))(b))),        \
        (void)0                                     \
    )

#define scalr_xor(a, b) scalr_bit_oper(a, ^, b)
#define scalr_and(a, b) scalr_bit_oper(a, &, b)
#define scalr_or(a, b)  scalr_bit_oper(a, |, b)

#define scalr_add(a, b) ((a) + (b))
#define scalr_sub(a, b) ((a) - (b))
#define scalr_mul(a, b) ((a) * (b))
#define scalr_div(a, b) ((a) / (b))

// right shift bits, flts are interpreted as the corresponding intgl type, before the right shift,
// ther result is interpreted back as the same flt type before returned
// arithmetic right shift, extends the sign bit,
#define scalr_rshift_arith(a, _mag) \
    comp_select(expr_is_(a, flt, 32), flt_rshift_arith(a, 4, _mag),   \
    comp_select(expr_is_(a, flt, 64), flt_rshift_arith(a, 8, _mag),   \
    _rshift_(a, _mag, sint_byt_t)))

// right shift bits logical (extend zeros) (supports all 10 scalar types, float types are interpret as uint bit logical rshift is applied
// and then reinterpreted as floats and returned
#define scalr_rshift_logic(a, _mag)                                       \
    comp_select(expr_is_(a, flt, 32), flt_rshift_logic(a, 4, _mag),       \
    comp_select(expr_is_(a, flt, 64), flt_rshift_logic(a, 8, _mag),       \
    _rshift_(a, _mag, uint_byt_t)))




/** SELECT based on type of expression ****/
#define scalr_switch_sint(expr, if_sint64bit, if_sint32bit, if_sint16bit, if_sint8bit, if_no_match)   \
    (comp_select(expr_is_(expr, sint, 64), if_sint64bit,  \
    comp_select(expr_is_(expr, sint, 32), if_sint32bit,   \
    comp_select(expr_is_(expr, sint, 16), if_sint16bit,  \
    comp_select(expr_is_(expr, sint, 8),  if_sint8bit,   \
        if_no_match)))))

#define scalr_switch_uint(expr, if_uint64bit, if_uint32bit, if_uint16bit, if_uint8bit, if_no_match)   \
    (comp_select(expr_is_(expr, uint, 64), if_uint64bit,  \
    comp_select(expr_is_(expr, uint, 32), if_uint32bit,  \
    comp_select(expr_is_(expr, uint, 16), if_uint16bit,  \
    comp_select(expr_is_(expr, uint, 8),  if_uint8bit,   \
        if_no_match)))))

// select expression on floats
#define scalr_switch_flt(expr, if_flt64bit, if_flt32bit, if_no_match) \
    (comp_select(expr_is_(expr, flt, 64), if_flt64bit,   \
    comp_select(expr_is_(expr, flt, 32), if_flt32bit,    \
    if_no_match)))

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


#define scalr_switch_kind(expr, if_flt, if_intgl, if_no_match)                          \
    macro_apply(                         \
        scalr_switch_flt,                \
        expr,                            \
        macro_unpack_args(if_flt),       \
        macro_apply(                     \
            scalr_switch_intgl,          \
            expr,                        \
            macro_unpack_args(if_intgl), \
            if_no_match                  \
        )                                \
    )

// @@>> DO NOT CHANGE THIS ORDER!!!!
#define flts_sizes     (flt, 64), (flt, 32)
#define sints_sizes    (sint, 64), (sint, 32), (sint, 16), (sint, 8)
#define uints_sizes    (uint, 64), (uint, 32), (uint, 16), (uint, 8)
#define scalr_intlg_cnt 8

#define intgls_sizes   sints_sizes, uints_sizes
#define scalrs_params_kinds_sizes   flts_sizes, intgls_sizes
/**************************************************************************/

#define type_bit_name_list(_kind_and_size) type_bit_name _kind_and_size
#define scalrs_names MAP_LIST(type_bit_name_list, scalrs_params_kinds_sizes)

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
)                                   \
    scalr_switch_flt(               \
        expr,                       \
        if_flt64bit,                \
        if_flt32bit,                \
        scalr_switch_sint(          \
            expr,                   \
            if_sint64bit,           \
            if_sint32bit,           \
            if_sint16bit,           \
            if_sint8bit,            \
            scalr_switch_uint(      \
                expr,               \
                if_uint64bit,       \
                if_uint32bit,       \
                if_uint16bit,       \
                if_uint8bit,        \
                                    \
                if_no_match         \
            )                       \
        )                           \
    )

#endif
