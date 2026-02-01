/**
 * Global configuration for font rendering.
 *
 * @author Niklas Vainio
 * @date   2026-01-31
 */

#pragma once

#include <array>

namespace Gbpp::Frontend::Font
{

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
inline const std::array<float, Size::Count> size_map = {
    8.0f, 12.0f, 24.0f, 36.0f};

} // namespace Gbpp::Frontend::Font