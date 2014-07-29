
#ifndef __MACRO_UTILS__
#define __MACRO_UTILS__

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0 (EVAL0 (EVAL0 (__VA_ARGS__)))
#define EVAL2(...) EVAL1 (EVAL1 (EVAL1 (__VA_ARGS__)))
#define EVAL3(...) EVAL2 (EVAL2 (EVAL2 (__VA_ARGS__)))
#define LARGEST_EVAL_LEVEL  EVAL3
//#define EVAL4(...) EVAL3 (EVAL3 (EVAL3 (__VA_ARGS__)))
//#define EVAL5(...) EVAL4 (EVAL4 (EVAL4 (__VA_ARGS__)))
//#define EVAL(...)  LARGEST_EVAL_LEVEL (LARGEST_EVAL_LEVEL (LARGEST_EVAL_LEVEL (__VA_ARGS__)))
#define EVAL(...)  LARGEST_EVAL_LEVEL (LARGEST_EVAL_LEVEL (__VA_ARGS__))

#define MAP_END(...)

#define MAP_OUT
#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(item, next, ...) next MAP_OUT // consume item return next ...
#define MAP_NEXT1(item, next) MAP_NEXT0 (item, next) //
#define MAP_NEXT(item, next, _end) MAP_NEXT1 (item _end, next) // returns either next (MAP0, MAP1) or MAP_END if item is MAP_GET_END


#define MAP0(f, x, peek, _end, ...) f(x) MAP_NEXT (peek, MAP1, _end) (f, peek, _end, __VA_ARGS__)
#define MAP1(f, x, peek, _end, ...) f(x) MAP_NEXT (peek, MAP0, _end) (f, peek, _end, __VA_ARGS__)

#define MAP(f, ...) EVAL (MAP1 (f, __VA_ARGS__, MAP_GET_END, (), 0))


/* MAP_2 **********************************************************************/
#define EVAL0_2(...) __VA_ARGS__
#define EVAL1_2(...) EVAL0_2 (EVAL0_2 (EVAL0_2 (__VA_ARGS__)))
#define EVAL2_2(...) EVAL1_2 (EVAL1_2 (EVAL1_2 (__VA_ARGS__)))
#define EVAL3_2(...) EVAL2_2 (EVAL2_2 (EVAL2_2 (__VA_ARGS__)))
//#define EVAL4_2(...) EVAL3_2 (EVAL3_2 (EVAL3_2 (__VA_ARGS__)))
#define LARGEST_EVAL_LEVEL_2  EVAL3_2
#define EVAL_2(...)  LARGEST_EVAL_LEVEL_2 (LARGEST_EVAL_LEVEL_2 (__VA_ARGS__))

#define MAP_END_2(...)

#define MAP_OUT_2
#define MAP_GET_END_2() 0, MAP_END_2
#define MAP_NEXT0_2(item, next, ...) next MAP_OUT // consume item return next ...
#define MAP_NEXT1_2(item, next) MAP_NEXT0_2 (item, next) //
#define MAP_NEXT_2(item, next, _end) MAP_NEXT1_2 (item _end, next) // returns either next (MAP0, MAP1) or MAP_END if item is MAP_GET_END


#define MAP0_2(f, x, peek, _end, ...) f(x) MAP_NEXT_2 (peek, MAP1_2, _end) (f, peek, _end, __VA_ARGS__)
#define MAP1_2(f, x, peek, _end, ...) f(x) MAP_NEXT_2 (peek, MAP0_2, _end) (f, peek, _end, __VA_ARGS__)

#define MAP_2(f, ...) EVAL_2 (MAP1_2 (f, __VA_ARGS__, MAP_GET_END_2, (), 0))
/****************************************************************************************************/





#define MAP0_LIST(f, x, peek, _end, ...) , f(x) MAP_NEXT (peek, MAP1_LIST, _end) (f, peek, _end, __VA_ARGS__)
#define MAP1_LIST(f, x, peek, _end, ...) , f(x) MAP_NEXT (peek, MAP0_LIST, _end) (f, peek, _end, __VA_ARGS__)


#define _MAP_LIST(f, arg0, ...) f(arg0) EVAL (MAP1_LIST (f, __VA_ARGS__, MAP_GET_END, (), 0))
#define MAP_LIST(f, ...) _MAP_LIST(f,  __VA_ARGS__)





