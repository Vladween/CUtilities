#ifndef CU_ARR_TYPE
#   ifdef CU_TYPE
#       define CU_ARR_TYPE CU_TYPE
#       define _CU_USED_DEFAULT_ARR_TYPE
#   elif !defined(__cplusplus)
#       error 'CU_ARR_TYPE' or 'CU_TYPE' must be defined!
#   endif
#endif
#if !defined(CU_ARR_TYPE_NAME)
#   define CU_ARR_TYPE_NAME CU_ARR_TYPE
#   define _CU_USED_DEFAULT_ARR_TYPE_NAME
#endif

#ifndef CUTILITIES_ARRAY_RAW_H
#ifndef __cplusplus
#   define CUTILITIES_ARRAY_RAW_H
#endif

#include <stdint.h>
#include "cutilities/allocator.h"
#include "cutilities/error.h"

#define CU_DECL_RAW_ARRAY_C_FUNC(name, c_suffix)   CU_CONCAT(raw_, CU_ARR_TYPE_NAME, _array_, name, c_suffix)
#define CU_DECL_RAW_ARRAY_CPP_FUNC(name, c_suffix) name
#define CU_CALL_RAW_ARRAY_C_FUNC(name, type_name, c_suffix) CU_CONCAT(raw_, type_name, _array_, name, c_suffix)
#define CU_CALL_RAW_ARRAY_CPP_FUNC(name, type, c_suffix)    cu::array::name<type> 

#endif

#if (defined(__cplusplus) && !defined(CUTILITIES_ARRAY_RAW_H)) || !defined(__cplusplus)

