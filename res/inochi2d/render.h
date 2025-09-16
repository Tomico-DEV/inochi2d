#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "inochi2d/inochi2d.h"

#ifndef H_INOCHI2D_RENDER
#define H_INOCHI2D_RENDER

#define IN_MAX_ATTACHMENTS 8

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

typedef uint32_t uint;

/**
    A resource that can be transferred between CPU and GPU.
*/
struct in_resource_t;

/**
    Gets the length of the resource in bytes.

    Params:
        obj = The resource object.
    
    Returns:
        The length of the resource's GPU memory allocation
        in bytes.
*/
EXPORT_I2D uint in_resource_get_length(in_resource_t* obj);
/**
    Gets the renderer ID of the resource.

    Params:
        obj = The resource object.
    
    Returns:
        The renderer ID of the resource.
*/
EXPORT_I2D void* in_resource_get_id(in_resource_t* obj);

/**
    Sets the renderer ID of the resource.

    Params:
        obj = The resource object.
        value = The value to set.
*/
EXPORT_I2D void in_resource_set_id(in_resource_t* obj, void* value);

//
//              TEXTURES
//

/**
    A texture.
*/
struct in_texture_t;

/**
    Creates a texture from a resource.

    Params:
        obj = The resource object.
    
    Returns:
        The texture object that is represented by the
        resource, or $(D null) if the resource is not
        a texture.
*/
EXPORT_I2D in_texture_t* in_texture_from_resource(in_resource_t* obj);

/**
    Gets the width of the texture in pixels.

    Params:
        obj = The texture object.

    Returns:
        The width of the texture in pixels.
*/
EXPORT_I2D uint in_texture_get_width(in_texture_t* obj);

/**
    Gets the height of the texture in pixels.

    Params:
        obj = The texture object.

    Returns:
        The height of the texture in pixels.
*/
EXPORT_I2D uint in_texture_get_height(in_texture_t* obj);

/**
    Gets the channels of the texture.

    Params:
        obj = The texture object.

    Returns:
        The channel count of the texture.
*/
EXPORT_I2D uint in_texture_get_channels(in_texture_t* obj);

/**
    Flips the texture's data vertically.
    Some engines read in a different direction from Inochi2D.

    Params:
        obj = The texture object.
*/
EXPORT_I2D void in_texture_flip_vertically(in_texture_t* obj);

/**
    Premultiplies the alpha channel of the texture.

    Params:
        obj = The texture object.
*/
EXPORT_I2D void in_texture_premultiply(in_texture_t* obj);

/**
    Un-premultiplies the alpha channel of the texture.

    Params:
        obj = The texture object.
*/
EXPORT_I2D void in_texture_unpremultiply(in_texture_t* obj);

/**
    Pads the texture with a border.

    Params:
        obj =       The texture object.
        thickness = Thickness of the border in pixels.
*/
EXPORT_I2D void in_texture_pad(in_texture_t* obj, uint thickness);

/**
    Gets the pixels of the texture.

    Params:
        obj = The texture object.

    Returns:
        The pixels of the texture.
*/
EXPORT_I2D void* in_texture_get_pixels(in_texture_t* obj);

//
//              DRAWLIST
//

/**
    DrawState flags
*/
enum in_drawstate_t
{
    IN_DRAW_STATE_NORMAL            = 0,
    IN_DRAW_STATE_DEFINE_MASK       = 1,
    IN_DRAW_STATE_MASKED_DRAW       = 2,
    IN_DRAW_STATE_COMPOSITE_BEGIN   = 3,
    IN_DRAW_STATE_COMPOSITE_END     = 4,
    IN_DRAW_STATE_COMPOSITE_BLIT    = 5
};

/**
    Masking modes
*/
enum in_mask_mode_t
{
    IN_MASK_MODE_MASK   = 0,
    IN_MASK_MODE_DODGE  = 1
};

