#ifndef SIMPLERAYTRACER_SDL2_UTILS_H
#define SIMPLERAYTRACER_SDL2_UTILS_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <SDL.h>

struct Vec2 {
    int x;
    int y;
};

void ensureFolderExists(const char*);
void saveImage(SDL_Window*, SDL_Renderer*, const char*);

#endif
