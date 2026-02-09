/**
 * Wrapper class around an SDL "streaming texture", whose data can be modified
 * at runtime.
 *
 * @author Niklas Vainio
 * @date 2026-02-08
 */

#pragma once

#include "context.hpp"
#include "types.hpp"
#include <SDL3/SDL.h>

namespace Gbpp::Frontend::Sdl
{

class RuntimeTexture
{
public:
    RuntimeTexture() = default;

    /**
     * Disallow copy/move.
     */
    RuntimeTexture(const RuntimeTexture &) = delete;
    RuntimeTexture &operator=(const RuntimeTexture &) = delete;
    RuntimeTexture(RuntimeTexture &&) = delete;
    RuntimeTexture &operator=(RuntimeTexture &&) = delete;

    /**
     * Initialize the texture. Assumes 4 byte-per-pixel RGBA rendering.
     *
     * @param context         SDL context
     * @param width           Texture width, in pixels
     * @param height          Texture height, in pixels
     *
     * @return True on success, false otherwise.
     */
    bool init(Context &context, const uint32_t width, const uint32_t height);

    /**
     * Deallocate the underlying texture.
     */
    void destroy();

    /**
     * Update the texture directly with a buffer of raw pixel data.
     *
     * @param pixels       Raw pointer to a buffer of pixels.
     *
     * @return True on success, false otherwise.
     */
    bool update(const Color *pixels);

    /**
     * Class providing a view to the pixels of the underlying texture. This
     * gets created when the lock is called, and calls a custom destruction
     * lambda when it does out of scope.
     */
    template <typename T>
    class PixelView
    {
    public:
        friend class RuntimeTexture;

        /**
         * Disallow copy/move.
         */
        PixelView(const PixelView &) = delete;
        PixelView &operator=(const PixelView &) = delete;
        PixelView(PixelView &&) = delete;
        PixelView &operator=(PixelView &&) = delete;

        /**
         * @returns A mutable reference to the pixel at the given coordinates
         */
        constexpr Color &operator()(const uint32_t x, const uint32_t y)
        {
            return pixels[x + y * width];
        }

        ~PixelView()
        {
            destructor_callback();
        }

    private:
        PixelView(const uint32_t width_, Color *pixels_, T destructor_callback_)
            : width(width_), pixels(pixels_),
              destructor_callback(destructor_callback_) {};

        /**
         * Width of the texture, in pixels.
         */
        uint32_t width;

        /**
         * Pointer to the underlying buffer.
         */
        Color *pixels;

        /**
         * Deletion function.
         */
        T destructor_callback;
    };

    /**
     * CTAD for PixelView.
     */
    template <class T>
    PixelView(uint32_t, Color *, T) -> PixelView<std::decay_t<T>>;

    /**
     * Lock the texture, allowing its internal data to be written to. The
     * returned RuntimeTexture::PixelView object unlocks the texture once it
     * goes out of scope.
     *
     * @return RuntimeTexture::PixelView object, allowing pixel modificiation.
     */
    auto lock()
    {
        Color *pixels{};
        int pitch{};
        SDL_LockTexture(
            texture, NULL, reinterpret_cast<void **>(&pixels), &pitch);

        return PixelView{static_cast<uint32_t>(pitch / sizeof(Color)),
                         pixels,
                         [this] { SDL_UnlockTexture(texture); }};
    }

    /**
     * Getter function for the internal texture.
     */
    SDL_Texture *get_underlying_texture() const
    {
        return texture;
    }

private:
    /**
     * Number of bytes per row of the texture.
     */
    uint32_t pitch{};

    /**
     * Underlying SDL texture resource.
     */
    SDL_Texture *texture{};
};

} // namespace Gbpp::Frontend::Sdl
