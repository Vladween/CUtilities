#ifndef CUTILITIES_CONFIG_OS_H
#define CUTILITIES_CONFIG_OS_H

#include "compiler.h"

#if defined(_WIN32) || defined(_WIN64)
#   define CU_OS_WINDOWS
#elif defined(__ANDROID__)
#   define CU_OS_ANDROID
#elif defined(__APPLE__)
#   include <TargetConditionals.h>
#   if TARGET_OS_IPHONE
#       define CU_OS_IOS
#   elif TARGET_OS_MAC
#       define CU_OS_MACOS
#   else
#       error Current Apple OS is not supported!
#   endif
#elif defined(__linux__)
#   define CU_OS_LINUX
#else
#   define CU_OS_BAREMETAL
#endif

#endif