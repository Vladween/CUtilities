#ifndef CUTILITIES_CONFIG_COMPILER_H
#define CUTILITIES_CONFIG_COMPILER_H

/// C standards
#define CU_C99 199901L
#define CU_C11 201112L
#define CU_C17 201710L

/// C++ standards
#define CU_CPP98 199711L
#define CU_CPP03 200303L
#define CU_CPP11 201103L
#define CU_CPP14 201402L
#define CU_CPP17 201703L
#define CU_CPP20 202002L
#define CU_CPP23 202302L

/// Current compiler
#if defined(_MSC_VER)
#   define CU_COMPILER_MSVC
#elif defined(__MINGW32__)
#   define CU_COMPILER_MINGW
#elif defined(__GNUC__)
#   define CU_COMPILER_GNU
#elif defined(__clang__)
#   define CU_COMPILER_CLANG
#elif defined(__ARDUINO__)
#   define CU_COMPILER_ARDUINO
#elif defined(IDF_VER)
#   define CU_COMPILER_ESPIDF
#elif defined(__AVR__)
#   define CU_COMPILER_AVR
#else
#   error Current C/C++ compiler is not supported!
#endif

#endif