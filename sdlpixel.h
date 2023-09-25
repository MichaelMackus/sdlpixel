/**
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SDLPIXEL_LIB_H
#define SDLPIXEL_LIB_H

#include "SDL2/SDL.h"
#include <assert.h>

#ifdef __cplusplus
extern "C"{
#endif 

// sdlpixel_create creates SDL window & also calls sdlpixel_init
void sdlpixel_create(const char *title, unsigned int width, unsigned int height);

// sdlpixel_create_with_flags is a convenience function (e.g. for fullscreen windows)
void sdlpixel_create_with_flags(const char *title, unsigned int width, unsigned int height, Uint32 window_flags);

// initialize SDL and sdlpixel library
void sdlpixel_init(SDL_Window *from_window, SDL_Renderer *from_renderer);

// associates a surface with sdlpixel
// NOTE: you are responsible for freeing the surface passed to this function
void sdlpixel_use_surface(SDL_Surface *from_surface);

// calls SDL_Quit and frees memory
void sdlpixel_quit();

void sdlpixel_refresh();
void sdlpixel_clear();
SDL_Window *sdlpixel_get_window();

SDL_Color sdlpixel_rgb(uint8_t r, uint8_t g, uint8_t b);
SDL_Color sdlpixel_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void sdlpixel_plot(unsigned int x, unsigned int y, const SDL_Color *color);

#ifdef SDLPIXEL_COMPILE

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Surface *window_surface;
uint32_t *pixels;

void sdlpixel_create(const char *title, unsigned int width, unsigned int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        assert("ERROR: Unable to init SDL video" == 0);
    }

    sdlpixel_create_with_flags(title, width, height, SDL_WINDOW_SHOWN);
}

void sdlpixel_create_with_flags(const char *title, unsigned int width, unsigned int height, Uint32 window_flags)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        assert("ERROR: Unable to init SDL video" == 0);
    }

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              width,
                              height, 
                              window_flags);


    if (window == NULL) {
        assert("ERROR: Unable to create SDL window" == 0);
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        assert("ERROR: Unable to create SDL renderer" == 0);
    }

    sdlpixel_init(window, renderer);
}

void sdlpixel_init(SDL_Window *from_window, SDL_Renderer *from_renderer)
{
    assert(from_window);
    assert(from_renderer);

    window = from_window;
    renderer = from_renderer;

    window_surface = SDL_GetWindowSurface(window);

    if (window_surface == NULL) {
        assert("ERROR: Unable to get SDL surface" == 0);
    }

    surface = SDL_ConvertSurfaceFormat(window_surface, SDL_PIXELFORMAT_RGBA8888, 0);

    if (surface == NULL) {
        assert("ERROR: Unable to convert SDL surface" == 0);
    }

    SDL_RenderPresent(renderer);
}

void sdlpixel_use_surface(SDL_Surface *from_surface)
{
    if (surface) {
        SDL_FreeSurface(surface);
    }

    surface = SDL_ConvertSurfaceFormat(from_surface, SDL_PIXELFORMAT_RGBA8888, 0);
}

SDL_Window *sdlpixel_get_window()
{
    return window;
}

void sdlpixel_quit()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_Quit();
}

void sdlpixel_refresh()
{
    if (surface->locked) {
        SDL_UnlockSurface(surface);
    }
    sdlpixel_clear();
    SDL_Rect rect = surface->clip_rect;
    SDL_Rect window_rect = window_surface->clip_rect;
    if (rect.w != window_rect.w || rect.h != window_rect.h) {
        SDL_BlitScaled(surface, &rect, window_surface, &window_rect);
    } else {
        SDL_BlitSurface(surface, &rect, window_surface, &window_rect);
    }
    SDL_UpdateWindowSurface(window);
}

void sdlpixel_clear()
{
    SDL_RenderClear(renderer);
}

SDL_Color sdlpixel_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return sdlpixel_rgba(r, g, b, 0xFF);
}

SDL_Color sdlpixel_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;

    return color;
}

void sdlpixel_plot(unsigned int x, unsigned int y, const SDL_Color *color)
{
    if (!surface->locked) {
        SDL_LockSurface(surface);
        pixels = (uint32_t*) surface->pixels;
    }

    pixels[x + y*surface->clip_rect.w] = color->r << 24 | color->g << 16 | color->b << 8 | color->a;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
