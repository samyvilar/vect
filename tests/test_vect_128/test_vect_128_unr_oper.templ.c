
#include "test_vect_128_unr_oper.h"

#ifndef _test_oper
    #error please specify the vector binary operation name using -D_test_oper=a_oper_name
#endif


int main() {

    run_test_vect_128(_test_oper, macro_apply(test_vect_128_oper, _test_oper), _test_type);

    return 0;
}



