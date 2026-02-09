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

void populate_memory_viewer_texture(Sdl::RuntimeTexture &memory_viewer_texture,
                                    const EmulatorDebugInfo &debug_info)
{
    /*
     * Map pixel values to grayscale.
     */
    auto pixels = memory_viewer_texture.lock();

    for (auto x = 0; x < 256; x++)
    {
        for (auto y = 0; y < 256; y++)
        {
            const auto value = debug_info.memory_viewer_pixel_buffer(x, y);
            pixels(x, y) = {.r = value, .g = value, .b = value, .a = 255};
        }
    }

    /*
     * Render PC, SP, and HL with special colors.
     */
    pixels(debug_info.cpu.pc & 0xFF, debug_info.cpu.pc >> 8) = Sdl::RED;
    pixels(debug_info.cpu.sp & 0xFF, debug_info.cpu.sp >> 8) = Sdl::CYAN;
    pixels(debug_info.cpu.L, debug_info.cpu.H) = Sdl::GREEN;
}

void draw_frame(Sdl::Context &sdl_context,
                Sdl::RuntimeTexture &memory_viewer_texture,
                const EmulatorDebugInfo &debug_info)
{
    Sdl::fill_screen(sdl_context, Sdl::BLACK);

    Sdl::fill_rect(sdl_context,
                   {.left = 0,
                    .top = 0,
                    .width = Layout::game_boy_viwer_width,
                    .height = Layout::game_boy_viwer_height},
                   Sdl::BLUE);

    /**
     * Draw debug area.
     */
    Sdl::draw_runtime_texture(
        sdl_context,
        memory_viewer_texture,
        {.left = 0, .top = 0, .width = 512, .height = 512});

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