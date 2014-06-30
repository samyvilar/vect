

#include "test_vect_128_bin_oper.h"

int main() {
    printf("test_vect_128_add: ");

    #ifdef enable_test
        MAP_2(_test_vect_128_add, test_memb_types)
    #endif

    print_ok();

    return 0;
}

