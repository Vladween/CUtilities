#ifndef CUTILITIES_FUNCDEF_H
#define CUTILITIES_FUNCDEF_H

#include "utilities.h"
#include "keywords.h"

#define CU_DECL_C_FUNC(module, name, ...) CU_CONCAT(CU_DECL_, module, _C_FUNC)(name, __VA_ARGS__)
#define CU_DECL_CPP_FUNC(module, name, ...) CU_CONCAT(CU_DECL_, module, _CPP_FUNC)(name, __VA_ARGS__)
#define CU_CALL_C_FUNC(module, name, type_name, ...) CU_CONCAT(CU_CALL_, module, _C_FUNC)(name, type_name, __VA_ARGS__)
#define CU_CALL_CPP_FUNC(module, name, type, ...) CU_CONCAT(CU_CALL_, module, _CPP_FUNC)(name, type, __VA_ARGS__)

#define CU_DECL_FUNC(module, name, ...) CU_C_CPP(CU_DECL_C_FUNC(module, name, __VA_ARGS__), CU_DECL_CPP_FUNC(module, name, __VA_ARGS__))
#define CU_CALL_FUNC(module, name, type_name, type, ...) CU_C_CPP(CU_CALL_C_FUNC(module, name, type_name, __VA_ARGS__), CU_CALL_CPP_FUNC(module, name, type, __VA_ARGS__))
#define CU_DEF_SIMPLE_FUNC_ALIAS(return_t, alias, func) inline return_t alias NOEXCEPT { return (return_t)func; } 
#define CU_DEF_FUNC_ALIAS(return_t, module, name, type, args, parsed_args, ...) inline return_t CU_DECL_C_FUNC(module, name, __VA_ARGS__) args NOEXCEPT { return (return_t)CU_CALL_CPP_FUNC(module, name, type, __VA_ARGS__)parsed_args; } 

#endif