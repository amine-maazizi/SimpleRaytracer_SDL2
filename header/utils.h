#ifndef SIMPLERAYTRACER_SDL2_UTILS_H
#define SIMPLERAYTRACER_SDL2_UTILS_H

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <SDL.h>
#include <math.h>

struct Vec3 {
    double x;
    double y;
    double z;
};

struct Color {
    int r;
    int g;
    int b;
};

void ensureFolderExists(const char*);
void saveImage(SDL_Window*, SDL_Renderer*, const char*);
double dotProduct(struct Vec3, struct Vec3);
double magnitude(struct Vec3);
struct Vec3 subtractVec3(struct Vec3, struct Vec3);
struct Vec3 addVec3(struct Vec3, struct Vec3);
struct Vec3 multiplyVec3(struct Vec3, double);
struct Color multiplyColor(struct Color, double);

#endif
