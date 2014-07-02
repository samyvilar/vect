
CC=gcc
CFLAGS=-Wall -Wfatal-errors

test_flt_types=float double
test_scalr_sint_types=signed_long_long_int signed_long_int signed_int int signed_short_int short_int short signed_char char
test_scalr_uint_types=unsigned_long_long_int unsigned_long_int unsigned_int unsigned_short unsigned_char
test_scalr_types=$(test_flt_types) $(test_scalr_sint_types) $(test_scalr_uint_types)

test_typedef_native_sclar_types=double_t float_t sllint_t slint_t sint_t s_t int_t ssint_t sshort_t schar_t char_t ullint_t ulint_t uint_t u_t usint_t ushort_t uchar_t

test_vect_comp_types=$(test_scalr_types) $(test_typedef_native_sclar_types)

test_bin_opers=xor and or add sub mul

test_opers=decl broad_cast load set

define test_vect_128_
	@$(CC) $(CFLAGS) -D_test_oper=$(1) -D_test_type=$(2) test_vect_128_$(3).templ.c -o test_vect_128_$(1)_$(2).out
	@./test_vect_128_$(1)_$(2).out


endef

define test_vect_128_templ_oper_kind
test_vect_128_$(1)_$(2):
$(call test_vect_128_,$(1),$(2),$(3))
endef

$(foreach oper,$(test_bin_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),bin_oper))))

$(foreach oper,$(test_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),$(oper)))))

test: $(foreach oper,$(test_opers) $(test_bin_opers),$(foreach kind,$(test_vect_comp_types),test_vect_128_$(oper)_$(kind)))

clean:
	rm -f test_vect_128_*.out




