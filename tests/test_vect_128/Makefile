
CC=gcc
CFLAGS=-Wall -Wfatal-errors

#$(call test_vect_128_, file_name)
define test_vect_128_
    $(CC) $(CFLAGS) $1.c -o $1
    ./$1
endef

test_vect_128_files=$(shell ls test_vect_128_*.c | xargs -n1 basename -s .c)

%: %.c
	$(call test_vect_128_,$@)

test: $(test_vect_128_files)

clean:
	rm -f $(test_vect_128_files)