#define MAP0_LIST_APPLY(f, expr, x, peek, _end, ...) , f(x) (expr) MAP_NEXT (peek, MAP1_LIST_APPLY, _end) (f, expr, peek, _end, __VA_ARGS__)
#define MAP1_LIST_APPLY(f, expr, x, peek, _end, ...) , f(x) (expr) MAP_NEXT (peek, MAP0_LIST_APPLY, _end) (f, expr, peek, _end, __VA_ARGS__)

#define _MAP_LIST_APPLY_ARG(f, expr, arg_0, ...) f(arg_0) (expr) EVAL (MAP1_LIST_APPLY (f, expr, __VA_ARGS__, MAP_GET_END, (), 0))
#define MAP_LIST_APPLY_ARG(f, ...) _MAP_LIST_APPLY_ARG(f, __VA_ARGS__)




#define macro_pack_args(...) (__VA_ARGS__)
#define macro_cons_parens(...) __VA_ARGS__
#define macro_unpack_args(args) macro_cons_parens args


#define macro_comma(arg) ,arg
#define macro_list(arg, rest...) arg MAP(macro_comma, rest)
//      ^^^^^^^^^^ turn arg into a comma seperated list ...


#define macro_repeat_0(...)
#define macro_repeat_1(...) __VA_ARGS__
#define macro_repeat_2(...) macro_repeat_1(__VA_ARGS__) macro_repeat_1(__VA_ARGS__)
#define macro_repeat_4(...) macro_repeat_2(__VA_ARGS__) macro_repeat_2(__VA_ARGS__)
#define macro_repeat_7(...) macro_repeat_4(__VA_ARGS__) macro_repeat_2(__VA_ARGS__) macro_repeat_1(__VA_ARGS__)
#define macro_repeat_8(...) macro_repeat_4(__VA_ARGS__) macro_repeat_4(__VA_ARGS__)
#define macro_repeat_(cnt)  macro_repeat_ ## cnt

#define macro_apply(f, ...) f (__VA_ARGS__)
// apply macro function to already parentheisized list of arguments ...


#define macro_comma_delim_0(arg)
#define macro_comma_delim_1(arg)    arg
#define macro_comma_delim_2(arg)    arg, arg
#define macro_comma_delim_3(arg)    macro_comma_delim_2(arg), macro_comma_delim_1(arg)
#define macro_comma_delim_4(arg)    macro_comma_delim_2(arg), macro_comma_delim_2(arg)
#define macro_comma_delim_5(arg)    macro_comma_delim_4(arg), macro_comma_delim_1(arg)
#define macro_comma_delim_6(arg)    macro_comma_delim_4(arg), macro_comma_delim_2(arg)
#define macro_comma_delim_7(arg)    macro_comma_delim_6(arg), macro_comma_delim_1(arg)
#define macro_comma_delim_8(arg)    macro_comma_delim_4(arg), macro_comma_delim_4(arg)
#define macro_comma_delim_16(arg)   macro_comma_delim_8(arg), macro_comma_delim_8(arg)

#define macro_comma_delim(_imm_literal, arg)  macro_comma_delim_ ## _imm_literal (arg)


#define macro_arg_0(arg_0, args...) arg_0
#define macro_arg_1(arg_0, arg_1, ...) arg_1
#define macro_arg_2(arg_0, arg_1, arg_2, ...) arg_2
#define macro_arg_3(arg_0, arg_1, arg_2, arg_3, ...) arg_3
#define macro_arg_4(arg_0, arg_1, arg_2, arg_3, arg_4, ...) arg_4
#define macro_arg_5(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, ...) arg_5

#define macro_arg(_imm_literal, args...) macro_arg_ ## _imm_literal (args)


#define macro_select_args_2(arg_0, arg_1, ...) arg_0, arg_1
#define macro_select_args_4(arg_0, arg_1, ...) arg_0, arg_1, macro_select_args_2(__VA_ARGS__)
#define macro_select_args_8(arg_0, arg_1, arg_2, arg_3, ...) arg_0, arg_1, arg_2, arg_3, macro_select_args_4(__VA_ARGS__)
#define macro_select_args_16(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, ...)\
    arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, macro_select_args_8(__VA_ARGS__)

#define macro_select_args(cnt, ...) macro_select_args_ ## cnt (__VA_ARGS__)



#define MACRO_NEW_LINE "\n\n"



#endif
