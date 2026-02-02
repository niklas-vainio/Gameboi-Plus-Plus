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

    SDL::fill_rect(sdl_context,
                   {.x = 0,
                    .y = 0,
                    .w = Layout::game_boy_viwer_width,
                    .h = Layout::game_boy_viwer_height},
                   SDL::BLUE);

    SDL::fill_rect(
        sdl_context,
        {.x = Layout::screen_width - 256, .y = 0, .w = 256, .h = 256},
        SDL::WHITE);

    SDL::draw_text(
        sdl_context,
        std::format("INSTRS {}", debug_info.cpu.num_instructions_executed),
        {Layout::debug_panel_start + Layout::padding, Layout::padding},
        SDL::WHITE,
        Font::SMALL);

    SDL::draw_text(
        sdl_context,
        std::format("CYCLES {}", debug_info.cpu.num_cycles_elapsed),
        {Layout::debug_panel_start + Layout::padding, Layout::padding + 30.0},
        SDL::WHITE,
        Font::SMALL);

    SDL::show(sdl_context);
}

} // namespace Gbpp::Frontend::Graphics