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

    draw_cpu_status(sdl_context, debug_info.cpu);

    SDL::show(sdl_context);
}

void draw_cpu_status(SDL::Context &sdl_context, const CpuDebugInfo &cpu)
{
    static constexpr auto column_width = 100;

    float y = Layout::padding;
    float x = Layout::debug_panel_start + Layout::padding;

    SDL::draw_text(sdl_context, "CPU Status", {x, y}, SDL::WHITE, Font::LARGE);
    y += Font::padding(Font::LARGE);

    /*
     * Registers
     */
    SDL::draw_text(sdl_context,
                   std::format("A  {:02X}", cpu.A),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("F  {:02x}", cpu.F),
                   {x + column_width, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("B  {:02X}", cpu.B),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("C  {:02x}", cpu.C),
                   {x + column_width, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("D  {:02X}", cpu.D),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("E  {:02x}", cpu.E),
                   {x + column_width, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("H  {:02X}", cpu.H),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("L  {:02X}", cpu.L),
                   {x + column_width, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += 2 * Font::padding(Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("PC  {:04X}", cpu.pc),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    SDL::draw_text(sdl_context,
                   std::format("SP  {:04X}", cpu.sp),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);

    /*
     * Flags
     */
    {
        static constexpr auto flag_spacing = 20;
        auto flag_x = x + column_width + 25;

        const auto color = [&](const auto bit)
        { return (cpu.F & (1 << bit)) ? SDL::GREEN : SDL::RED; };

        SDL::draw_text(sdl_context, "Z", {flag_x, y}, color(7), Font::SMALL);
        flag_x += flag_spacing;
        SDL::draw_text(sdl_context, "N", {flag_x, y}, color(6), Font::SMALL);
        flag_x += flag_spacing;
        SDL::draw_text(sdl_context, "H", {flag_x, y}, color(5), Font::SMALL);
        flag_x += flag_spacing;
        SDL::draw_text(sdl_context, "C", {flag_x, y}, color(4), Font::SMALL);
    }
    y += 2 * Font::padding(Font::SMALL);

    /*
     * Cycle count
     */
    SDL::draw_text(sdl_context,
                   std::format("CYCLES  {}", cpu.num_cycles_elapsed),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    /**
     * Instruction Opcode
     */
    SDL::draw_text(sdl_context,
                   std::format("OPCODE  {:02x}", cpu.opcode),
                   {x, y},
                   SDL::WHITE,
                   Font::SMALL);
    y += 2 * Font::padding(Font::SMALL);

    /*
     * Assembly state
     */
    SDL::draw_text(sdl_context,
                   cpu.current_instruction_asm,
                   {x, y},
                   SDL::CYAN,
                   Font::MEDIUM);
}

} // namespace Gbpp::Frontend::Graphics