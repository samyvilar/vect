
CC=gcc
CFLAGS=-Wall -Wfatal-errors

test_flt_types=float double
test_scalr_sint_types=signed_long_long_int signed_long_int signed_int int signed_short_int short_int short signed_char char
test_scalr_uint_types=unsigned_long_long_int unsigned_long_int unsigned_int unsigned_short unsigned_char
test_scalr_types=$(test_flt_types) $(test_scalr_sint_types) $(test_scalr_uint_types)

test_typedef_native_sclar_types=double_t float_t sllint_t slint_t sint_t s_t int_t ssint_t sshort_t schar_t char_t ullint_t ulint_t uint_t u_t usint_t ushort_t uchar_t

test_vect_comp_types=$(test_scalr_types) $(test_typedef_native_sclar_types)

test_opers=decl broad_cast load store set
test_unr_opers=sign_ext
test_bin_opers=xor and or add sub mul lshift_imm lshift_scalr lshift rshift_logic_imm rshift_logic_scalr rshift_logic rshift_arith_imm rshift_arith_scalr rshift_arith


define test_vect_128_
	@$(CC) $(CFLAGS) -D_test_oper=$(1) -D_test_type=$(2) test_vect_128_$(3).templ.c -o test_vect_128_$(1)_$(2).out
	@./test_vect_128_$(1)_$(2).out


endef

define test_vect_128_templ_oper_kind
test_vect_128_$(1)_$(2):
$(call test_vect_128_,$(1),$(2),$(3))
endef


$(foreach oper,$(test_bin_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),bin_oper))))


$(foreach oper,$(test_unr_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),unr_oper))))


$(foreach oper,$(test_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),$(oper)))))


define test_vect_128_assembly
test_vect_128_$(1)_$(2)_native:
	@$(CC) $(CFLAGS) -S -D_test_oper=$(1)_native -D_test_type=$(2) test_vect_128_$(3)_native.templ.c -o test_vect_128_$(1)_$(2)_native.s
	@$(CC) $(CFLAGS) -S -D_test_oper=$(1)_vect   -D_test_type=$(2) test_vect_128_$(3)_native.templ.c -o test_vect_128_$(1)_$(2)_vect.s
	@diff test_vect_128_$(1)_$(2)_native.s test_vect_128_$(1)_$(2)_vect.s
	@echo "test_vect_128_$$$$(tput setaf 10)$(1)_native$$$$(tput sgr0)($$$$(tput setaf 3)$(2)$$$$(tput sgr0)): $$$$(tput setaf 10)ok.$$$$(tput sgr0)"


endef

assembly_tests=broad_cast_unr broad_cast_bin
$(foreach o,$(assembly_tests),\
$(foreach t,$(test_vect_comp_types),\
$(eval $(call test_vect_128_assembly,$(o),$(t),broad_cast))))

test_vect_128_native: $(foreach oper,$(assembly_tests),$(foreach kind,$(test_vect_comp_types),test_vect_128_$(oper)_$(kind)_native))

test: $(foreach oper,$(test_opers) $(test_unr_opers) $(test_bin_opers),\
$(foreach kind,$(test_vect_comp_types),test_vect_128_$(oper)_$(kind))) $(test_vect_128_native)

clean:
	rm -f test_vect_128_*.out
	rm -f test_vect_128_*.s




