#ifndef CU_OBJ_TYPE
#   ifdef CU_TYPE
#       define CU_OBJ_TYPE CU_TYPE
#       define _CU_USED_DEFAULT_OBJ_TYPE
#   elif !defined(__cplusplus)
#       error 'CU_OBJ_TYPE' or 'CU_TYPE' must be defined!
#   endif
#endif
#ifndef CU_OBJ_TYPE_NAME
#   ifdef CU_TYPE_NAME
#       define CU_OBJ_TYPE_NAME CU_TYPE_NAME
#   else
#       define CU_OBJ_TYPE_NAME CU_OBJ_TYPE
#   endif
#   define _CU_USED_DEFAULT_OBJ_TYPE_NAME
#endif

#ifndef CUTILITIES_OBJECT_H
#define CUTILITIES_OBJECT_H

#include "config.h"
#include "error.h"

#define CU_DECL_OBJECT_C_FUNC(name, c_suffix) CU_CONCAT(object_, name, _, CU_OBJ_TYPE_NAME, c_suffix)
#define CU_DECL_OBJECT_CPP_FUNC(name, c_suffix) name
#define CU_CALL_OBJECT_C_FUNC(name, type_name, c_suffix) CU_CONCAT(object_, name, _, type_name, c_suffix)
#define CU_CALL_OBJECT_CPP_FUNC(name, type, c_suffix) cu::object::name<type>

#ifdef __cplusplus
#   include <new>
#   if CU_ENV_EXCEPTIONS_ENABLED == 1
#       define _CU_PRIV_PREFIX(function) CU_CONCAT(__, function)
#       define _CU_PRIV_NAMESPACE priv
#       if __cplusplus >= CU_CPP11 && CU_ENV_STL_ENABLED == 1
#           include <type_traits>
#       endif
#   else
#       define _CU_PRIV_PREFIX(function) function
#       define _CU_PRIV_NAMESPACE object
#   endif

namespace cu
{
    namespace _CU_PRIV_NAMESPACE
    {
        template<typename T>
        int _CU_PRIV_PREFIX(create)(T* mem)
        {
            new(mem)T();
            return 0;
        }

        template<typename T>
        int _CU_PRIV_PREFIX(create)(T* mem, const T& cpy)
        {
            new(mem)T(cpy);
            return 0;
        }

        template<typename T>
        int _CU_PRIV_PREFIX(create)(T* mem, T* mov)
        {
#   if __cplusplus >= CU_CPP11
            new(mem)T(static_cast<T&&>(*mov));
#   else
            new(mem)T(*mov);
#   endif
            return 0;
        }

        template<typename T>
        int _CU_PRIV_PREFIX(assign)(T* mem, const T& cpy)
        {
            *mem = cpy;
            return 0;
        } 

        template<typename T>
        int _CU_PRIV_PREFIX(assign)(T* mem, T* mov)
        {
#   if __cplusplus >= CU_CPP11
            *mem = static_cast<T&&>(*mov);
#   else
            *mem = *mov;
#   endif
            return 0;
        }

#   if __cplusplus >= CU_CPP11
        template<typename T>
        int _CU_PRIV_PREFIX(create)(T* mem, T&& mov)
        {
            new(mem)T(static_cast<T&&>(mov));
            return 0;
        }
        template<typename T>
        int _CU_PRIV_PREFIX(assign)(T* mem, T&& mov)
        {
            *mem = static_cast<T&&>(mov);
            return 0;
        }
#   endif
    }

    namespace object
    {
        template<typename T>
        CONSTEXPR bool create_move_may_fail() NOEXCEPT
        { 
#   if __cplusplus >= CU_CPP11 && CU_ENV_STL_ENABLED == 1
            return !std::is_nothrow_move_constructible<T>::value;
#   else
            return false;
#   endif
        }
        template<typename T>
        CONSTEXPR bool move_may_fail() NOEXCEPT
        {
#   if __cplusplus >= CU_CPP11 && CU_ENV_STL_ENABLED == 1
            return !std::is_nothrow_move_assignable<T>::value;
#   else
            return false;
#   endif
        }

        template<typename T>
        void destroy(T* mem) NOEXCEPT
        {
            (*mem).~T();
        }

#   if CU_ENV_EXCEPTIONS_ENABLED == 1

        template<typename T>
        int create(T* mem) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__create(mem);
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }
        }

        template<typename T>
        int create(T* mem, const T& cpy) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__create(mem, cpy);
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }
        }

        template<typename T>
        int create(T* mem, T* mov) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__create(mem, mov);
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }
        }

        template<typename T>
        int assign(T* mem, const T& cpy) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__assign(mem, cpy);
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }
        }

        template<typename T>
        int assign(T* mem, T* mov) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__assign(mem, mov);
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }
        }