#ifndef __cplusplus
#   define T CU_ARR_TYPE
#else
#   define CUTILITIES_ARRAY_RAW_H
namespace cu
{
    namespace array
    {
#endif
        /// deallocate
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, deallocate, _with_fn)(T* arr, size_t size, deallocate_fn_t dealloc) NOEXCEPT
        {
            if(!dealloc) return CU_INVALID_ARGS;
            if(!arr || !size) return CU_OK;

            for(size_t i=size; i>0; i--)
                CU_CALL_FUNC(OBJECT, destroy, CU_ARR_TYPE_NAME, T)(&arr[i - 1]);
            dealloc(arr);
            return CU_OK;
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, deallocate, _with_allocator)(T* arr, size_t size, const allocator_t* alctor) NOEXCEPT
        {
            if(!alctor) return CU_INVALID_ARGS;
            return CU_CALL_FUNC(RAW_ARRAY, deallocate, CU_ARR_TYPE_NAME, T, _with_fn)(arr, size, alctor->deallocate);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, deallocate)(T* arr, size_t size) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, deallocate, CU_ARR_TYPE_NAME, T, _with_fn)(arr, size, free);
        }

        /// allocate
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead_with_fn)(T** arr, size_t size, size_t capacity, allocate_fn_t alloc, deallocate_fn_t dealloc) NOEXCEPT
        {
            *cu_last_error_ptr() = 0;

            if(!arr || !alloc || !dealloc)
                return CU_INVALID_ARGS;

            if(capacity < size)
                capacity = size;
            if(!capacity)
                return CU_OK;

            *arr = (T*)alloc(capacity);
            if(!(*arr))
                return CU_ALLOC_FAILED;

            int err;
            for(size_t i=0; i<size; i++)                
            {
                if(err = CU_CALL_FUNC(OBJECT, create, CU_ARR_TYPE_NAME, T)(&(*arr)[i]))
                {
                    CU_CALL_FUNC(RAW_ARRAY, deallocate, CU_ARR_TYPE_NAME, T, _with_fn)(*arr, i, dealloc);
                    if(err != CU_THREW_EXCEPTION)
                    {
                        *cu_last_error_ptr() = err;
                        return CU_SEMANTIC_FAILED; 
                    }
                    return CU_THREW_EXCEPTION;
                }
            }

            return CU_OK;
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead_with_allocator)(T** arr, size_t size, size_t capacity, const allocator_t* alctor) NOEXCEPT
        {
            if(!alctor) return CU_INVALID_ARGS;
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_with_fn)(arr, size, capacity, alctor->allocate, alctor->deallocate);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead)(T** arr, size_t size, size_t capacity) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_with_fn)(arr, size, capacity, malloc, free);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _with_fn)(T** arr, size_t size, allocate_fn_t alloc, deallocate_fn_t dealloc) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_with_fn)(arr, size, size, alloc, dealloc);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _with_allocator)(T** arr, size_t size, const allocator_t* alctor) NOEXCEPT
        {
            if(!alctor) return CU_INVALID_ARGS;
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _with_fn)(arr, size, alctor->allocate, alctor->deallocate);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate)(T** arr, size_t size) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _with_fn)(arr, size, malloc, free);
        }

        /// allocate_copy
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead_copy_with_fn)(T** arr, const T* cpy, size_t size, size_t capacity, allocate_fn_t alloc, deallocate_fn_t dealloc) NOEXCEPT
        {
            *cu_last_error_ptr() = 0;

            if(!arr || !alloc || !dealloc || (!cpy && size))
                return CU_INVALID_ARGS;

            if(capacity < size)
                capacity = size;
            if(!capacity)
                return CU_OK;

            *arr = (T*)alloc(capacity);
            if(!(*arr))
                return CU_ALLOC_FAILED;

            int err;
            for(size_t i=0; i<size; i++)
            {
                if(err = CU_CALL_FUNC(OBJECT, create, CU_ARR_TYPE_NAME, T, _copy)(&(*arr)[i], cpy[i]))
                {
                    CU_CALL_FUNC(RAW_ARRAY, deallocate, CU_ARR_TYPE_NAME, T, _with_fn)(*arr, i, dealloc);
                    if(err != CU_THREW_EXCEPTION)
                    {
                        *cu_last_error_ptr() = err;
                        return CU_SEMANTIC_FAILED;
                    }
                    return CU_THREW_EXCEPTION;
                }
            }

            return CU_OK;
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead_copy_with_allocator)(T** arr, const T* cpy, size_t size, size_t capacity, const allocator_t* alctor) NOEXCEPT
        {
            if(!alctor) return CU_INVALID_ARGS;
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_copy_with_fn)(arr, cpy, size, capacity, alctor->allocate, alctor->deallocate);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _overhead_copy)(T** arr, const T* cpy, size_t size, size_t capacity) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_copy_with_fn)(arr, cpy, size, capacity, malloc, free);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _copy_with_fn)(T** arr, const T* cpy, size_t size, allocate_fn_t alloc, deallocate_fn_t dealloc) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _overhead_copy_with_fn)(arr, cpy, size, size, alloc, dealloc);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _copy_with_allocator)(T** arr, const T* cpy, size_t size, const allocator_t* alctor) NOEXCEPT
        {
            if(!alctor) return CU_INVALID_ARGS;
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _copy_with_fn)(arr, cpy, size, alctor->allocate, alctor->deallocate);
        }
        TEMPLATE(typename T) cu_err_t CU_DECL_FUNC(RAW_ARRAY, allocate, _copy)(T** arr, const T* cpy, size_t size) NOEXCEPT
        {
            return CU_CALL_FUNC(RAW_ARRAY, allocate, CU_ARR_TYPE_NAME, T, _copy_with_fn)(arr, cpy, size, malloc, free);
        }
#ifdef __cplusplus
    }
}
#endif

#endif

#ifdef _CU_USED_DEFAULT_ARR_TYPE
#   undef CU_ARR_TYPE
#   undef _CU_USED_DEFAULT_ARR_TYPE
#endif
#ifdef _CU_USED_DEFAULT_ARR_TYPE_NAME
#   undef CU_ARR_TYPE_NAME
#   undef _CU_USED_DEFAULT_ARR_TYPE_NAME
#endif