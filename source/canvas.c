#include "../header/canvas.h"

struct Canvas* createCanvas(int width, int height)
{
    struct Canvas* canvas = malloc(sizeof(struct Canvas));

    if (canvas == NULL) {
        perror("CANVAS::Memory allocation failed for struct Canvas");
        return NULL;
    }

    canvas->width = width;
    canvas->height = height;
    canvas->canvas = (int (*)[3])malloc(width * height * sizeof(int[3]));

    if (canvas->canvas == NULL) {
        perror("CANVAS::Memory allocation failed for canvas->canvas");
        free(canvas); // Clean up the previously allocated memory
        return NULL;
    }

    return canvas;
}

void freeCanvas(struct Canvas* canvas) {
    if (canvas != NULL) {
        if (canvas->canvas != NULL) {
            free(canvas->canvas);
        }
        free(canvas);
    }
}

void setPixel(struct Canvas* canvas, SDL_Renderer* renderer, int x, int y, int r, int g, int b) {
    x = x + canvas->width / 2;
    y = canvas->height / 2 - y - 1;
    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

struct Viewport* createViewport(int width, int height, int distance) {
    struct Viewport* viewport = malloc(sizeof(struct Viewport));

    if (viewport == NULL) {
        perror("CANVAS::Memory allocation failed for struct Viewport");
        return NULL;
    }

    viewport->width = width;
    viewport->height = height;
    viewport->distance = distance;

    return viewport;
}

void freeViewport(struct Viewport* viewport) {
    if (viewport != NULL) {
        free(viewport);
    }
}

struct Vec3 canvas2viewport(struct Canvas* canvas, struct Viewport* viewport, int x, int y)
{
    return (struct Vec3){
        .x = (double)x * (double)viewport->width / (double)canvas->width,
        .y = (double)y * (double)viewport->height / (double)canvas->height,
        .z = viewport->distance,
    };
}