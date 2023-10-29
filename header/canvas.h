#ifndef SIMPLERAYTRACER_SDL2_CANVAS_H
#define SIMPLERAYTRACER_SDL2_CANVAS_H

#include <stdlib.h>
#include <SDL.h>
#include "utils.h"

struct Canvas {
        int width;
        int height;
        int (*canvas)[3]; // Pointer to a dynamic 2D array
};

struct Viewport {
        int width;
        int height;
        int distance;
};

struct Canvas* createCanvas(int, int);
void freeCanvas(struct Canvas*);
void setPixel(struct Canvas*, SDL_Renderer*, int, int, int, int, int);

struct Viewport* createViewport(int, int, int);
void freeViewport(struct Viewport*);
struct Vec3 canvas2viewport(struct Canvas*, struct Viewport*, int, int);


#endif
