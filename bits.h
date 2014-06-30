
#ifndef __BITS__
#define __BITS__

#include <assert.h>
#include <limits.h>

#include "scalr_types.h"
#include "comp_utils.h"


#define BYTE_BIT_SIZE                   (sizeof(char) * CHAR_BIT)
#define pow_2(value)                    ((typeof(value))1 << (value))
#define bit_cnt(byte_cnt)               ((byte_cnt) * BYTE_BIT_SIZE)
#define bit_size(type)                  (sizeof(type) * BYTE_BIT_SIZE)
#define addr_not_aligned(addr, type)    ((addr) % sizeof(type))

// return a seq of ones, using the fact that 0b100000 - 1 == 0b011111, that has the same type as bit_cnt
#define ones(bit_cnt) ((typeof(bit_cnt)1 << (bit_cnt)) - 1)

#define instr_postfix_1 "b" // byte
#define instr_postfix_2 "w" // short
#define instr_postfix_4 "l" // int
#define instr_postfix_8 "q" // long
#define get_instr_postfix(size) instr_postfix_ ## size
#define att_instr(instr_name, operand_size) instr_name get_instr_postfix(operand_size)

#define intrsc_signat(ret_type) __inline ret_type __attribute__((__gnu_inline__, __always_inline__, __artificial__))
#ifdef __INTEL_COMPILER // icc doesn't have __builtin_clzs or __builtin_ctz which is kind of strange
    intrsc_signat(unsigned) __builtin_clzs(unsigned short x) { // count leading zeros, return 15 if all zeros ...
        asm     (att_instr("bsr", 2) " %0, %0\t\nxor $15, %0\t\n" : "=r" (x) : "0"(x));
        return x;
    }

    intrsc_signat(unsigned) __builtin_ctzs(unsigned short x) { // count trailing zeros, return 0 if 0 ...
        asm (att_instr("bsf", 2) " %0, %0" : "=r" (x) : "0"(x));
        return x;
    }

    intrsc_signat(unsigned) __builtin_popcounts(unsigned short x) { // count set 1s return 0 if 0
        return __builtin_popcount(x) - 8;
    }
#endif

// there is no instruction that supports bit scan on a char ...

#define __builtin_clzb(x) (cnt_leadn_zrs_16((unsigned char)(x)) ^ 8) // subtract leading 8 zeros ...
#define __builtin_ctzb(x) cnt_trlng_zrs_16((unsigned char)(x))
#define __builtin_popcountb(x) bit_ones_cnt_16((unsigned char)(x))


#define cnt_leadn_zrs_8 __builtin_clzb
#define cnt_leadn_zrs_16 __builtin_clzs
#define cnt_leadn_zrs_32 __builtin_clz
#define cnt_leadn_zrs_64 __builtin_clzll   


#define cnt_trlng_zrs_8 __builtin_ctzb
#define cnt_trlng_zrs_16 __builtin_ctzs
#define cnt_trlng_zrs_32 __builtin_ctz
#define cnt_trlng_zrs_64 __builtin_ctzll

#define cnt_trlng_zrs(x) singl_param_integral_macro(cnt_trlng_zrs_, x, unsigned)
//#define cnt_trlng_zrs(a) ({                             \
//    unsigned _cnt_;                                     \
//    switch (sizeof(a)) {                                \
//        case 1: _cnt_ = cnt_trlng_zrs_8(a); break ;     \
//        case 2: _cnt_ = cnt_trlng_zrs_16(a); break ;    \
//        case 4: _cnt_ = cnt_trlng_zrs_32(a); break ;    \
//        case 8: _cnt_ = cnt_trlng_zrs_64(a); break ;    \
//    } _cnt_;})


// theres no intrinsic for counting set bits on bytes so we need to convert it to an unsigned short...
#define bit_ones_cnt_8(x) __builtin_popcounts(uint_byt_t(2)(x))
#define bit_ones_cnt_16 __builtin_popcounts
#define bit_ones_cnt_32 __builtin_popcount
#define bit_ones_cnt_64 __builtin_popcountll

#define bit_ones_cnt(x) singl_param_integral_macro(bit_ones_cnt_, x, unsigned)
//#define bit_ones_cnt(a) ({                          \
//    unsigned cnt;                                   \
//    switch(sizeof(a)) {                             \
//        case 1: cnt = bit_ones_cnt_8(a); break ;    \
//        case 2: cnt = bit_ones_cnt_16(a); break ;   \
//        case 4: cnt = bit_ones_cnt_32(a); break ;   \
//        case 8: cnt = bit_ones_cnt_64(a); break ;   \
//     } cnt;})


