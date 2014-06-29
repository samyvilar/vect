
#ifndef __COMP_ERROR__
#define __COMP_ERROR__

#include <assert.h>

#define assert_with_msg(expr, msg) assert((msg && (expr)))
#define comp_error_init(msg) ({ assert_with_msg(0, msg); (void)0;})
#define comp_error_proc(expr) ({ typeof(expr) __ = (expr); })

#define comp_select     __builtin_choose_expr
#define comp_types_eq   __builtin_types_compatible_p
#define comp_types_neq  !__builtin_types_compatible_p

#define comp_switch_(type_or_expr, ...)

#endif
