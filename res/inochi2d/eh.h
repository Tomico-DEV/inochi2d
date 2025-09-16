#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "inochi2d.h"

#ifndef H_INOCHI2D_EH
#define H_INOCHI2D_EH

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

//
//              ERROR HANDLING
//

/**
    Gets the last error.

    Returns:
        A string with the last error that occured,
        or $(D null).
*/
EXPORT_I2D const char* in_get_last_error();

//
//              DRT INIT
//

/// CRT CTOR
EXPORT_I2D void in_crt_init();
/// CRT DTOR
EXPORT_I2D void in_crt_term();

#ifdef __cplusplus
}
#endif


#endif