#       if __cplusplus >= CU_CPP11
        template<typename T>
        int create(T* mem, T&& mov) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__create(mem, static_cast<T&&>(mov));
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }   
        }

        template<typename T>
        int assign(T* mem, T&& mov) NOEXCEPT
        {
            _CU_CLEAN_LAST_EXCEPTION
            try
            {
                return priv::__assign(mem, static_cast<T&&>(mov));
            }
            catch(...)
            {
                _CU_UPDATE_LAST_EXCEPTION
                return CU_THREW_EXCEPTION;
            }   
        }
#       endif

#       undef _CU_CLEAN_LAST_EXCEPTION
#       undef _CU_UPDATE_LAST_EXCEPTION
#   endif
    }
}
#   endif
#endif

#ifdef __cplusplus
#   ifdef CU_OBJ_TYPE

namespace cu::CU_PRIV_NAMESPACE
{
#       ifdef CU_CREATE
    template<>
    int _CU_PRIV_PREFIX(create)(CU_OBJ_TYPE* mem)
        CU_CREATE(mem)
#       endif
#       ifdef CU_CREATE_COPY
    template<>
    int _CU_PRIV_PREFIX(create)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy)
        CU_CREATE_COPY(mem, cpy)
#           ifndef CU_COPY
    template<>
    int _CU_PRIV_PREFIX(assign)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy)
        CU_CREATE_COPY(mem, cpy)
#           endif
#       endif
#       ifdef CU_CREATE_MOVE
    template<>
    int _CU_PRIV_PREFIX(create)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov)
        CU_CREATE_MOVE(mem, mov)
#           if __cplusplus >= CPP11
    template<>
    int _CU_PRIV_PREFIX(create)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE&& mov)
        CU_CREATE_MOVE(mem, (&mov));
#           endif
#       endif
#       ifdef CU_COPY
#           ifndef CU_CREATE_COPY
    template<>
    int _CU_PRIV_PREFIX(create)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy)
        CU_COPY(mem, cpy)
#           endif
    template<>
    int _CU_PRIV_PREFIX(assign)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy)
        CU_COPY(mem, cpy)
#       endif
#       ifdef CU_MOVE
    template<>
    int CU_PRIV_PREFIX(assign)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov)
        CU_MOVE(mem, mov)
#           if __cplusplus >= CPP11
    template<>
    int CU_PRIV_PREFIX(assign)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE&& mov)
        CU_MOVE(mem, (&mov))
#           endif
#       endif
}

#       ifdef CU_DESTROY
namespace cu::object
{
    template<>
    void destroy(CU_OBJ_TYPE* mem) NOEXCEPT
        CU_DESTROY(mem)
}
#       endif

CU_DEF_FUNC_ALIAS(int,  OBJECT, create,  CU_OBJ_TYPE, (CU_OBJ_TYPE* mem), (mem))
CU_DEF_FUNC_ALIAS(void, OBJECT, destroy, CU_OBJ_TYPE, (CU_OBJ_TYPE* mem), (mem))
CU_DEF_FUNC_ALIAS(int, OBJECT, create, CU_OBJ_TYPE, (CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy), (mem, cpy), _copy)
CU_DEF_FUNC_ALIAS(int, OBJECT, create, CU_OBJ_TYPE, (CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov),       (mem, mov), _move)
CU_DEF_SIMPLE_FUNC_ALIAS(int, CU_CONCAT(object_create_, CU_OBJ_TYPE, _move_may_fail)(), cu::object::create_move_may_fail<CU_OBJ_TYPE>())
CU_DEF_SIMPLE_FUNC_ALIAS(int, CU_CONCAT(object_move_,   CU_OBJ_TYPE, _may_fail)(),      cu::object::move_may_fail<CU_OBJ_TYPE>()       )
CU_DEF_SIMPLE_FUNC_ALIAS(int, CU_CONCAT(object_copy_, CU_OBJ_TYPE)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE& cpy), cu::object::assign<CU_OBJ_TYPE>(mem, cpy))
CU_DEF_SIMPLE_FUNC_ALIAS(int, CU_CONCAT(object_move_, CU_OBJ_TYPE)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov),       cu::object::assign<CU_OBJ_TYPE>(mem, mov))

