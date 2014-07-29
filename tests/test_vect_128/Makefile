
CC=gcc

CFLAGS=-Wfatal-errors
ifeq ($(CC),gcc)
CFLAGS+=-fmacro-backtrace-limit=0
endif

test_flt_types=float double
test_scalr_sint_types=signed_long_long_int signed_long_int signed_int int signed_short_int short_int short signed_char char
test_scalr_uint_types=unsigned_long_long_int unsigned_long_int unsigned_int unsigned_short unsigned_char
test_scalr_types=$(test_flt_types) $(test_scalr_sint_types) $(test_scalr_uint_types)

test_typedef_native_sclar_types=double_t float_t sllint_t slint_t sint_t s_t int_t ssint_t sshort_t schar_t char_t ullint_t ulint_t uint_t u_t usint_t ushort_t uchar_t

test_vect_comp_types=$(test_scalr_types) $(test_typedef_native_sclar_types)

test_opers=decl broad_cast
test_unr_opers=sign_ext_unr

arg_cnt_kinds=bin

shift_kinds=lshift rshift_logic rshift_arith
shift_mag_kinds=imm scalr
shift_test_opers=$(foreach shft,$(shift_kinds),\
$(foreach mg_t,$(shift_mag_kinds),\
$(foreach arc,$(arg_cnt_kinds),$(shft)_$(mg_t)_$(arc))))

load_test_opers=load_unr load_align_unr load_unr_vect_128_p load_align_unr_vect_128_p
store_test_opers=store store_align
test_bin_opers=extrt_imm set $(load_test_opers) $(store_test_opers) xor_bin and_bin or_bin add_bin sub_bin mul_bin $(shift_test_opers), div

v=@

define test_vect_128_
	$(v)$(CC) $(CFLAGS) -D_test_oper=$(1) -D_test_type=$(2) test_vect_128_$(3).templ.c -o test_vect_128_$(1)_$(2).out
	$(v)./test_vect_128_$(1)_$(2).out


endef

define get_test_names
$(foreach kind,$(test_vect_comp_types),test_vect_128_$(1)_$(kind))
endef

test_vect_128_shifts: $(foreach opr,$(shift_test_opers),$(call get_test_names,$(opr)))

test_vect_128_loads: $(foreach opr,$(load_test_opers),$(call get_test_names,$(opr)))

test_vect_128_broad_casts: $(call get_test_names,broad_cast)

test_vect_128_bit_opers: $(foreach op,xor_bin xor_tnr and_bin and_tnr or_bin or_tnr,$(call get_test_names,$(op)))

define test_vect_128_templ_oper_kind
test_vect_128_$(1)_$(2):
$(call test_vect_128_,$(1),$(2),$(3))
endef


$(foreach oper,$(test_bin_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),bin_oper))))


$(foreach oper,$(test_unr_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),unr_oper))))


$(foreach oper,$(test_opers),$(foreach kind,$(test_vect_comp_types),$(eval $(call test_vect_128_templ_oper_kind,$(oper),$(kind),$(oper)))))


define test_vect_128_assembly
test_vect_128_$(1)_$(2)_native:
	@$(CC) $(CFLAGS) -S -fno-verbose-asm -D_test_oper=$(1)_native -D_test_type=$(2) test_vect_128_native.templ.c -o test_vect_128_$(1)_$(2)_native.s
	@$(CC) $(CFLAGS) -S -fno-verbose-asm -D_test_oper=$(1)_vect   -D_test_type=$(2) test_vect_128_native.templ.c -o test_vect_128_$(1)_$(2)_vect.s
	@diff test_vect_128_$(1)_$(2)_native.s test_vect_128_$(1)_$(2)_vect.s
	@echo "test_vect_128_$$$$(tput setaf 2)$(1)_native$$$$(tput sgr0)($$$$(tput setaf 3)$(2)$$$$(tput sgr0)): $$$$(tput setaf 2)ok.$$$$(tput sgr0)"


endef

assembly_tests=broad_cast_unr load_unr load_align_unr store store_align
$(foreach o,$(assembly_tests),\
$(foreach t,$(test_vect_comp_types),\
$(eval $(call test_vect_128_assembly,$(o),$(t),broad_cast))))

test_vect_128_native: $(foreach oper,$(assembly_tests),$(foreach kind,$(test_vect_comp_types),test_vect_128_$(oper)_$(kind)_native))


test: $(foreach oper,$(test_opers) $(test_unr_opers) $(test_bin_opers),\
$(foreach kind,$(test_vect_comp_types),test_vect_128_$(oper)_$(kind))) test_vect_128_native

clean:
	rm -f test_vect_128_*.out
	rm -f test_vect_128_*.s




