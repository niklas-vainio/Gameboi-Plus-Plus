/**
 * Wrapper class around an SDL "streaming texture", whose data can be modified
 * at runtime.
 *
 * @author Niklas Vainio
 * @date 2026-02-08
 */

#include "runtime_texture.hpp"
#include "abort.hpp"

namespace Gbpp::Frontend::Sdl
{

bool RuntimeTexture::init(Context &context,
                          const uint32_t width,
                          const uint32_t height)
{
    pitch = width * sizeof(Color);
    texture = SDL_CreateTexture(context.renderer,
                                SDL_PixelFormat::SDL_PIXELFORMAT_RGBA32,
                                SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING,
                                width,
                                height);

    AbortOnSDLError(texture);

    /*
     * Use nearest neighbor mode for clean scaling, and disable alpha blending.
     */
    AbortOnSDLError(SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST));
    AbortOnSDLError(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE));
    return true;
}

bool RuntimeTexture::update(const Color *pixels)
{
    AbortOnSDLError(SDL_UpdateTexture(texture, NULL, pixels, pitch));
    return true;
}

void RuntimeTexture::destroy()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

} // namespace Gbpp::Frontend::Sdl