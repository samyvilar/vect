
#ifndef __VECT_DEF__
#define __VECT_DEF__

#include "comp_utils.h"
#include "scalr_types.h"

#define vect_comp_err_emit   comp_error_init

#define vect_512_not_supprtd(...) ({vect_comp_err_emit("Theres no support for 512 bit vectors (yet) ..."); })
#define vect_256_not_supprtd(...) ({vect_comp_err_emit("Theres no support for 256 bit vectors (yet) ..."); 0;})
#define vect_128_not_supprtd(...) ({vect_comp_err_emit("Theres no support for 128 bit vectors (yet) ..."); 0;})
#define vect_not_supprtd(vect_s) vect_ ##  vect_s ## _not_supprtd


#define vect_t_name(_vect_bit_mag, _memb_name) vect_ ## _vect_bit_mag ## _ ## _memb_name ## _t
//      ^^^^^^^^^^^ returns the internal type name of a vector with
//                  _vect_bit_mag(512, 256, 128) bits containing
//                  _memb_kind(flt, sint, uint) packed elements each with
//                  _memb_bit_mag(64, 32, 16, 8) bits


#define vect_native_t(_vect_bit_mag, _memb_name) vect_ ##  _vect_bit_mag ## _ ## _memb_name ## _native_t
//      ^^^^^^^^^^^^ returns the intrinsic type containing _vect_bit_mag bits,
//                   containing _memb_kind members each _memb_bit_mag bits


#define vect_typedef(_vect_bit_mag, _memb_name)              \
/*      ^^^^^^^^^^^^ typedef internal vector type of:
        _vect_bit_mag(512, 256, 128) bits holding packed
        _memb_kind(flt, sint, uint) each
        _memb_bit_mag(64, 32, 16, 8) bits */                                \
    typedef union {                                                         \
        vect_native_t(_vect_bit_mag, _memb_name) _v;                         \
                                                                            \
        _memb_name ## _t                                                    \
        _m[sizeof(vect_native_t(_vect_bit_mag, _memb_name))/sizeof(_memb_name ## _t)];\
    } vect_t_name(_vect_bit_mag, _memb_name)

#define vect_native(v) ((v)._v) // returns native intrinsic vect type
#define vect_set_native(v, _v) (vect_native(v) = (_v)) // sets intrinsic vect type

#define vect_membs(v)       ((v)._m)
#define vect_memb(v, i)     (vect_membs(v)[i])
#define vect_memb_t(v)      typeof(vect_memb(v, 0))

#define vect_memb_cnt(v)    (sizeof(vect_membs(v))/sizeof(vect_memb(v, 0)))


#define vect_err_memb_no_suppt(_type) (typeof( ({ (struct vect_memb_no_support {typeof(_type) _invalid_type;}){}; }))){}

#endif
