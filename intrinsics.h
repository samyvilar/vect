#ifndef INTRINSICS_H
#define INTRINSICS_H

#include <immintrin.h>

#ifdef __INTEL_COMPILER // icc doesn't support __nodebug__
#define vect_128_intrs_signt_attrs  __attribute__((__always_inline__))
#else
#define vect_128_intrs_signt_attrs  __attribute__((__always_inline__, __nodebug__))
#endif


#define vect_128_intrs_signt(ret_t) static __inline__ ret_t vect_128_intrs_signt_attrs



#include "sse41.h"
#include "ssse3.h"
#include "sse2.h"


#endif // INTRINSICS_H
