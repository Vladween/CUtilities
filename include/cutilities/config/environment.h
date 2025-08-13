#ifndef CUTILITIES_CONFIG_ENVIRONMENT_H
#define CUTILITIES_CONFIG_ENVIRONMENT_H

#include "compiler.h"
#include "os.h"

#if defined(__cplusplus)         \
    && !defined(CLIB_ENV_NO_STL) \
    && !defined(CLIB_OS_BAREMETAL) 
#   define CU_ENV_STL_ENABLED 1
#else
#   define CU_ENV_STL_ENABLED 0
#endif

#if defined(__cplusplus)                     \
    && !defined(CU_ENV_NO_EXCEPTIONS)      \
    && !defined(CU_OS_BAREMETAL)           \
    && ((                                    \
            !defined(CU_COMPILER_CLANG)    \
            && (                             \
                defined(__cpp_exceptions)    \
                || defined(__EXCEPTIONS)     \
                || defined(_CPPUNWIND)       \
            )                                \
        )                                    \
        || (                                 \
            defined(CU_COMPILER_CLANG)     \
            && __has_feature(cxx_exceptions) \
        )                                    \
    )
#   define CU_ENV_EXCEPTIONS_ENABLED 1
#else
#   define CU_ENV_EXCEPTIONS_ENABLED 0
#endif

#ifndef CU_ENV_WARNING_LEVEL
#   define CU_ENV_WARNING_LEVEL 1
#endif

#endif