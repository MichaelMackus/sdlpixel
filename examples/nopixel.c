#define SDLPIXEL_COMPILE
#include "SDL2/SDL.h"
#include <assert.h>
#include <time.h>

int main()
{
    int width = 1920;
    int height = 1080;

    SDL_Window *win = SDL_CreateWindow("Hello",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    if (win == NULL) {
        assert("ERROR: Unable to create SDL window" == 0);
    }

    /* SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); */
    SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        assert("ERROR: Unable to create SDL renderer" == 0);
    }

    SDL_Surface *sdlpixel_window_surface = SDL_GetWindowSurface(win);
    SDL_Surface *sdlpixel_surface = SDL_ConvertSurfaceFormat(sdlpixel_window_surface, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_RenderPresent(renderer);

    int quit = 0;
    SDL_Event event;
    int msec;
    clock_t start, diff;
    unsigned char r,g,b;
    uint32_t *pixels;
    int pitch = sdlpixel_surface->clip_rect.w;

    printf("Pitch: %d\n", pitch);

    pixels = (uint32_t*) sdlpixel_surface->pixels;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            start = clock();
            SDL_LockSurface(sdlpixel_surface);

            if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
                quit = 1;
            }

            r = rand() % 256;
            g = rand() % 256;
            b = rand() % 256;
            for (int y=0; y<height; ++y) {
                for (int x=0; x<width; ++x) {
                    pixels[x + y*pitch] = r << 24 | g << 16 | b << 8 | 0xFF;
                    ++r;
                    --g;
                    b ^= b;
                    ++b;
                }
                break;
            }

            SDL_UnlockSurface(sdlpixel_surface);

            SDL_Rect rect = sdlpixel_surface->clip_rect;
            SDL_Rect window_rect = sdlpixel_window_surface->clip_rect;
            if (rect.w != window_rect.w || rect.h != window_rect.h) {
                SDL_BlitScaled(sdlpixel_surface, &rect, sdlpixel_window_surface, &window_rect);
            } else {
                SDL_BlitSurface(sdlpixel_surface, &rect, sdlpixel_window_surface, &window_rect);
            }
            SDL_UpdateWindowSurface(win); // TODO avoid this so we can use sdl draw functions

            diff = clock() - start;
            msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
        }
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(sdlpixel_surface);
    SDL_Quit();

    return 0;
}
