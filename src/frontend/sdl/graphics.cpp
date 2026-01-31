/**
 * Collection of utility functions for rendering in SDL.
 *
 * @author Niklas Vainio
 * @date 2026-01-30
 */

#include "graphics.hpp"

namespace Gbpp::Frontend::SDL
{
void fill_screen(Context &context, SDL_Color color)
{
    SDL_SetRenderDrawColor(
        context.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(context.renderer);
}

void show(Context &context)
{
    SDL_RenderPresent(context.renderer);
}

} // namespace Gbpp::Frontend::SDL