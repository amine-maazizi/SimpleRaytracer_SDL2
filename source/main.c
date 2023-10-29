#include <stdio.h>
#include <SDL.h>

#include "../header/canvas.h"
#include "../header/scene.h"


#define WIDTH  500
#define HEIGHT  500

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

    struct Viewport* viewport = createViewport(1, 1, 1);
    if (viewport == NULL) {
        fprintf(stderr, "createViewport Error: %s\n", SDL_GetError());
        freeCanvas(canvas);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    struct Sphere* s1 = createSphere((struct Vec3){.x = 0, .y = -1, .z = 3}, 1, (struct Color){.r = 255, .g = 0, .b = 0});
    struct Sphere* s2 = createSphere((struct Vec3){.x = 2, .y = 0, .z = 4}, 1, (struct Color){.r = 0, .g = 255, .b = 0});
    struct Sphere* s3 = createSphere((struct Vec3){.x = -2, .y = 0, .z = 4}, 1, (struct Color){.r = 0, .g = 0, .b = 255});
    struct Sphere* s4 = createSphere((struct Vec3){.x = 0, .y = -5001, .z = 0}, 5000, (struct Color){.r = 255, .g = 255, .b = 0});
    struct Sphere s[4] = {*s1, *s2, *s3, *s4};

    struct AmbientLight* AL = createAmbientLight(0.2);
    struct PointLight* PL = createPointLight(0.6, (struct Vec3){.x = 2, .y = 1, .z = 0});
    struct DirectionalLight* DL = createDirectionalLight(0.2, (struct Vec3){.x = 1, .y = 4, .z = 4});

    struct LightArray* LA = createLightArray(AL, 1, PL, 1, DL, 1);

    renderScene(renderer, canvas, viewport, s, 4, LA);

    SDL_RenderPresent(renderer);

    // Save the image to disk
    ensureFolderExists("../output");
    saveImage(window, renderer, "../output/scene.bmp");

    // Cleanup and exit
    freeCanvas(canvas);
    freeViewport(viewport);
    for (int i = 0; i < 3; i++) {
        freeSphere(&s[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
