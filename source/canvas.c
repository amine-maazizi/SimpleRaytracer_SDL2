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
    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return;
    }

    int index = y * canvas->width + x;

    canvas->canvas[index][0] = r;
    canvas->canvas[index][1] = g;
    canvas->canvas[index][2] = b;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

struct Vec2 canvas2viewport(struct Canvas* canvas, struct Viewport* viewport, int x, int y)
{
    return (sturct Vec2){
        .x = x * viewport->width / canvas->width,
        .y = y * viewport->height / canvas->height
    }
}