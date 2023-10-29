#include "../header/scene.h"


struct Sphere* createSphere(struct Vec3 center, int radius, struct Color color) {
    struct Sphere* sphere = malloc(sizeof(struct Sphere));
    sphere->center = center;
    sphere->radius = radius;
    sphere->color = color;

    return sphere;
}

void freeSphere(struct Sphere* sphere)
{
    if (sphere != NULL) {
        free(sphere);
    }
}

double intersectRaySphere(struct Vec3 O, struct Vec3 D, struct Sphere* sphere) {
    int radius = sphere->radius;
    struct Vec3 CO = subtractVec3(O, sphere->center);

    double a = dotProduct(D, D);
    double b = 2 * dotProduct(CO, D);
    double c = dotProduct(CO, CO) - radius * radius;

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        return -1;
    } else {
        double t1 = (-b - sqrt(delta)) / (2.0 * a);
        double t2 = (-b + sqrt(delta)) / (2.0 * a);

        if (t1 < 0 && t2 < 0) {
            return -1;
        } else if (t1 < 0) {
            return t2;
        } else if (t2 < 0) {
            return t1;
        } else {
            return t1 < t2 ? t1 : t2;
        }
    }
}

struct Color traceRay(struct Vec3 O, struct Vec3 D, int t_min, int t_max, struct Sphere* spheres, int sphereCount, struct LightArray* LA)
{
    double closest_t = t_max;
    struct Sphere* closest_sphere = NULL;

    for (int i = 0; i < sphereCount; i++) {
        struct Sphere* sphere = &spheres[i];
        double t = intersectRaySphere(O, D, sphere);
        if (t > t_min && t < closest_t) {
            closest_t = t;
            closest_sphere = sphere;
        }
    }

    if (closest_sphere != NULL) {
        struct Vec3 P = addVec3(O, multiplyVec3(D, closest_t));
        struct Vec3 N = subtractVec3(P, closest_sphere->center);
        N = multiplyVec3(N, 1.0 / sqrt(dotProduct(N, N)));
        return multiplyColor(closest_sphere->color, computeLighting(P, N, LA));
    } else {
        return (struct Color) {0, 0, 0};
    }
}

void renderScene(SDL_Renderer* renderer, struct Canvas* canvas, struct Viewport* viewport, struct Sphere* spheres, int sphereCount, struct LightArray* LA) {
    int width = canvas->width;
    int height = canvas->height;
    struct Vec3 camera = {0, 0, 0};

    for (int x = -width / 2; x < width / 2; x++) {
        for (int y = -height / 2; y < height / 2; y++) {
            struct Vec3 P = canvas2viewport(canvas, viewport, x, y);
            struct Vec3 rayDirection = subtractVec3(P, camera);
            struct Color color = traceRay(camera, rayDirection, 1, INFINITY, spheres, sphereCount, LA);
            setPixel(canvas, renderer, x, y, color.r, color.g, color.b);
        }
    }
}

double computeLighting(struct Vec3 P, struct Vec3 N, struct LightArray* LA) {
    double i = 0;
    int na = LA->ambientLightCount;
    int np = LA->pointLightCount;
    int nd = LA->directionalLightCount;

    struct AmbientLight* AL = LA->ambientLights;
    struct PointLight* PL = LA->pointLights;
    struct DirectionalLight* DL = LA->directionalLights;

    for (int j = 0; j < na; j++) {
        struct AmbientLight* al = &AL[j];
        i += al->intensity;
    }

    for (int j = 0; j < np; j++) {
        struct PointLight* pl = &PL[j];
        struct Vec3 L = subtractVec3(pl->position, P);
        i += pl->intensity * dotProduct(L, N) / (dotProduct(L, L) * dotProduct(N, N));
    }

    for (int j = 0; j < nd; j++) {
        struct DirectionalLight* dl = &DL[j];
        i += dl->intensity * dotProduct(dl->direction, N) / (dotProduct(dl->direction, dl->direction) * dotProduct(N, N));
    }

    return i;
}