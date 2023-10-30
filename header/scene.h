#ifndef SIMPLERAYTRACER_SDL2_SCENE_H
#define SIMPLERAYTRACER_SDL2_SCENE_H

#include "canvas.h"
#include "utils.h"
#include "light.h"

#define INF 2147483647

struct Sphere {
    struct Vec3 center;
    int radius;
    struct Color color;
    int specular; // -1 for non-specular, higher values for more specular.
};

struct Sphere* createSphere(struct Vec3, int, struct Color, int);
void freeSphere(struct Sphere*);

double intersectRaySphere(struct Vec3, struct Vec3, struct Sphere*);
struct Color traceRay(struct Vec3, struct Vec3, int, int,  struct Sphere*, int, struct LightArray*);
void renderScene(SDL_Renderer*, struct Canvas*, struct Viewport*, struct Sphere*, int, struct LightArray*);
double computeLighting(struct Vec3, struct Vec3, struct Vec3, int, struct LightArray*);

#endif //SIMPLERAYTRACER_SDL2_SCENE_H
