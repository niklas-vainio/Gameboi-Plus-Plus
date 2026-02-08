/**
 * Collection of utility functions to handle interacting with the SDL layer
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

namespace Gbpp::Frontend::Sdl
{

/**
 * Struct representing the SDL version.
 */
struct Version
{
    uint32_t major{};
    uint32_t minor{};
    uint32_t patch{};
};

/**
 * @return The currently active SDL version
 */
Version get_version();

/**
 * Collection of objects defining the currently open SDL session.
 */
struct Context
{
    SDL_Window *window{};
    SDL_Renderer *renderer{};

    /*
     * Configurations for TTF font rendering.
     */
    TTF_TextEngine *text_engine{};
    std::vector<TTF_Font *> fonts{};
};

/**
 * Initialize SDL, popualting the given context struct.
 *
 * @param[out] context      Context to be populated
 * @param[in]  window_title  Title for the window.
 * @param[in]  screen_width  Width of the screen, in pixels.
 * @param[in]  screen_height Height of the screen, in pixels.
 * @param[in]  window_flags  Window settings.
 * @param[in]  font_file     Filename of the font for text.
 * @param[in]  font_sizes    List of font sizes to load.
 *
 * @return True on success, false otherwise.
 */
bool init(Context &context,
          const std::string &window_title,
          const uint32_t screen_width,
          const uint32_t screen_height,
          const uint64_t window_flags,
          const std::string &font_file,
          std::span<const float> font_sizes);

/**
 * Destroy the currently running SDL instance.
 *
 * @param[in] context   Current SDL context.
 */
void quit(Context &context);

} // namespace Gbpp::Frontend::Sdl