



#include "test_vect_128_bin_oper.h"

#ifndef _test_oper
    #error please specify the vector binary operation name using -D_test_oper=a_oper_name
#endif


int main() {
    printf(
        "test_vect_128_"
        set_str_color("%s", GREEN) "("
        set_str_color("%s", YELLOW) "): "
        ,macro_apply(stringify_token, _test_oper)
        ,macro_apply(stringify_token, _test_type)
    );

        macro_apply(test_vect_128_oper, _test_oper)(_test_type);

    print_ok();

    return 0;
}


