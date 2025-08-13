#ifndef CUTILITIES_CONFIG_UTILITIES_H
#define CUTILITIES_CONFIG_UTILITIES_H

#define _CU_TO_STR(x) #x
#define CU_TO_STR(x) _CU_TO_STR(x)

#ifdef __cplusplus
#   define CU_C(x)
#   define CU_CPP(x) x
#   define CU_C_CPP(C, CPP) CPP
#else
#   define CU_C(x) x
#   define CU_CPP(x)
#   define CU_C_CPP(C, CPP) C
#endif

#define _CU_EVAL1(...) __VA_ARGS__
#define _CU_EVAL2(...) _CU_EVAL1(_CU_EVAL1(_CU_EVAL1(_CU_EVAL1(__VA_ARGS__))))
#define _CU_EVAL3(...) _CU_EVAL2(_CU_EVAL2(_CU_EVAL2(_CU_EVAL2(__VA_ARGS__))))
#define _CU_EVAL4(...) _CU_EVAL3(_CU_EVAL3(_CU_EVAL3(_CU_EVAL3(__VA_ARGS__))))
#define _CU_EVAL5(...) _CU_EVAL4(_CU_EVAL4(_CU_EVAL4(_CU_EVAL4(__VA_ARGS__))))
#define _CU_EMPTY()
#define _CU_TUPLE_AT_1(a,b,...) b
#define _CU_CHECK(...) _CU_TUPLE_AT_1(__VA_ARGS__)
#define _CU_CONCAT_PROBE(...) ,_CU_CONCAT_END,
#define _CU_CONCAT_IND() _CU_CONCAT_
#define _CU_CONCAT_(x,a,...) _CU_CHECK(_CU_CONCAT_PROBE a,_CU_CONCAT_NEXT)(x,a,__VA_ARGS__)
#define _CU_CONCAT_NEXT(x,a,...) _CU_CONCAT_IND _CU_EMPTY()()(x##a,__VA_ARGS__)
#define _CU_CONCAT_END(x,a,...) x

#define CU_CONCAT(...) _CU_EVAL5(_CU_CONCAT_(,__VA_ARGS__,()))
#define CU_C_CONCAT(first, ...) CU_C_CPP(CU_CONCAT(first, __VA_ARGS__), first)
#define CU_CPP_CONCAT(first, ...) CU_C_CPP(first, CU_CONCAT(first, __VA_ARGS__))

#endif