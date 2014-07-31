#ifndef SSSE3_H
#define SSSE3_H

#include "intrinsics.h"


vect_128_intrs_signt(__m128i) _mm_abs_epi8(__m128i a) { // 4 cycles ...
    __m128i sign = _mm_cmplt_epi8(a, _mm_setzero_si128());
    return _mm_sub_epi8(_mm_xor_si128(sign, a), sign); // apply twos complement ...
}

// negate a if b is negative, zero if b is zero, do nothing if b is positive non-zero
// 7 cycles ...
vect_128_intrs_signt(__m128i) _mm_sign_epi8(__m128i a, __m128i b) {
    a = _mm_andnot_si128(_mm_cmpeq_epi8(b, _mm_setzero_si128()), a); // zero out a if b is zero (3 cycles)
    __m128i sign = _mm_cmplt_epi8(b, _mm_setzero_si128()); // 2 cycles ...
    return _mm_sub_epi8(_mm_xor_si128(a, sign), sign); // (2 cycles) apply twos complement ...

    //    return _mm_andnot_si128(
//        _mm_cmpeq_epi8(b, _mm_setzero_si128()),
//        _mm_add_epi8(_mm_xor_si128(a, _mm_cmplt_epi8(b, _mm_setzero_si128())), _mm_srli_epi8(b, 7))
//    );
}


#endif

#endif // SSSE3_H
