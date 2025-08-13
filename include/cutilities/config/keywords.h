#ifndef CUTILITIES_CONFIG_KEYWORDS_H
#define CUTILITIES_CONFIG_KEYWORDS_H

#include "compiler.h"

/// C++ keywords
#ifdef __cplusplus
#   define TEMPLATE(...) template<__VA_ARGS__>
#else
#   define TEMPLATE(...)
#endif

/// C++11 or higher keywords
#if defined(__cplusplus) && __cplusplus >= CLIB_CPP11
#   define NOEXCEPT noexcept
#   define FINAL final
#   define CONSTEXPR constexpr
#   define EXPLICIT explicit
#   define THREAD_LOCAL thread_local
#else
#   define NOEXCEPT
#   define FINAL
#   define CONSTEXPR
#   define EXPLICIT
#   define THREAD_LOCAL
#endif

/// C99 or higher or C++ keywords 
#if (!defined(__cplusplus) && __STDC_VERSION__ >= C99) || defined(__cplusplus)
#   define INLINE inline
#else
#   define INLINE
#endif

/// C++17 or higher keywords
#if defined(__cplusplus) && __cplusplus >= CLIB_CPP17
#   define NODISCARD [[nodiscard]]
#   define NORETURN [[noreturn]]
#   define FALLTHROUGH [[fallthrough]]
#   define DEPRECATED [[deprecated]]
#   define MAYBE_UNUSED [[maybe_unused]]
#   define IF_CONSTEXPR if constexpr
#   define CONSTEXPR_VAR constexpr
#else
#   define NODISCARD
#   define NORETURN
#   define FALLTHROUGH
#   define DEPRECATED
#   define MAYBE_UNUSED
#   define IF_CONSTEXPR if
#   define CONSTEXPR_VAR const
#endif

#endif