// returns 0 if x is zero, or 1 if non_zero, by shifting the most significant set bit to the least significant position
// __builtin_clz returns the number of leading zeros,
// so the index of the most significant 1 (assuming little endian) must be the bitsize - trailing_zero_cnt
// so simply shift the value by this index - 1, so we either get 1 or 0, if it was zero.
//#define bool_int(x)  ((unsigned)(x) >>      ((bit_size(x) - 1) - cnt_leadn_zrs_32((unsigned)(x))))
//#define bool_long(x) ((unsigned long)(x) >> ((bit_size(x) - 1) - cnt_leadn_zrs_64((unsigned long)(x))))

#define bool_by_bit_shft(a) ({typeof(a) _sb = (a); rshift_logic(_sb, leadn_one_index(_sb));})
#define bool_by_logical(a) (!!(a))
#define bool bool_by_logical

// xor the bits of a, b (both must be of equal size) returns the same type as a ...
#define bits_xor(a, b) ({                                   \
    assert(sizeof(a) == sizeof(b));                         \
    types_t _oprn_a, _oprn_b;                               \
    types_init(_oprn_a, a);                                 \
    types_init(_oprn_a, b);                                 \
    switch (sizeof(a))     {                                \
        case 1: _oprn_a.u_char  ^= _oprn_b.u_char;  break ; \
        case 2: _oprn_a.u_short ^= _oprn_b.u_short; break ; \
        case 4: _oprn_a.u_int   ^= _oprn_b.u_int;   break ; \
        case 8: _oprn_a.u_long  ^= _oprn_b.u_long;  break ; \
        default: assert(0);                                 \
    }                                                       \
_oprn_a; })
// set mask
#define bool_mask_p(x) ((signed word_t)(cast_ptr(x) << __builtin_clzll(cast_ptr(x))) >> (bit_size(word_t) - 1))



// returns expr_on_true if cond is non-zero otherwise expr_on_false is returned,
// it uses the following  A & -1 = A, A ^ 0 = A, A ^ A = 0, so A ^ B ^ A = B for branchless code ..
#define select_expr_xor(cond, expr_on_true, expr_on_false) (\
    (bool_mask_p(cond) & (cast_ptr(expr_on_true) ^ cast_ptr(expr_on_false))) ^ cast_ptr(expr_on_false))


#define swap_by_temp(a, b) ({typeof(a) _temp = (a); (a) = (b); (b) = _temp;}) // swap using temp variable ...



#define xor_ptrs(a, b)       ((void *)(cast_ptr(a) ^ cast_ptr(b)))
//#define xor_swap_p(a, b)     ((a = xor_ptrs(a, b)), (b = xor_ptrs(b, a)), (a = xor_ptrs(a, b))) // swap pointer unsafe ...
//#define xor_swap_p(a, b) ({ptr_to_int_t int_a = cast_ptr(a), int_b = cast_ptr(b); int_a ^= int_b; int_b ^= int_a; int_a ^= int_b; a = (void *)int_a; b = (void *)int_b;})

#define xor_swap_p_mask(a, b, mask)  ((a = xor_ptrs(a, (cast_ptr(b) & (word_t)(mask)))), (b = xor_ptrs(b, (cast_ptr(a) & (word_t)(mask)))), (a = xor_ptrs(a, (cast_ptr(b) & (word_t)(mask))))) // swap pointer unsafe ...
#define xor_swap_p_safe(a, b) ((&(a) != &(b)) && xor_swap_p(a, b))

#define xor_swap(a, b)      (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) // in place swap, unsafe it assume a, b are two diff addr locs

#define swap_xchg_1(a, b)  ({asm(att_instr("xchg", 1) " %0, %1" : "=r"(a), "=r"(b) : "0"(a), "1"(b));})
#define swap_xchg_2(a, b)  ({asm(att_instr("xchg", 2) " %0, %1" : "=r"(a), "=r"(b) : "0"(a), "1"(b));})
#define swap_xchg_4(a, b)  ({asm(att_instr("xchg", 4) " %0, %1" : "=r"(a), "=r"(b) : "0"(a), "1"(b));})
#define swap_xchg_8(a, b)  ({asm(att_instr("xchg", 8) " %0, %1" : "=r"(a), "=r"(b) : "0"(a), "1"(b));})
//#define swap_4_xchng xor_swap

#define instr(instr, size) instr ## size

#define swap(a, b) ({       \
    switch(sizeof(a)) {\
        case 1: instr(swap_xchg_, 1)(a, b); break ;\
        case 2: instr(swap_xchg_, 2)(a, b); break ;\
        case 4: instr(swap_xchg_, 4)(a, b); break ;\
        case 8: instr(swap_xchg_, 8)(a, b); break ;\
    }\
})



#define sign_bit_ext(a) rshift_arith(a, (bit_size(a) - 1))  // extends the sign bit creating a mask of ones or zeros..
// the following is faster on cpu with slow shifts, assuming little endian architecture ...
#define sign_ext_by_mem(a) 	((typeof(a))(((union {long long val; struct {int low, high;};}){.val = (a)}).high))

