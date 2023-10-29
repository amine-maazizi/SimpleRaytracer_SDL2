#ifndef SIMPLERAYTRACER_SDL2_SCENE_H
#define SIMPLERAYTRACER_SDL2_SCENE_H

#include <math.h>
#include "canvas.h"
#include "utils.h"

#define INF 1000000

struct Sphere {
    struct Vec3 center;
    int radius;
    struct Color color;
};

struct Sphere* createSphere(struct Vec3, int, struct Color);
void freeSphere(struct Sphere*);

double intersectRaySphere(struct Vec3, struct Vec3, struct Sphere*);
struct Color traceRay(struct Vec3, struct Vec3, int, int,  struct Sphere*, int);
void renderScene(SDL_Renderer*, struct Canvas*, struct Viewport*, struct Sphere*, int);

#endif //SIMPLERAYTRACER_SDL2_SCENE_H
