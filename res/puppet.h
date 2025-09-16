#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "render.h"
#include "package.h"

#ifndef H_INOCHI2D_PUPPET
#define H_INOCHI2D_PUPPET

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
//              PUPPET
//

typedef uint32_t uint;

/**
    Opaque handle to a puppet.
*/
struct in_puppet_t;
/**
    A texture cache.
*/
struct in_texture_cache_t;
struct in_parameter_t;

/**
    Loads a puppet into memory.

    Params:
        file = The file to load.
    
    Returns:
        A new puppet instance, or $(D null) on failure.
    
    See_Also:
        $(D in_get_last_error)
*/
EXPORT_I2D in_puppet_t* in_puppet_load(const char* file);

/**
    Loads a puppet into memory.

    Params:
        data = The data of the puppet.
        length = The length of that data in bytes.
    
    Returns:
        A new puppet instance, or $(D null) on failure.
    
    See_Also:
        $(D in_get_last_error)
*/
EXPORT_I2D in_puppet_t* in_puppet_load_from_memory(const uint8_t* data, uint length);

/**
    Frees a puppet from memory.

    Notes:
        The main Inochi2D type hirearchy hasn't been converted
        to numem types yet, as such this simply unpins it
        from the D GC.

    Params:
        obj = The puppet object.
*/
EXPORT_I2D void in_puppet_free(in_puppet_t* obj);

/**
    Gets the name of a puppet.

    Params:
        obj = The puppet object.

    Returns:
        The name of the puppet as specified by
        its author.
*/
EXPORT_I2D const char* in_puppet_get_name(in_puppet_t* obj);

/**
    Gets whether to calculate physics for the puppet.

    Params:
        obj = The puppet object.

    Returns:
        Whether physics are enabled.
*/
EXPORT_I2D bool in_puppet_get_physics_enabled(in_puppet_t* obj);

/**
    Sets whether to calculate physics for the puppet.

    Params:
        obj =   The puppet object.
        value = The value to set.
*/
EXPORT_I2D void in_puppet_set_physics_enabled(in_puppet_t* obj, bool value);

/**
    Gets the pixel-to-meter unit mapping for the physics system.

    Params:
        obj = The puppet object.

    Returns:
        A value describing how many pixels count as a meter.
*/
EXPORT_I2D float in_puppet_get_pixels_per_meter(in_puppet_t* obj);

/**
    Sets the pixel-to-meter unit mapping for the physics system.

    Params:
        obj =   The puppet object.
        value = The value to set.
*/
EXPORT_I2D void in_puppet_set_pixels_per_meter(in_puppet_t* obj, float value);

/**
    Gets the gravity constant for the puppet.

    Params:
        obj = The puppet object.

    Returns:
        A value describing how many meters a second gravity
        pulls on the puppet. Normally is 9.8.
*/
EXPORT_I2D float in_puppet_get_gravity(in_puppet_t* obj);

/**
    Sets the gravity constant for the puppet.

    Params:
        obj =   The puppet object.
        value = The value to set.
*/
EXPORT_I2D void in_puppet_set_gravity(in_puppet_t* obj, float value);

/**
    Updates a puppet.

    Params:
        obj = The puppet object.
        delta = Time since last frame.
*/
EXPORT_I2D void in_puppet_update(in_puppet_t* obj, float delta);

/**
    Draws a puppet.

    Params:
        obj = The puppet object.
        delta = Time since last frame.
*/
EXPORT_I2D void in_puppet_draw(in_puppet_t* obj, float delta);

/**
    Resets the physics state for the puppet.

    Params:
        obj = The puppet object.
*/
EXPORT_I2D void in_puppet_reset_drivers(in_puppet_t* obj);

/**
    Gets the texture cache belonging to the puppet.

    Params:
        obj = The puppet object.
    
    Returns:
        The texture cache associated with the puppet.
*/
EXPORT_I2D in_texture_cache_t* in_puppet_get_texture_cache(in_puppet_t* obj);

