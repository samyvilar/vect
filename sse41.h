#ifndef SSE41_H // SSE 4.1 ALTERNATIVES ...
#define SSE41_H

#include "macro_utils.h"
#include "scalr_types.h"
#include "intrinsics.h"

#ifndef __SSE4_1__



//__m128i _mm_cvtepi16_epi64 (__m128i a) pmovsxdq
vect_128_intrs_signt(__m128i) _mm_cvtepi16_epi64(__m128i a) {
//#ifdef __SSSE3__
    // 4 cycles ...
    a = _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 0, 0));
    return _mm_unpacklo_epi32(
        _mm_srai_epi32(a, 16),
        _mm_srai_epi32(a, 32)
    );
    // ^^^^^^^^ a16[0], a16[0] < 0, a16[0] < 0, a16[0] < 0, a16[1], a16[1] < 0,  a16[1] < 0,  a16[1] < 0

//    // 5 - 6 cycles ...
//    a = _mm_shufflehi_epi16(_mm_shufflelo_epi16(a, _MM_SHUFFLE(0, 0, 0, 0)), _MM_SHUFFLE(0, 0, 0, 0));
//    return _mm_or_si128(_mm_srli_epi64(a, 48), _mm_slli_epi64(_mm_srai_epi32(a, 32), 16));
}

//__m128i _mm_cvtepi32_epi64 (__m128i a) pmovsxbw
vect_128_intrs_signt(__m128i) _mm_cvtepi32_epi64(__m128i a) { // 2 cycles ...
    return _mm_unpacklo_epi32(a, _mm_srai_epi32(a, 32)); // a32[0], 32 0s or 1s, a32[1], 0s or 1s
}

//__m128i _mm_cvtepi8_epi64 (__m128i a) pmovzxwd
vect_128_intrs_signt(__m128i) _mm_cvtepi8_epi64(__m128i a) { // 5 cycles ...
    a = _mm_unpacklo_epi8(a, a); // a0, a0, a1, a1, ....
    a = _mm_unpacklo_epi16(a, a); // a0, a0, a0, a0, a1, a1, a1, a1

    return _mm_unpacklo_epi32(
        _mm_srai_epi32(a, 24),
        _mm_srai_epi32(a, 32)
    );
}

// __m128i _mm_cvtepu16_epi64 (__m128i a) pmovzxdq
vect_128_intrs_signt(__m128i) _mm_cvtepu16_epi64(__m128i a) {
#ifdef __SSSE3__
    return _mm_shuffle_epi8( // 1 - 2 cycles ...
        a,
        _mm_set_epi8(
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 3, 2,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 1, 0
        )
    );
#else
    return _mm_srli_epi64( // 3 cycles ...
        _mm_shuffle_epi32(
            _mm_shufflelo_epi16(
                a,
                _MM_SHUFFLE(1, 1, 0, 0)
            ),
            _MM_SHUFFLE(1, 1, 0, 0)
        ),
        48
    );
#endif
}

//__m128i _mm_cvtepu32_epi64 (__m128i a) pmovzxbw
vect_128_intrs_signt(__m128i) _mm_cvtepu32_epi64(__m128i a) { // 1 - 2 cycles ...
    return _mm_unpacklo_epi32(a, _mm_setzero_si128());
}

//__m128i _mm_cvtepu8_epi64 (__m128i a)
vect_128_intrs_signt(__m128i) _mm_cvtepu8_epi64(__m128i a) {
#ifdef __SSSE3__
    return _mm_shuffle_epi8( // 1 - 2 cycles ...
        a,
        _mm_set_epi8(
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 1,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0
        )
    );
#else
     // 4 cycles ...
    return _mm_srli_epi64(
        _mm_slli_epi64(
            _mm_unpacklo_epi64(a, _mm_srli_si128(a, 1)),
            56
        ),
        56
    );

#endif
}


vect_128_intrs_signt(__m128i) _mm_cvtepu8_epi16(__m128i a) { // 2 cycles ..    
    return _mm_unpacklo_epi8(a, _mm_setzero_si128());
}

vect_128_intrs_signt(__m128i) _mm_cvtepu8_epi32(__m128i a) { // 3 cycles ...
#ifdef __SSSE3__
    return _mm_shuffle_epi8(
        a,
        _mm_set_epi8(
            0x80, 0x80, 0x80, 3,
            0x80, 0x80, 0x80, 2,
            0x80, 0x80, 0x80, 1,
            0x80, 0x80, 0x80, 0
        )
    );
#else
    a = _mm_unpacklo_epi8(a, a); // a0, a0, a1, a1, a2, a2, a3, a3, ....
    return _mm_srli_epi32(_mm_unpacklo_epi16(a, a), 24);
#endif
}

