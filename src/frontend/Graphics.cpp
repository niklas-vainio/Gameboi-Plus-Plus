/**
 * Functions for rendering the emulator screen and UI.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#include "Graphics.hpp"
#include "Font.hpp"
#include <format>

namespace Gbpp::Frontend::Graphics
{

void draw_frame(SDL::Context &sdl_context, const EmulatorDebugInfo &debug_info)
{
    SDL::fill_screen(sdl_context, SDL::BLACK);

    SDL::fill_rect(
        sdl_context, {.x = 0, .y = 0, .h = 576, .w = 640}, SDL::BLUE);

    SDL::fill_rect(sdl_context,
                   {.x = screen_width - 256, .y = 0, .w = 256, .h = 256},
                   SDL::WHITE);

    SDL::draw_text(
        sdl_context,
        std::format("CPU: PC = {:04X}", debug_info.num_instructions_executed),
        {20.0, 50.0},
        SDL::WHITE,
        Font::MEDIUM);

    SDL::show(sdl_context);
}

} // namespace Gbpp::Frontend::Graphics