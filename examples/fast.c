#include <time.h>
#include <SDL2/SDL.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Raw SDL2 pixel plotting example with surface blitting.
 */
int main()
{
    const int windowWidth = 1920;
    const int windowHeight = 1080;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Practice making sdl Window",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth,
            windowHeight, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Quit();
        return 2;
    }

    // We create a renderer with hardware acceleration, we also present according with the vertical sync refresh.
    /* SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ; */
    SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED) ;
    SDL_GL_SetSwapInterval(0);

    int quit = 0;
    SDL_Event event;

    /* SDL_HasWindowSurface(); */
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    SDL_Surface *surface;

    surface = SDL_ConvertSurfaceFormat(window_surface, SDL_PIXELFORMAT_RGBA8888, 0);

    // We clear what we draw before
    /* SDL_RenderClear(s); */
    // Set our color for the draw functions
    /* SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF); */
    // show the window
    SDL_RenderPresent(s);

    int generate = 1;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
                quit = 1;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                generate = 1;
            }

            if (generate) {
                int msec;
                clock_t start, diff;
                unsigned char r,g,b;
                uint32_t *pixels;

                /* generate = 0; */
                start = clock();

                SDL_RenderClear(s);
                window_surface = SDL_GetWindowSurface(window);
                SDL_LockSurface(surface);

                pixels = (uint32_t*) surface->pixels;
                r = rand() % 256;
                g = rand() % 256;
                b = rand() % 256;
                for (int y=0; y<windowHeight; ++y) {
                    for (int x=0; x<windowWidth; ++x) {
                        pixels[x + y*windowWidth] = r << 24 | g << 16 | b << 8 | 0xFF;
                        ++r;
                        --g;
                        b ^= b;
                        ++b;
                    }
                }
                SDL_UnlockSurface(surface);

                SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.w = windowWidth;
                rect.h = windowHeight;

                SDL_BlitSurface(surface, &rect, window_surface, &rect);
                SDL_UpdateWindowSurface(window);
                /* SDL_RenderPresent(s); */

                diff = clock() - start;
                msec = diff * 1000 / CLOCKS_PER_SEC;
                printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
            }
        }

    }

    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(s);
    SDL_Quit();
}
