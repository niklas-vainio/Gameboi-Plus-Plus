/**
 * Class representing a 2D array of pixels (with arbitrary underlying type),
 * used to pass graphics data to the frontend.
 *
 * @author Niklas Vainio
 * @date 2026-02-08
 */

#pragma once

#include "GameBoyConstants.hpp"
#include <array>
#include <cstdint>

namespace Gbpp
{

template <typename T, std::size_t Width, std::size_t Height>
class PixelBuffer
{
public:
    static constexpr auto width = Width;
    static constexpr auto height = Height;
    static constexpr auto num_pixels = width * height;

    PixelBuffer() = default;

    /**
     * Disallow copy and move.
     */
    PixelBuffer(const PixelBuffer &) = delete;
    PixelBuffer &operator=(const PixelBuffer &) = delete;
    PixelBuffer(PixelBuffer &&) = delete;
    PixelBuffer &operator=(PixelBuffer &&) = delete;

    /**
     * @return Raw read-only pointer to the underlying pixel data in row-major
     * order.
     */
    const T *raw_data() const
    {
        return pixels.data();
    }

    /**
     * Getter methods returning references to specific pixels.
     * @{
     */
    T &operator()(const std::size_t x, const std::size_t y)
    {
        return pixels.at(x + y * Width);
    }
    const T &operator()(const std::size_t x, const std::size_t y) const
    {
        return pixels.at(x + y * Width);
    }
    /**
     * @}
     */

    /**
     * Fill the entire internal buffer with the given value.
     *
     * @param value     Value to fill with.
     */
    void fill(const T value)
    {
        pixels.fill(value);
    }

private:
    /**
     * Internal array of pixels.
     */
    std::array<T, Width * Height> pixels{};
};

/**
 * Fixed definitions for buffers passed between the frontend and backend.
 */
using MemoryViewerPixelBuffer = PixelBuffer<uint8_t, 256, 256>;
using ScreenPixelBuffer = PixelBuffer<uint8_t,
                                      GameBoyConstants::screen_width,
                                      GameBoyConstants::screen_height>;

} // namespace Gbpp