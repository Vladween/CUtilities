#ifndef CUTILITIES_OBJECT_POD_H
#define CUTILITIES_OBJECT_POD_H

#include <stdint.h>

#define CU_TYPE char
#include "../object.h"
#undef CU_TYPE

#define CU_TYPE short
#include "../object.h"
#undef CU_TYPE

#define CU_TYPE int
#include "../object.h"
#undef CU_TYPE

#define CU_TYPE long
#include "../object.h"
#undef CU_TYPE

#define CU_TYPE long long
#define CU_TYPE_NAME llong
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME


#define CU_TYPE unsigned char
#define CU_TYPE_NAME uchar
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE unsigned short
#define CU_TYPE_NAME ushort
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE unsigned int
#define CU_TYPE_NAME uint
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE unsigned long
#define CU_TYPE_NAME ulong
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE unsigned long long
#define CU_TYPE_NAME ullong
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME


#define CU_TYPE float
#include "../object.h"
#undef CU_TYPE

#define CU_TYPE double
#include "../object.h"
#undef CU_TYPE



#define CU_TYPE int8_t
#define CU_TYPE_NAME int8
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE int16_t
#define CU_TYPE_NAME int16
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE int32_t
#define CU_TYPE_NAME int32
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE int64_t
#define CU_TYPE_NAME int64
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME


#define CU_TYPE uint8_t
#define CU_TYPE_NAME uint8
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE uint16_t
#define CU_TYPE_NAME uint16
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE uint32_t
#define CU_TYPE_NAME uint32
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE uint64_t
#define CU_TYPE_NAME uint64
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#define CU_TYPE size_t
#define CU_TYPE_NAME size
#include "../object.h"
#undef CU_TYPE
#undef CU_TYPE_NAME

#endif