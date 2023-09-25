#define SDLPIXEL_COMPILE
#include "../sdlpixel.h"
#include <time.h>

int main()
{
    sdlpixel_create("SDLPixel test", 1920, 1080);

    int width = 800;
    int height = 600;
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 8, SDL_PIXELFORMAT_RGBA8888);
    sdlpixel_use_surface(surface);

    int msec;
    clock_t start, diff;
    int quit = 0;
    SDL_Event event;
    SDL_Color color;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
                quit = 1;
            }

            start = clock();
            color = sdlpixel_rgb(rand() % 256, rand() % 256, rand() % 256);
            for (int y=0; y<height; ++y) {
                for (int x=0; x<width; ++x) {
                    sdlpixel_plot(x, y, &color);
                    ++color.r;
                    --color.g;
                    color.b ^= color.b;
                    ++color.b;
                }
            }

            sdlpixel_refresh();
            diff = clock() - start;
            msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
        }
    }

    sdlpixel_quit();
    SDL_FreeSurface(surface);

    return 0;
}