#   endif
#else
#   ifndef CU_CREATE
#       define CU_CREATE(mem) { return 0; }
#       define _CU_USED_DEFAULT_CREATE
#   endif
#   if defined(CU_CREATE_COPY) != defined(CU_COPY)
#       ifdef CU_CREATE_COPY
#           define CU_COPY(mem, cpy) CU_CREATE_COPY(mem, cpy)
#           define _CU_USED_DEFAULT_COPY
#       else
#           define CU_CREATE_COPY(mem, cpy) CU_COPY(mem, cpy)
#           define _CU_USED_DEFAULT_CREATE_COPY
#       endif
#   elif !defined(CU_CREATE_COPY) && !defined(CU_COPY)
#       define CU_CREATE_COPY(mem, cpy) { *mem = cpy; return 0; }
#       define _CU_USED_DEFAULT_CREATE_COPY
#       define CU_COPY(mem, cpy) CU_CREATE_COPY(mem, cpy)
#       define _CU_USED_DEFAULT_COPY
#   endif
#   if defined(CU_CREATE_MOVE) != defined(CU_MOVE)
#       ifdef CU_CREATE_MOVE
#           define CU_MOVE(mem, mov) CU_CREATE_MOVE(mem, mov)
#           define _CU_USED_DEFAULT_MOVE
#           ifdef CU_CREATE_MOVE_MAY_FAIL
#               define CU_MOVE_MAY_FAIL
#               define _CU_USED_DEFAULT_MOVE_MAY_FAIL
#           endif
#       else
#           define CU_CREATE_MOVE(mem, mov) CU_MOVE(mem, mov)
#           define _CU_USED_DEFAULT_CREATE_MOVE
#           ifdef CU_MOVE_MAY_FAIL
#               define CU_CREATE_MOVE_MAY_FAIL
#               define _CU_USED_DEFAULT_CREATE_MOVE_MAY_FAIL
#           endif
#       endif
#   elif !defined(CU_CREATE_MOVE) && !defined(CU_MOVE)
#       define CU_CREATE_MOVE(mem, mov) CU_CREATE_COPY(mem, (*mov))
#       define CU_MOVE(mem, mov) CU_COPY(mem, (*mov))
#       define _CU_USED_DEFAULT_CREATE_MOVE
#       define _CU_USED_DEFAULT_MOVE
#   endif
#   ifndef CU_DESTROY
#       define CU_DESTROY(mem) { }
#       define _CU_USED_DEFAULT_DESTROY
#   endif

int CU_DECL_OBJECT_C_FUNC(create,)(CU_OBJ_TYPE* mem)
    CU_CREATE(mem)
int CU_DECL_OBJECT_C_FUNC(create, _copy)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE cpy)
    CU_CREATE_COPY(mem, cpy)
int CU_DECL_OBJECT_C_FUNC(create, _move)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov)
    CU_CREATE_MOVE(mem, mov)
int CU_DECL_OBJECT_C_FUNC(copy,)(CU_OBJ_TYPE* mem, const CU_OBJ_TYPE cpy)
    CU_COPY(mem, cpy)
int CU_DECL_OBJECT_C_FUNC(move,)(CU_OBJ_TYPE* mem, CU_OBJ_TYPE* mov)
    CU_MOVE(mem, mov)
void CU_DECL_OBJECT_C_FUNC(destroy,)(CU_OBJ_TYPE* mem)
    CU_DESTROY(mem)

int CU_DECL_OBJECT_C_FUNC(create, _move_may_fail)()
{
#   ifdef CU_CREATE_MOVE_MAY_FAIL
    return 1;
#   else
    return 0;
#   endif
}
int CU_DECL_OBJECT_C_FUNC(move, _may_fail)()
{
#   ifdef CU_MOVE_MAY_FAIL
    return 1;
#   else
    return 0;
#   endif
}

#   ifdef _CU_USED_DEFAULT_CREATE
#       undef CU_CREATE
#       undef _CU_USED_DEFAULT_CREATE
#   endif
#   ifdef _CU_USED_DEFAULT_CREATE_COPY
#       undef CU_CREATE_COPY
#       undef _CU_USED_DEFAULT_CREATE_COPY
#   endif
#   ifdef _CU_USED_DEFAULT_COPY
#       undef CU_COPY
#       undef _CU_USED_DEFAULT_COPY
#   endif
#   ifdef _CU_USED_DEFAULT_CREATE_MOVE
#       undef CU_CREATE_MOVE
#       undef _CU_USED_DEFAULT_CREATE_MOVE
#   endif
#   ifdef _CU_USED_DEFAULT_MOVE
#       undef CU_MOVE
#       undef _CU_USED_DEFAULT_MOVE
#   endif
#   ifdef _CU_USED_DEFAULT_CREATE_MOVE_MAY_FAIL
#       undef CU_CREATE_MOVE_MAY_FAIL
#       undef _CU_USED_DEFAULT_CREATE_MOVE_MAY_FAIL
#   endif
#   ifdef _CU_USED_DEFAULT_MOVE_MAY_FAIL
#       undef CU_MOVE_MAY_FAIL
#       undef _CU_USED_DEFAULT_MOVE_MAY_FAIL
#   endif
#   ifdef _CU_USED_DEFAULT_DESTROY
#       undef CU_DESTROY
#       undef _CU_USED_DEFAULT_DESTROY
#   endif
#endif

#ifdef _CU_USED_DEFAULT_OBJ_TYPE
#   undef CU_OBJ_TYPE
#   undef _CU_USED_DEFAULT_OBJ_TYPE
#endif
#ifdef _CU_USED_DEFAULT_OBJ_TYPE_NAME
#   undef CU_OBJ_TYPE_NAME
#   undef _CU_USED_DEFAULT_OBJ_TYPE_NAME
#endif