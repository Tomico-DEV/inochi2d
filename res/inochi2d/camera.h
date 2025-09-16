#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "inochi2d/inochi2d.h"

#ifndef H_INOCHI2D_CAMERA
#define H_INOCHI2D_CAMERA

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
//              CAMERA
//

/**
    Opaque handle to camera.
*/
struct in_camera_t;

/**
    Gets the current camera.

    Returns:
        The current camera.
*/
EXPORT_I2D in_camera_t* in_camera_get_current();

/**
    Sets the camera's position

    Params:
        cam = The camra object.
        pos = The position to set to.
*/
EXPORT_I2D void in_camera_set_position(in_camera_t* cam, in_vec2_t pos);

/**
    Gets the camera's position.

    Params:
        cam = The camera object.
    Returns:
        The camera's position.
*/
EXPORT_I2D in_vec2_t in_camera_get_position(in_camera_t* cam);

/**
    Sets the camera's rotation.

    Params:
        cam = The camera object.
        rot = Rotation value (radians) to set to.
*/
EXPORT_I2D void in_camera_set_rotation(in_camera_t* cam, float rot);

/**
    Gets the camera's rotation.

    Params:
        cam = The camera object.

    Returns:
        The camera's rotation.
*/
EXPORT_I2D float in_camera_get_rotation(in_camera_t* cam);

/**
    Sets the camera's scale.

    Params:
        cam = The camera object.
        scale = The zoom value to set to.
*/
EXPORT_I2D void in_camera_set_scale(in_camera_t* cam, float scale);

/**
    Gets the camera's scale.

    Params:
        cam = The camera object.

    Returns:
        The camera's scale.
*/
EXPORT_I2D void in_camera_get_scale(in_camera_t* cam);

/**
    Gets the camera's center offset.

    Params:
        cam = The camera object.

    Returns:
        The camera's center offset.
*/
EXPORT_I2D in_vec2_t in_camera_get_center_offset(in_camera_t* cam);
/**
    Copies the values of the internal camera matrix out to mat4

    Params:
        cam = The camera object.
        mat4 = The matrix to populate values with. Must have len 16
*/
EXPORT_I2D void in_camera_get_matrix(in_camera_t* cam, const float* mat4);
/**
    Destroys the camera.

    Params:
        cam = The camera to destroy.
*/
EXPORT_I2D void in_camera_destroy(in_camera_t* cam);

#ifdef __cplusplus
}
#endif


#endif
