module inochi2d.cffi.camera;
import inochi2d.core.math;
import inochi2d.cffi;
import numem;
import inmath;

version(IN_DYNLIB):
extern(C) export:

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
in_camera_t* in_camera_get_current() {
    import core.memory : GC;

    auto cam = new Camera2D();
    GC.addRoot(cast(void*)cam);
    return cast(in_camera_t*)cam;
}

/**
    Updates the camera.

    Params:
        cam = The camera object.
*/
@nogc
void in_camera_update(in_camera_t* cam) {
    (cast(Camera2D)cam).update();
}

/**
    Sets the camera's position

    Params:
        cam = The camera object.
        pos = The position to set to.
*/
@nogc
void in_camera_set_position(in_camera_t* cam, in_vec2_t pos) {
    (cast(Camera2D)cam).position = reinterpret_cast!vec2(pos);
}

/**
    Gets the camera's position.

    Params:
        cam = The camera object.
    Returns:
        The camera's position.
*/
@nogc
in_vec2_t in_camera_get_position(in_camera_t* cam) {
    return reinterpret_cast!in_vec2_t((cast(Camera2D)cam).position);
}

/**
    Sets the camera's rotation.

    Params:
        cam = The camera object.
        rot = Rotation value (radians) to set to.
*/
@nogc
void in_camera_set_rotation(in_camera_t* cam, float rot) {
    (cast(Camera2D)cam).rotation = rot;
}

/**
    Gets the camera's rotation.

    Params:
        cam = The camera object.

    Returns:
        The camera's rotation.
*/
@nogc
float in_camera_get_rotation(in_camera_t* cam) {
    return (cast(Camera2D)cam).rotation;
}
/**
    Sets the camera's scale.

    Params:
        cam = The camera object.
        scale = The scale value to set to.
*/
@nogc
void in_camera_set_scale(in_camera_t* cam, float scale) {
    (cast(Camera2D)cam).scale = scale;
}

/**
    Gets the camera's scale.

    Params:
        cam = The camera object.

    Returns:
        The camera's scale.
*/
@nogc
float in_camera_get_zoom(in_camera_t* cam) {
    return (cast(Camera2D)cam).scale;
}


/**
    Gets the camera's center offset.

    Params:
        cam = The camera object.

    Returns:
        The camera's center offset.
*/
@nogc
in_vec2_t in_camera_get_center_offset(in_camera_t* cam) {
    return reinterpret_cast!in_vec2_t((cast(Camera2D)cam).centerOffset);
}

/**
    Copies the values of the internal camera matrix out to mat4

    Params:
        cam = The camera object.
        mat4 = The matrix to populate values with. Must have len 16
*/
@nogc
void in_camera_get_matrix(in_camera_t* cam, const(float)* mat4) {
    import core.stdc.string : memcpy;
    memcpy(cast(void*)mat4, (cast(Camera2D)cam).matrix.ptr, float.sizeof*16);
}

/**
    Destroys the camera.

    Params:
        cam = The camera to destroy.
*/
@nogc
void in_camera_destroy(in_camera_t* cam) {
    import core.memory : GC;

    if (cam) {
        GC.removeRoot(cast(void*)cam);
        assumeNoGC(&destroy!(false, Camera2D), cast(Camera2D)cam);
        GC.free(cam);
    }
}