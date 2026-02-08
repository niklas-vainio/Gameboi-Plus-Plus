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

void draw_frame(Sdl::Context &sdl_context, const EmulatorDebugInfo &debug_info)
{
    Sdl::fill_screen(sdl_context, Sdl::BLACK);

    Sdl::fill_rect(sdl_context,
                   {.x = 0,
                    .y = 0,
                    .w = Layout::game_boy_viwer_width,
                    .h = Layout::game_boy_viwer_height},
                   Sdl::BLUE);

    Sdl::fill_rect(
        sdl_context,
        {.x = Layout::screen_width - 256, .y = 0, .w = 256, .h = 256},
        Sdl::WHITE);

    draw_cpu_status(sdl_context, debug_info.cpu);

    Sdl::show(sdl_context);
}

void draw_cpu_status(Sdl::Context &sdl_context, const CpuDebugInfo &cpu)
{
    static constexpr auto column_width = 100;

    float y = Layout::padding;
    float x = Layout::debug_panel_start + Layout::padding;

    Sdl::draw_text(sdl_context, "Cpu Status", {x, y}, Sdl::WHITE, Font::LARGE);
    y += Font::padding(Font::LARGE);

    /*
     * Registers
     */
    Sdl::draw_text(sdl_context,
                   std::format("A  {:02X}", cpu.A),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("F  {:02x}", cpu.F),
                   {x + column_width, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("B  {:02X}", cpu.B),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("C  {:02x}", cpu.C),
                   {x + column_width, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("D  {:02X}", cpu.D),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("E  {:02x}", cpu.E),
                   {x + column_width, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("H  {:02X}", cpu.H),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("L  {:02X}", cpu.L),
                   {x + column_width, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += 2 * Font::padding(Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("PC  {:04X}", cpu.pc),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    Sdl::draw_text(sdl_context,
                   std::format("SP  {:04X}", cpu.sp),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);

    /*
     * Flags
     */
    {
        static constexpr auto flag_spacing = 20;
        auto flag_x = x + column_width + 25;

        const auto color = [&](const auto bit)
        { return (cpu.F & (1 << bit)) ? Sdl::GREEN : Sdl::RED; };

        Sdl::draw_text(sdl_context, "Z", {flag_x, y}, color(7), Font::SMALL);
        flag_x += flag_spacing;
        Sdl::draw_text(sdl_context, "N", {flag_x, y}, color(6), Font::SMALL);
        flag_x += flag_spacing;
        Sdl::draw_text(sdl_context, "H", {flag_x, y}, color(5), Font::SMALL);
        flag_x += flag_spacing;
        Sdl::draw_text(sdl_context, "C", {flag_x, y}, color(4), Font::SMALL);
    }
    y += 2 * Font::padding(Font::SMALL);

    /*
     * Cycle count
     */
    Sdl::draw_text(sdl_context,
                   std::format("CYCLES  {}", cpu.num_cycles_elapsed),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += Font::padding(Font::SMALL);

    /**
     * Instruction Opcode
     */
    Sdl::draw_text(sdl_context,
                   std::format("OPCODE  {:02x}", cpu.opcode),
                   {x, y},
                   Sdl::WHITE,
                   Font::SMALL);
    y += 2 * Font::padding(Font::SMALL);

    /*
     * Assembly state
     */
    Sdl::draw_text(sdl_context,
                   cpu.current_instruction_asm,
                   {x, y},
                   Sdl::CYAN,
                   Font::MEDIUM);
}

} // namespace Gbpp::Frontend::Graphics