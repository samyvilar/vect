
#ifndef __COMP_ERROR__
#define __COMP_ERROR__

#include <assert.h>

#define assert_with_msg(expr, msg) assert((msg && (expr)))
#define comp_error_init(msg) ({ assert_with_msg(0, msg); (void)0;})
#define comp_error_proc(expr) ({ typeof(expr) __ = (expr); })

#define comp_select         __builtin_choose_expr
//      ^^^^^^^^^^^ similar to ?: but requires the conditional to be an immdiate and the types aren't modified ...

#define comp_types_eq       __builtin_types_compatible_p
//      ^^^^^^^^^^^^^   compares two types returns 1 if they equal or if typedef, their underlying types match, otherwise 0
//                  compilation error if args are not types at all ....

#define comp_types_neq      !__builtin_types_compatible_p
//      ^^^^^^^^^^^^^^ inverts comp_types_eq

#define comp_expr_is_imm    __builtin_constant_p
//      ^^^^^^^^^^^^^^^^ returns 0 if expression is a compile time constant otherwise 0 ...
//              compilation error if argument is not an expression ...

#endif
