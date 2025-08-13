#ifndef CUTILITIES_ALLOCATOR_H
#define CUTILITIES_ALLOCATOR_H

#include "config.h"
#include <stdlib.h>
#include <stdio.h>

typedef void*(*allocate_fn_t)(size_t);
typedef void*(*reallocate_fn_t)(void*, size_t);
typedef void(*deallocate_fn_t)(void*);

typedef struct
{
    allocate_fn_t   allocate;
    reallocate_fn_t reallocate;
    deallocate_fn_t deallocate;
} allocator_t;

CONSTEXPR_VAR allocator_t heap_allocator = { malloc, realloc, free };

CONSTEXPR allocator_t allocator(allocate_fn_t allocate, reallocate_fn_t reallocate, deallocate_fn_t deallocate) NOEXCEPT
{
    allocator_t res = { allocate, reallocate, deallocate };
    return res;
}

#define CU_OBJ_TYPE allocator_t
#define CU_OBJ_TYPE_NAME allocator
#define CU_CREATE(mem) {   \
    *mem = heap_allocator; \
    return 0;              \
}
#include "object.h"
#undef CU_OBJ_TYPE
#undef CU_OBJ_TYPE_NAME
#undef CU_CREATE


#ifdef __cplusplus
namespace cutils
{
    class Allocator
    {
    public:
        void* allocate(size_t size)
        {
            return malloc(size);
        }    
        void* reallocate(void* mem, size_t size)
        {
            return realloc(mem, size);
        }
        void deallocate(void* mem)
        {
            free(mem);
        }
    };
}
#endif

#endif