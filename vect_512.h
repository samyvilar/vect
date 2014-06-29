
#ifndef __VECT_512__
#define __VECT_512__

#include "vect_def.h"

#define vect_512_flt32bit_supprt  0
#define vect_512_flt64bit_supprt  0
#define vect_512_sint8bit_supprt  0
#define vect_512_sint16bit_supprt 0
#define vect_512_sint32bit_supprt 0
#define vect_512_sint64bit_supprt 0
#define vect_512_uint8bit_supprt  0
#define vect_512_uint16bit_supprt 0
#define vect_512_uint32bit_supprt 0
#define vect_512_uint64bit_supprt 0


#define vect_512_no_supprt vect_not_supprtd(512)

#define _vect_512_t             vect_512_no_supprt
#define vect_512_t              vect_512_no_supprt

#define vect_512_load           vect_512_no_supprt
#define vect_512_load_align     vect_512_no_supprt
#define vect_512_store          vect_512_no_supprt
#define vect_512_store_algin    vect_512_no_supprt

#define vect_512_broad_cast     vect_512_no_supprt
#define vect_512_add            vect_512_no_supprt
#define vect_512_sub            vect_512_no_supprt
#define vect_512_mul            vect_512_no_supprt
#define vect_512_div            vect_512_no_supprt

#define vect_512_lshft          vect_512_no_supprt

#define vect_512_rshft_arith    vect_512_no_supprt
#define vect_512_rshft_logic    vect_512_no_supprt

#define vect_512_extrt          vect_512_no_supprt

#define vect_512_sign_ext       vect_512_no_supprt


#endif
