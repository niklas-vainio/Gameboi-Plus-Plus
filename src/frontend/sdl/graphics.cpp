/**
 * Collection of utility functions for rendering in SDL.
 *
 * @author Niklas Vainio
 * @date   2026-01-30
 */

#include "graphics.hpp"

namespace Gbpp::Frontend::Sdl
{
void fill_screen(Context &context, const Color color)
{
    SDL_SetRenderDrawColor(
        context.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(context.renderer);
}

void fill_rect(Context &context, const Rect<float> rect, const Color color)
{
    SDL_SetRenderDrawColor(
        context.renderer, color.r, color.g, color.b, color.a);

    const auto sdl_rect = rect.to_sdl();
    SDL_RenderFillRect(context.renderer, &sdl_rect);
}

void draw_text(Context &context,
               const std::string &text,
               const Position<float> position,
               const Color color,
               const uint32_t font_size)
{
    TTF_Font *font = context.fonts[font_size];

    TTF_Text *text_object =
        TTF_CreateText(context.text_engine, font, text.c_str(), 0);

    TTF_SetTextColor(text_object, color.r, color.g, color.b, color.a);
    TTF_DrawRendererText(text_object, position.x, position.y);

    TTF_DestroyText(text_object);
}

void draw_runtime_texture(Context &context,
                          RuntimeTexture &texture,
                          const Rect<float> rect)
{
    const auto sdl_rect = rect.to_sdl();

    SDL_RenderTexture(
        context.renderer, texture.get_underlying_texture(), NULL, &sdl_rect);
}

void show(Context &context)
{
    SDL_RenderPresent(context.renderer);
}

} // namespace Gbpp::Frontend::Sdl