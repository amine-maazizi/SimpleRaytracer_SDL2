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
    double reflective; // 0 for non-reflective, 1 for fully reflective.
};

struct Sphere* createSphere(struct Vec3, int, struct Color, int, double);
void freeSphere(struct Sphere*);

double intersectRaySphere(struct Vec3, struct Vec3, struct Sphere*);
struct Sphere* closestIntersection(struct Vec3, struct Vec3, double, double, double*, struct Sphere*, int);
struct Color traceRay(struct Vec3, struct Vec3, double, double,  struct Sphere*, int, struct LightArray*, int);
void renderScene(SDL_Renderer*, struct Canvas*, struct Viewport*, struct Sphere*, int, struct LightArray*);
double computeLighting(struct Vec3, struct Vec3, struct Vec3, int, double, struct LightArray*, struct Sphere*, int);
struct Vec3 reflectRay(struct Vec3, struct Vec3);

#endif //SIMPLERAYTRACER_SDL2_SCENE_H