vect_128_intrs_signt(__m128i) _mm_cvtepi8_epi32(__m128i a) { // 3 cycles ...
    a = _mm_unpacklo_epi8(a, a); // a0, a0, a1, a1, a2, a2, a3, a3, ....
    return _mm_srai_epi32(_mm_unpacklo_epi16(a, a), 24);
}



vect_128_intrs_signt(__m128i) _mm_cvtepi8_epi16(__m128i a) {  // 2 cycles ...
    return _mm_srai_epi16(_mm_unpacklo_epi8(a, a), 8); // a0, a0, a1, a1, a2, a2
}



vect_128_intrs_signt(__m128i) _mm_cvtepi16_epu8(__m128i a) { // 3-4 cycles ..
#ifdef __SSSE3__
    return _mm_shuffle_epi8(
        a,
        _mm_set_epi8( // slightly  faster even if it does access memory
            0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80,
              14,   12,   10,    8,
               6,    4,    2,    0
        )
    );
#else    
    return _mm_packus_epi16( // 3-4 cycles ...
        // clear out top 8 bits otherwise
        // _mm_packus_epi16 will saturate it, to either 255 if gt 255 or 0 if lt 0
        _mm_srli_epi16(_mm_slli_epi16(a, 8), 8),
        _mm_setzero_si128()
    );
#endif
}

vect_128_intrs_signt(__m128i) _mm_cvtepu16_epi32(__m128i a) { // 2 cycles ..
    return _mm_unpacklo_epi16(a, _mm_setzero_si128());
//    return _mm_srli_epi32(_mm_unpacklo_epi16(a, a), 16); may be slower since _mm_srli_epi32 has a higher Throughput than _mm_setzero_si128
}

vect_128_intrs_signt(__m128i) _mm_cvtepi16_epi32(__m128i a) { // 2 cycles ...
    return _mm_srai_epi32(_mm_unpacklo_epi16(a, a), 16);
}


vect_128_intrs_signt(__m128i) _mm_cvtepi32_epu16(__m128i a) { // 4-5 cycles ...
#ifdef __SSSE3__
    return _mm_shuffle_epi8( // 1-2 cycles,
        a,
        _mm_set_epi8(
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
              13,   12,    9,    8,    5,    4,    1,    0
        )
    );
#else    
    return _mm_move_epi64( // 4 cycles ...
        _mm_shuffle_epi32(
            _mm_shufflehi_epi16(
                _mm_shufflelo_epi16(a, _MM_SHUFFLE(3, 1, 2, 0)),
                _MM_SHUFFLE(3, 1, 2, 0)
            ),
        _MM_SHUFFLE(3, 1, 2, 0)
        )
    );
#endif
}



vect_128_intrs_signt(sint_bit_t(64)) _mm_extract_epi64(__m128i a, int _imm) {
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

vect_128_intrs_signt(sint_bit_t(8)) _mm_extract_epi8(__m128i a, int _imm)  {
//    #define _extract_byte_case(i) case i: return _mm_cvtsi128_si32(_mm_srli_si128(a, i));
//    switch (_imm) {
//        MAP(_extract_byte_case, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
//     }
    switch (_imm) {
        case 15: return _mm_cvtsi128_si32(_mm_srli_si128(a, 15));
        case 14: return _mm_cvtsi128_si32(_mm_srli_si128(a, 14));
        case 13: return _mm_cvtsi128_si32(_mm_srli_si128(a, 13));
        case 12: return _mm_cvtsi128_si32(_mm_srli_si128(a, 12));
        case 11: return _mm_cvtsi128_si32(_mm_srli_si128(a, 11));
        case 10: return _mm_cvtsi128_si32(_mm_srli_si128(a, 10));
        case 9:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 9));
        case 8:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 8));
        case 7:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 7));
        case 6:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 6));
        case 5:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 5));
        case 4:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 4));
        case 3:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 3));
        case 2:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 2));
        case 1:  return _mm_cvtsi128_si32(_mm_srli_si128(a, 1));
        case 0:  return _mm_cvtsi128_si32(a);
     }
    return 0;
}



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



vect_128_intrs_signt(int) _mm_test_all_ones(__m128i a) { // 4-5 cycles ...
    return _mm_cvtsi128_si64(_mm_and_si128(a, _mm_srli_si128(a, 8))) == -1LL;
}




#endif


#endif // SSE41_H