#define sign_bit_bool(a)  // rshift_logcl(a, (bit_size(a) - 1)) // returns 0 if sign bit is 0 or 1 if sign bits is 1 (so it just moves the sign from ms loc to ls loc ...) (((unsigned long long)(a) >> (bit_size(unsigned long long) - 1)) & 1LLU)

#define sign_ext   sign_bit_ext

// min-max functions ...
#define min_by_cmp(a, b)        (((a) < (b)) ? (a) : (b))
#define max_by_cmp(a, b)        (((a) < (b)) ? (b) : (a))
// branchless min/max counterparts ...
#define min_by_subt(a, b)    	((b) + (((a) - (b)) & sign_ext((a) - (b))))
#define max_by_subt(a, b)		((a) + (((b) - (a)) & sign_ext((a) - (b))))

#define min_by_xor(a, b)    	((b) ^ (((a) ^ (b)) & sign_bit_ext((a) - (b))))
#define max_by_xor(a, b)        ((a) ^ (((a) ^ (b)) & sign_bit_ext((a) - (b))))

// a bit safer since the exprs are temporary copied and the exprs only appear twice withing the macro
#define min_by_subt_cpy(a, b)    ((typeof(a)[2]){(b), (a)}[sign_bit_bool((a) - (b))])
#define max_by_subt_cpy(a, b)    ((typeof(a)[2]){(a), (b)}[sign_bit_bool((a) - (b))])

#define min min_by_subt
#define max max_by_subt

#define max_p(a, b) ((void *)max(cast_ptr(a), cast_ptr(b)))
#define min_p(a, b) ((void *)min(cast_ptr(a), cast_ptr(b)))

#define zero_out(ptr, byte_cnt) memset(ptr, 0, byte_cnt)


// BIT FIELD ...
#define bit_fld_t unsigned word_t
#define bit_fld_mag(mag)            (((mag) / bit_size(bit_fld_t)) + bool((mag) % bit_size(bit_fld_t)))

#define bit_fld_def(name, mag)      bit_fld_t name[bit_fld_mag(mag)]

#define bit_fld_elem_cnt(bit_cnt)   ((bit_cnt) / bit_size(bit_fld_elem_t))

#define bit_fld_word(fld, index)      ((fld)[((index) / bit_size((fld)[0]))])
#define bit_fld_mask(fld, index)      ((typeof((fld)[0]))1 << ((index) % bit_size((fld)[0])))
#define bit_fld_opr(fld, index, oper) (bit_fld_word(fld, index) oper bit_fld_mask(fld, index))
#define bit_fld_set_bit(fld, index)   bit_fld_opr(fld, index, |=)
#define bit_fld_clr_bit(fld, index)   bit_fld_opr(fld, index, &= ~)
#define bit_fld_bit(fld, index)       bit_fld_opr(fld, index, &)


typedef struct packed_bits_t {  // represents a set of packed bits, used to store and retrieve variable number of bits..
    unsigned word_t             // unlike a bitfield which can only and set/clr a single bit, this structure can set and retrieve a variable number of bits up to sizeof(unsigned word_t) bits ...
        *_bits,                 // seq of bits ...
        _bit_size;              // number of total available bits ....
} packed_bits_t;

#define packed_bits_fld(pbits) ((pbits)->_bits)
#define packed_bits_set_fld(pbits, bits) (packed_bits(pbits) = (bits))

#define packed_bits_bit_cnt(pbits) ((pbits)->_bit_size)
#define packed_bits_set_bit_cnt(pbits, cnt) (packed_bits_bit_cnt(pbits) = (cnt))

#define packed_bits_empty(pbits) (!(packed_bits_bit_cnt(pbits) && packed_bits_fld(pbits)))

#define packed_bits_word_indx(pbits, index, bit_mag) (((bit_mag) * (index)) / bit_size(packed_bits_fld(pbits)[0]))
#define packed_bits_bit_indx(pbits, index, bit_mag)  (((bit_mag) * (index)) % bit_size(packed_bits_fld(pbits)[0]))

#define packed_bits_word(pbits, index, bit_mag) (packed_bits_fld(pbits)[packed_bits_word_indx(pbits, index, bit_mag)])

#define packed_bits_mask(pbits, index, bit_mag) ({                                                      \
    typeof(packed_bits_fld(pbits)[0]) _mask = (typeof(packed_bits_fld(pbits)[0]))-1;                    \
    unsigned _trailing_zers_cnt = packed_bits_bit_indx(pbits, index, _bit_mag);                         \
    unsigned _leading_zers_cnt = max(0, (bit_size(_mask) - (trailing_zeros_cnt + _bit_mag)));           \
    rshift_logic(_mask, _leading_zers_cnt) & (_mask << _trailing_zers_cnt);                             \
})