/**
    Gets the parameters of the puppet.

    Params:
        obj = The puppet object.
        count = Where to store the parameter element count.
    
    Returns:
        A puppet-owned array of parameters.
*/
EXPORT_I2D in_parameter_t** in_puppet_get_parameters(in_puppet_t* obj, uint* count);
/**
    Gets the puppet's draw list.

    Params:
        obj = The puppet object.
    
    Returns:
        The drawlist used by the puppet.
*/
EXPORT_I2D in_drawlist_t* in_puppet_get_drawlist(in_puppet_t* obj);

//
//              PARAMETERS
//

struct in_parameter_t;

/**
    Gets the name of the parameter.
    
    Params:
        obj = The parameter object.
    
    Returns:
        The name of the parameter.
*/
EXPORT_I2D const char* in_parameter_get_name(in_parameter_t* obj);

/**
    Gets whether the parameter is active.
    
    Params:
        obj = The parameter object.
    
    Returns:
        $(D true) if the parameter is active,
        $(D false) otherwise.
*/
EXPORT_I2D bool in_parameter_get_active(in_parameter_t* obj);

/**
    Gets how many dimensions the parameter has.
    
    Params:
        obj = The parameter object.
    
    Returns:
        A number which indicates how many dimensions
        the parameter has.
*/
EXPORT_I2D uint in_parameter_get_dimensions(in_parameter_t* obj);

/**
    Gets the parameter's minimum value.
    
    Params:
        obj = The parameter object.
    
    Returns:
        The parameter's minimum value.
*/
EXPORT_I2D in_vec2_t in_parameter_get_min_value(in_parameter_t* obj);

/**
    Gets the parameter's maximum value.
    
    Params:
        obj = The parameter object.
    
    Returns:
        The parameter's maximum value.
*/
EXPORT_I2D in_vec2_t in_parameter_get_max_value(in_parameter_t* obj);

/**
    Gets the parameter's current value.
    
    Params:
        obj = The parameter object.
    
    Returns:
        The parameter's current value.
*/
EXPORT_I2D in_vec2_t in_parameter_get_value(in_parameter_t* obj);

/**
    Sets the parameter's current value.
    
    Params:
        obj =   The parameter object.
        value = The value to set.
*/
EXPORT_I2D void in_parameter_set_value(in_parameter_t* obj, in_vec2_t value);

/**
    Gets the parameter's current value normalized to
    a range of 0..1
    
    Params:
        obj = The parameter object.
    
    Returns:
        The parameter's current normalized value.
*/
EXPORT_I2D in_vec2_t in_parameter_get_normalized_value(in_parameter_t* obj);

/**
    Sets the parameter's current value normalized to
    a range of 0..1
    
    Params:
        obj =   The parameter object.
        value = The value to set.
*/
EXPORT_I2D void in_parameter_set_normalized_value(in_parameter_t* obj, in_vec2_t value);

//
//              TEXTURE CACHE
//

/**
    Gets the size (amount of textures) of the texture cache.

    Params:
        obj = The texture cache object.

    Returns:
        The amount of textures within the cache.
*/
EXPORT_I2D uint in_texture_cache_get_size(in_texture_cache_t* obj);

/**
    Gets a texture from the cache.

    Params:
        obj = The texture cache object.
        slot = The slot to get the texture from.

    Returns:
        The requested texture if found,
        otherwise $(D null).
*/
EXPORT_I2D in_texture_t* in_texture_cache_get_texture(in_texture_cache_t* obj, uint slot);

/**
    Gets a texture from the cache.

    Params:
        obj = The texture cache object.
        count = Where to store the texture count.

    Returns:
        A puppet-owned array of textures.
*/

EXPORT_I2D in_texture_t** in_texture_cache_get_textures(in_texture_cache_t* obj, uint* count);

/**
    Prunes the texture cache of unreferenced textures.

    Params:
        obj = The texture cache object.
*/
EXPORT_I2D void in_texture_cache_prune(in_texture_cache_t* obj);

#ifdef __cplusplus
}
#endif


#endif
