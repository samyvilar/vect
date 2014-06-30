

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
        error_if_memb_t_not((vect_128_t(_memb_type)){}, _memb_type);

    #define _test_vect_128_decl_by_expr(_memb_type)         \
        error_if_memb_t_not((vect_128_t((_memb_type)0)){}, _memb_type);

    printf("test_vect_128_decl: ");

#ifdef enable_test
    MAP_2(_test_vect_128_decl_by_type_name, test_memb_types)

    if (!comp_types_eq(vect_128_t(union {}), void))
        error("failed to handle vect_128_t non-scalar member type ...\n");

    if (!comp_types_eq(vect_128_t(union {}, int), int))
        error("failed to return default type while creating a non supported vect_128_t member type ...\n");
#endif
    print_ok();
}





