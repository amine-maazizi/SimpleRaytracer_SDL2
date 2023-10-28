#include <stdio.h>
#include <SDL.h>

#include "../header/canvas.h"
#include "../header/utils.h"

#define WIDTH  800
#define HEIGHT  600

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Image Save Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    struct Canvas* canvas = createCanvas(WIDTH, HEIGHT);
    if (canvas == NULL) {
        fprintf(stderr, "createCanvas Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    for (int y = 0; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            setPixel(canvas, renderer, x, y, 255, 0, 0);
        }
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Save the image to disk
    ensureFolderExists("../output");
    saveImage(window, renderer, "../output/scene.bmp");

    // Cleanup and exit
    freeCanvas(canvas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
