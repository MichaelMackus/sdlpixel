#include <time.h>
#include <SDL2/SDL.h>
#include <ctype.h>

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

    const int pointLocationx = windowWidth/2;
    const int pointLocationy = windowHeight/2;

    int quit = 0;
    SDL_Event event;

    //drawing particles
    //setting up objects
    //repeated over and over again

    int msec, i;
    clock_t start, diff;

    /* SDL_HasWindowSurface(); */
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    SDL_Surface *surface;

    surface = SDL_ConvertSurfaceFormat(window_surface, SDL_PIXELFORMAT_RGBA8888, 0);

    // We clear what we draw before
    SDL_RenderClear(s);
    // Set our color for the draw functions
    SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);

    /* i = 100000; */
    start = clock();
    SDL_LockSurface(surface);
    unsigned int *color;
    unsigned char r,g,b;
    uint32_t *pixels;
    pixels = (uint32_t*) surface->pixels;
    r = 255;
    g = 127;
    b = 0;
    i = 0;
    for (int y=0; y<windowHeight; ++y) {
        for (int x=0; x<windowWidth; ++x) {
            pixels[i] = r << 24 | g << 16 | b << 8 | 0xFF;
            ++r;
            --g;
            ++b;
            ++i;
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

    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

    // Now we can draw our point
    /* SDL_RenderDrawPoint(s, pointLocationx, pointLocationy); */
    // Set the color to what was before
    /* SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF); */
    // .. you could do some other drawing here
    // And now we present everything we draw after the clear.
    /* SDL_RenderPresent(s); */

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

    }

    SDL_DestroyWindow(window);
    // We have to destroy the renderer, same as with the window.
    SDL_DestroyRenderer(s);
    SDL_Quit();
}