/**
    Blending modes
*/
enum in_blend_mode_t
{
    IN_BLEND_MODE_NORMAL            = 0x00,
    IN_BLEND_MODE_MULTIPLY          = 0x01,
    IN_BLEND_MODE_SCREEN            = 0x02,
    IN_BLEND_MODE_OVERLAY           = 0x03,
    IN_BLEND_MODE_DARKEN            = 0x04,
    IN_BLEND_MODE_LIGHTEN           = 0x05,
    IN_BLEND_MODE_COLOR_DODGE       = 0x06,
    IN_BLEND_MODE_LINEAR_DODGE      = 0x07,
    IN_BLEND_MODE_ADD_GLOW          = 0x08,
    IN_BLEND_MODE_COLOR_BURN        = 0x09,
    IN_BLEND_MODE_HARD_LIGHT        = 0x0A,
    IN_BLEND_MODE_SOFT_LIGHT        = 0x0B,
    IN_BLEND_MODE_DIFFERENCE        = 0x0C,
    IN_BLEND_MODE_EXCLUSION         = 0x0D,
    IN_BLEND_MODE_SUBTRACT          = 0x0E,
    IN_BLEND_MODE_INVERSE           = 0x0F,
    IN_BLEND_MODE_DESTINATION_IN    = 0x10,
    IN_BLEND_MODE_SOURCE_IN         = 0x11,
    IN_BLEND_MODE_SOURCE_OUT        = 0x12
};

/**
    A drawing command from the Inochi2D draw list
*/
struct in_drawcmd_t {
    in_texture_t*                       sources[IN_MAX_ATTACHMENTS];
    in_drawstate_t                      state;
    in_blend_mode_t                     blendMode;
    in_mask_mode_t                      maskMode;
    uint                                allocId;
    uint                                vtxOffset;
    uint                                idxOffset;
    uint                                elemCount;
    uint                                type;
    unsigned char                       vars[64];
};

/**
    A drawlist mesh allocation
*/
struct in_drawalloc_t {
    uint vtxOffset;
    uint idxOffset;
    uint idxCount;
    uint vtxCount;
    uint allocId;
};

/**
    A drawlist instance
*/
struct in_drawlist_t;

/**
    Gets whether the draw list uses base vertex offsets.

    Params:
        obj = The drawlist
    
    Returns:
        $(D true) if base vertex offsets are being generated,
        $(D false) otherwise.
*/
EXPORT_I2D bool in_drawlist_get_use_base_vertex(in_drawlist_t* obj);

/**
    Sets whether the draw list uses base vertex offsets.

    Params:
        obj =   The drawlist
        value = The value to set.
*/
EXPORT_I2D void in_drawlist_set_use_base_vertex(in_drawlist_t* obj, bool value);

/**
    Gets all of the commands stored in the draw list for iteration.
    
    This memory is owned by the draw list and should not be freed
    by you.

    Params:
        obj =   The drawlist
        count = Where to store the command count
    
    Returns:
        A pointer to an array of draw commands
*/
EXPORT_I2D in_drawcmd_t* in_drawlist_get_commands(in_drawlist_t* obj, uint* count);

/**
    Gets all of the vertex data stored in the draw list.
    
    This memory is owned by the draw list and should not be freed
    by you.

    Params:
        obj =   The drawlist
        bytes = Where to store the byte count of the data.
    
    Returns:
        A pointer to the data
*/
EXPORT_I2D void* in_drawlist_get_vertex_data(in_drawlist_t* obj, uint* bytes);

/**
    Gets all of the index data stored in the draw list.
    
    This memory is owned by the draw list and should not be freed
    by you.

    Params:
        obj =   The drawlist
        bytes = Where to store the byte count of the data.
    
    Returns:
        A pointer to the data
*/
EXPORT_I2D void* in_drawlist_get_index_data(in_drawlist_t* obj, uint* bytes);

/**
    Gets all of the allocated meshes of the drawlist.
    
    This memory is owned by the draw list and should not be freed
    by you.

    Params:
        obj =   The drawlist
        count = Where to store the element count
    
    Returns:
        A pointer to the data
*/
EXPORT_I2D in_drawalloc_t* in_drawlist_get_allocations(in_drawlist_t* obj, uint* count);

#ifdef __cplusplus
}
#endif


#endif