#define packed_bits_get(pbits, index, bit_mag)  ({                                                          \
                                                                                                            \
    typeof(pbits) _pbits = (pbits);                                                                         \
    word_t _index = (index),                                                                                \
        _bit_mag = (bit_mag),                                                                               \
        _word_index = packed_bits_word_indx(_pbits, _index, _bit_mag),                                      \
        _cnt;                                                                                               \
                                                                                                            \
    typeof(packed_bits_fld(_pbits)[0])) _mask = packed_bits_mask(_pbits, _index, _bit_mag);                 \
    uint_bit_t(64) _entry = (packed_bits_fld(pbits)[_word_index++] & _mask)                                 \
                                >> packed_bits_bit_indx(_pbits, _index, _bit_mag);                          \
    _cnt = bit_ones_cnt(_mask);                                                                             \
    for (_bit_mag -= cnt; _bit_mag < bit_size(_mask) && _cnt < _bit_mag; _word_index++) {                   \
        _entry |= (typeof(_entry))packed_bits_fld(pbits)[_word_index] << _cnt;                              \
        _cnt += bit_size(_mask);                                                                            \
        _bit_mag -= bit_size(_mask);                                                                        \
    }                                                                                                       \
    _entry | ((packed_bits_fld(pbits)[_word_index] & ((typeof(_mask)1 << _bit_mag) - 1)) << _cnt); })

#define packed_bits_set(pbits, index, value, bit_mag)  ({   \
    packed_bits_word(pbits, index, bit_mag) &= ~mask(pbits, index, bit_mag);    \
    packed_bits_word(pbits, index, bit_mag) |=  \
        ((value & ones(bit_mag)) << packed_bits_bit_indx(pbits, index, bit_mag));    \
)


#define bits_intrp_as_dbl(a)  (((union {double _d; typeof(a) _value;}){._value = (a)})._d)
#define bits_intrp_as_sngl(a) (((union {float _s; typeof(a) _value;}){._value = (a)})._s)   


#define cnt_leadn_zrs(x)        \
    scalr_switch(               \
        x,                      \
        cnt_leadn_zrs_64(_interp(x, flt_bit_t(64), sint_bit_t(64))),    \
        cnt_leadn_zrs_32(_interp(x, flt_bit_t(32), sint_bit_t(32))),    \
        cnt_leadn_zrs_64(x), cnt_leadn_zrs_32(x), cnt_leadn_zrs_16(x), cnt_leadn_zrs_8(x),     \
        cnt_leadn_zrs_64(x), cnt_leadn_zrs_32(x), cnt_leadn_zrs_16(x), cnt_leadn_zrs_8(x),     \
        (void)0 \
    )
#define leadn_one_index(x) (bit_size(x) - cnt_leadn_zrs(x))


#define rand_entropy_bit_mag leadn_one_index(RAND_MAX) // rands number of bits
#define rand_enty_cnt(_t) ((bit_size(_t)/rand_entropy_bit_mag) + !!(bit_size(_t) % rand_entropy_bit_mag))

#define bits_rand(_t) ({                                                                \
    int _rand_bits[rand_enty_cnt(_t)];                                                  \
    unsigned _index, _set_bit_cnt;                                                      \
    for (_index = 0; _index < (sizeof(_rand_bits)/sizeof(_rand_bits[0])); _index++) {   \
        _rand_bits[_index] = 0;                                                         \
        for (_set_bit_cnt = 0; _set_bit_cnt < bit_size(_rand_bits[0]); _set_bit_cnt += rand_entropy_bit_mag)\
            _rand_bits[_index] |= rand() << _set_bit_cnt;                               \
    } scalr_switch(                                                                     \
        _t,                                                                             \
        ((*(sint_bit_t(64) *)_rand_bits) / ((double)(-1LLU))),                          \
        ((*(sint_bit_t(32) *)_rand_bits) / (float)(-1U)),                               \
        *(sint_bit_t(64) *)_rand_bits,                                                  \
        *(sint_bit_t(32) *)_rand_bits,                                                  \
        *(sint_bit_t(16) *)_rand_bits,                                                  \
        *(sint_bit_t(8) *)_rand_bits,                                                   \
        *(uint_bit_t(64) *)_rand_bits,                                                  \
        *(uint_bit_t(32) *)_rand_bits,                                                  \
        *(uint_bit_t(16) *)_rand_bits,                                                  \
        *(uint_bit_t(8) *)_rand_bits,                                                   \
        (void)0                                                                         \
    ); })
/* ^^^^^^^^^^^^^^^^^^^^^^^^ returns a random number from a type or expr, if type is flt,
 *                returns a number from -1 to 1
 *                for integral types simply sets the appropriate number of bits
 *                 returns the bits interpreted as _t.
 */                                                                                     \



#endif
