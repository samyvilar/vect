#ifndef SSE2_H
#define SSE2_H

#include "intrinsics.h"

#define _mm_setbits_ps(a) _mm_cmpeq_ps(a, a)

#define _mm_setbits_pd(a) _mm_cmpeq_pd(a, a)


#define _mm_setbits_si128(a) _mm_cmpeq_epi32(a, a)  // 1 cycle ...

vect_128_intrs_signt(__m128i) _mm_invert_si128(__m128i a) {
    return _mm_xor_si128(a, _mm_setbits_si128(a)); // returns ~a, 2 cycles ...
}

vect_128_intrs_signt(__m128i) _mm_cmpge_epi32(__m128i a, __m128i b) { // 3 cycles ...
    return _mm_invert_si128(_mm_cmplt_epi32(a, b)); // a >= b == ~(a < b)
}


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


#endif // SSE2_H
