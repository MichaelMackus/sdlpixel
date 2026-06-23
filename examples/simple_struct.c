#define SDLPIXEL_COMPILE
#include "../sdlpixel.h"
#include <time.h>

int main()
{
    int width = 1920;
    int height = 1080;
    sdlpixel_create("SDLPixel stripes", width, height);

    int quit = 0;
    SDL_Event event;
    int msec;
    clock_t start, diff;
    SDL_Color color;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            start = clock();

            if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
                quit = 1;
            }

            color.r = rand() % 256;
            color.g = rand() % 256;
            color.b = rand() % 256;
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

    return 0;
}
