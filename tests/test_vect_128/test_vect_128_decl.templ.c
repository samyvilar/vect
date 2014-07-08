
#include "test_vect_128_common.h"

#define error_if_memb_t_not(v, exp_t)                                       \
    comp_select(                                                            \
        scalr_types_neq(vect_memb_t(v), exp_t),                             \
        error_with_format(                                                  \
            "Error expected a vector with member type `%s`\n", #exp_t       \
        ),                                                                  \
        (void)0                                                             \
    )


int main() { // test vect_128 declarations ....
    #define _test_vect_128_decl_by_type_name(_memb_type)    \
        error_if_memb_t_not((vect_128_t(_memb_type)){}, _memb_type)

    #define _test_vect_128_decl_by_expr(_memb_type)         \
        error_if_memb_t_not((vect_128_t((typeof(_memb_type))0)){}, typeof(_memb_type))

    #define _test_vect_128_decl_void(_memb_type)  ({                        \
        if (!comp_types_eq(vect_128_t(union {_memb_type _;}), void))        \
            error("failed to handle vect_128_t non-scalar member type ...\n");})

    #define _test_vect_128_decl_default(_memb_type) ({                  \
    if (!comp_types_eq(vect_128_t(union {}, (_memb_type)0), _memb_type))   \
        error("failed to return default type while creating a non supported vect_128_t member type ...\n");\
    })

    run_test_vect_128(decl_by_type, _test_vect_128_decl_by_type_name, _test_type);

    run_test_vect_128(decl_by_expr, _test_vect_128_decl_by_expr, (_test_type)0);

    run_test_vect_128(decl_void, _test_vect_128_decl_void, _test_type);

    run_test_vect_128(decl_default, _test_vect_128_decl_default, _test_type);

    return 0;
}





