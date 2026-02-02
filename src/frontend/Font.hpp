/**
 * Global configuration for font rendering.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include <array>
#include <string>

namespace Gbpp::Frontend::Font
{

/**
 * Name of the font file to use.
 */
inline constexpr std::string font_file = "GameBoy.ttf";

/**
 * List of available font sizes.
 */
enum Size
{
    EXTRA_SMALL,
    SMALL,
    MEDIUM,
    LARGE,
    Count,
};

/**
 * Actual sizes for each font setting, defined in the order above.
 */
inline constexpr std::array<float, Size::Count> size_map = {
    8.0f, 12.0f, 24.0f, 36.0f};

/**
 * Amount of vertical padding (in pixels) to use after each font size, defined
 * in the order above.
 */
inline constexpr std::array<uint32_t, Size::Count> padding_map = {
    10, 13, 30, 36};

/**
 * Return the vertical padding (in pixels) for the given font size.
 *
 * @param[in] size      Font size
 * @return Amount of vertical padding to use, in pixels.
 */
inline constexpr uint32_t padding(const Size size)
{
    return padding_map[size];
}

} // namespace Gbpp::Frontend::Font