/**
 * Functions for rendering the emulator screen and UI.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#include "Graphics.hpp"
#include "Font.hpp"

namespace Gbpp::Frontend::Graphics
{

void draw_frame(SDL::Context &sdl_context)
{
    SDL::fill_screen(sdl_context, SDL::BLACK);

    SDL::fill_rect(
        sdl_context, {.x = 0, .y = 0, .h = 576, .w = 640}, SDL::BLUE);

    SDL::fill_rect(sdl_context,
                   {.x = screen_width - 256, .y = 0, .w = 256, .h = 256},
                   SDL::WHITE);

    SDL::draw_text(sdl_context,
                   "Extra Small Text here owo",
                   {20.0, 20.0},
                   SDL::WHITE,
                   Font::EXTRA_SMALL);

    SDL::draw_text(sdl_context,
                   "Small Text here: 34fa",
                   {20.0, 40.0},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   "Medium Text here",
                   {20.0, 70.0},
                   SDL::WHITE,
                   Font::MEDIUM);

    SDL::draw_text(
        sdl_context, "Large text here", {20.0, 120.0}, SDL::WHITE, Font::LARGE);

    SDL::show(sdl_context);
}

} // namespace Gbpp::Frontend::Graphics