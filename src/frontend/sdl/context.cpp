/**
 * Collection of utility functions to handle interacting with the SDL layer
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#include "context.hpp"
#include "abort.hpp"
#include "common/resource.hpp"

namespace Gbpp::Frontend::Sdl
{

Version get_version()
{
    const uint32_t version = SDL_GetVersion();

    return {.major = SDL_VERSIONNUM_MAJOR(version),
            .minor = SDL_VERSIONNUM_MINOR(version),
            .patch = SDL_VERSIONNUM_MICRO(version)};
}

bool init(Context &context,
          const std::string &window_title,
          const uint32_t screen_width,
          const uint32_t screen_height,
          const uint64_t window_flags,
          const std::string &font_file,
          std::span<const float> font_sizes)
{
    AbortOnSDLError(SDL_Init(SDL_INIT_VIDEO));

    /*
     * Create window and renderer.
     */
    context.window = SDL_CreateWindow(
        window_title.c_str(), screen_width, screen_height, window_flags);
    AbortOnSDLError(context.window);

    context.renderer = SDL_CreateRenderer(context.window, nullptr);
    AbortOnSDLError(context.renderer);

    /*
     * Initialize the TTF engine.
     */
    AbortOnSDLError(TTF_Init());
    context.text_engine = TTF_CreateRendererTextEngine(context.renderer);
    AbortOnSDLError(context.text_engine);

    /*
     * Load all fonts.
     */
    const auto font_path = Resource::get_resource_path(font_file);

    for (const auto font_size : font_sizes)
    {
        auto font = TTF_OpenFont(font_path.c_str(), font_size);
        AbortOnSDLError(font);
        context.fonts.push_back(font);
    }

    return true;
}

void quit(Context &context)
{
    /*
     * Check all context fields, because they might be nullptr if an
     * exception occured during initialization.
     */
    if (context.text_engine)
    {
        TTF_DestroyRendererTextEngine(context.text_engine);
    }

    /*
     * Close all fonts.
     */
    for (auto font : context.fonts)
    {
        TTF_CloseFont(font);
    }

    if (context.window)
    {
        SDL_DestroyWindow(context.window);
    }
    if (context.renderer)
    {
        SDL_DestroyRenderer(context.renderer);
    }
    SDL_Quit();
}

} // namespace Gbpp::Frontend::Sdl