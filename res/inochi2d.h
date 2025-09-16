#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef H_INOCHI2D
#define H_INOCHI2D

// Handle calling convention on Windows.
// This will ensure MSVC does not try to use stdcall
// when the D library uses cdecl.
#ifdef _WIN32
    #ifdef _MSC_VER
        #define EXPORT_I2D __cdecl
    #else
        #define EXPORT_I2D
    #endif
#else
    #define EXPORT_I2D
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
    2D Vector
*/
struct in_vec2_t {
    float x;
    float y;
};

/**
    Retains a reference to a Inochi2D Object.

    Params:
        obj = The object to retain.
    
    Returns:
        The object.
*/
EXPORT_I2D void* in_retain(void* obj);

/**
    Releases a reference to a Inochi2D Object.

    Params:
        obj = The object to release.
    
    Returns:
        The object.
*/
EXPORT_I2D void* in_release(void* obj);

#ifdef __cplusplus
}
#endif
