/**
 * Collection of local mirrors of SDL types, for dependency management.
 *
 * @author Niklas Vainio
 * @date 2026-02-08
 */

#pragma once

#include <SDL3/SDL.h>

namespace Gbpp::Frontend::Sdl
{

/**
 * Alias the native Color type to this namespace.
 */
using Color = SDL_Color;

/**
 * Struct to store a screen position with coordinates of any type (typically an
 * int/float).
 */
template <typename T>
struct Position
{
    T x{};
    T y{};
};

/**
 * Struct to store a rectangle with coordinates of any type (typically an
 * int/float).
 */
template <typename T>
struct Rect
{
    T left{};
    T top{};
    T width{};
    T height{};
};

template <>
struct Rect<float>
{
    float left{};
    float top{};
    float width{};
    float height{};

    SDL_FRect to_sdl() const
    {
        return {.x = left, .y = top, .w = width, .h = height};
    }
};

} // namespace Gbpp::Frontend::Sdl
