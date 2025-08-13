#ifndef CUTILITIES_CONFIG_DLL_H
#define CUTILITIES_CONFIG_DLL_H

#ifdef _WIN32
#   define CU_EXPORT __declspec(dllexport)
#   define CU_IMPORT __declspec(dllimport)
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__unix__)
#   define CU_EXPORT __attribute__((__visibility__("default")))
#   define CU_IMPORT __attribute__((__visibility__("default")))
#else
#   define CU_EXPORT
#   define CU_IMPORT
#endif

#endif