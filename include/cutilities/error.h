#ifndef CUTILITIES_ERROR_H
#define CUTILITIES_ERROR_H

#include "config/environment.h"
#include "config/compiler.h"
#include "config/keywords.h"

typedef enum cu_err_t {
    CU_OK,
    CU_INVALID_ARGS,
    CU_ALLOC_FAILED,
    CU_SEMANTIC_FAILED,
    CU_THREW_EXCEPTION = 0xECC
} cu_err_t;

#ifdef __cplusplus
namespace cu
{
    using err_t = cu_err_t;
}
#endif

int* cu_last_error_ptr() NOEXCEPT
{
    static THREAD_LOCAL int err = 0;
    return &err;
}
int cu_last_error() NOEXCEPT
{
    return *cu_last_error_ptr();
}

#ifdef __cplusplus
namespace cu
{
    inline int* last_error_ptr() NOEXCEPT
    {
        return cu_last_error_ptr();
    }
    inline int last_error() NOEXCEPT
    {
        return cu_last_error();
    }

#if __cplusplus >= CU_CPP11 && CU_ENV_STL_ENABLED == 1 && CU_ENV_EXCEPTIONS_ENABLED == 1
#   include <exception>
#   define _CU_CLEAN_LAST_EXCEPTION last_exception() = nullptr;
#   define _CU_UPDATE_LAST_EXCEPTION last_exception() = std::current_exception();
    inline std::exception_ptr& last_exception() noexcept
    {
        static thread_local std::exception_ptr ex;
        return ex;
    }
#else
#   define _CU_CLEAN_LAST_EXCEPTION
#   define _CU_UPDATE_LAST_EXCEPTION
#endif

}
#endif

#endif