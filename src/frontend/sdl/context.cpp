/**
 * Collection of utility functions to handle interacting with the SDL layer
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#include "context.hpp"
#include "abort.hpp"
#include "common/resource.hpp"

namespace Gbpp::Frontend::SDL
{

Version get_version()
{
    const uint32_t version = SDL_GetVersion();

    return {.major = SDL_VERSIONNUM_MAJOR(version),
            .minor = SDL_VERSIONNUM_MINOR(version),
            .patch = SDL_VERSIONNUM_MICRO(version)};
}

Context init(const std::string &window_title,
             const uint32_t screen_width,
             const uint32_t screen_height,
             const uint64_t window_flags,
             const std::string &font_file,
             std::span<const float> font_sizes)
{
    Context context{};

    AbortOnSdlError(SDL_Init(SDL_INIT_VIDEO));

    /*
     * Create window and renderer.
     */
    context.window = AbortOnSdlError(SDL_CreateWindow(
        window_title.c_str(), screen_width, screen_height, window_flags));

    context.renderer =
        AbortOnSdlError(SDL_CreateRenderer(context.window, nullptr));

    /*
     * Initialize the TTF engine.
     */
    AbortOnSdlError(TTF_Init());
    context.text_engine =
        AbortOnSdlError(TTF_CreateRendererTextEngine(context.renderer));

    /*
     * Load all fonts.
     */
    const auto font_path = Resource::get_resource_path(font_file);

    for (const auto font_size : font_sizes)
    {
        auto font = AbortOnSdlError(TTF_OpenFont(font_path.c_str(), font_size));
        context.fonts.push_back(font);
    }

    return context;
}

void quit(Context &context)
{
    TTF_DestroyRendererTextEngine(context.text_engine);

    /*
     * Close all fonts.
     */
    for (auto font : context.fonts)
    {
        TTF_CloseFont(font);
    }

    SDL_DestroyWindow(context.window);
    SDL_DestroyRenderer(context.renderer);
    SDL_Quit();
}

} // namespace Gbpp::Frontend::SDL