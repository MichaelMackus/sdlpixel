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
    unsigned char r,g,b;
    uint32_t *pixels;
    int pitch = sdlpixel_get_pitch();

    printf("Pitch: %d\n", pitch);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            start = clock();
            pixels = sdlpixel_get_rgba_pixels();

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

            sdlpixel_refresh();

            diff = clock() - start;
            msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
        }
    }

    sdlpixel_quit();

    return 0;
}
