/**
 * Collection of utility functions to handle interacting with the SDL layer
 *
 * @author Niklas Vainio
 * @date 2026-01-30
 */

#include "context.hpp"
#include "abort.hpp"

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
             const uint64_t flags)
{
    AbortOnSdlError(SDL_Init(SDL_INIT_VIDEO));

    auto *window = AbortOnSdlError(SDL_CreateWindow(
        window_title.c_str(), screen_width, screen_height, flags));

    auto *renderer = AbortOnSdlError(SDL_CreateRenderer(window, nullptr));

    return {window, renderer};
}

void quit(Context &context)
{
    SDL_DestroyWindow(context.window);
    SDL_DestroyRenderer(context.renderer);
    SDL_Quit();
}

} // namespace Gbpp::Frontend::SDL