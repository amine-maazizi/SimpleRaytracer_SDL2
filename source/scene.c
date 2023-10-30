#include "../header/scene.h"


struct Sphere* createSphere(struct Vec3 center, int radius, struct Color color, int specular, double reflective) {
    struct Sphere* sphere = malloc(sizeof(struct Sphere));
    sphere->center = center;
    sphere->radius = radius;
    sphere->color = color;
    sphere->specular = specular;
    sphere->reflective = reflective;

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

struct Sphere* closestIntersection(struct Vec3 O, struct Vec3 D, double t_min, double t_max, double* closest_t, struct Sphere* spheres, int sphereCount)
{
    struct Sphere* closest_sphere = NULL;

    for (int i = 0; i < sphereCount; i++) {
        struct Sphere* sphere = &spheres[i];
        double t = intersectRaySphere(O, D, sphere);
        if (t > t_min && t < t_max && t < *closest_t) {
            *closest_t = t;
            closest_sphere = sphere;
        }
    }

    return closest_sphere;
}

struct Color traceRay(struct Vec3 O, struct Vec3 D, double t_min, double t_max, struct Sphere* spheres, int sphereCount, struct LightArray* LA, int recursionDepth)
{
    double closest_t = t_max;
    struct Sphere* closest_sphere = closestIntersection(O, D, t_min, t_max, &closest_t, spheres, sphereCount);


    if (closest_sphere == NULL) {
        return (struct Color) {0, 0, 0};
    }
    struct Vec3 P = addVec3(O, multiplyVec3(D, closest_t));
    struct Vec3 N = subtractVec3(P, closest_sphere->center);
    N = multiplyVec3(N, 1.0 / magnitude(N));
    struct Color local_color = multiplyColor(closest_sphere->color, computeLighting(P, N, multiplyVec3(D, -1), closest_sphere->specular, t_max, LA, spheres, sphereCount));

    double r =closest_sphere->reflective;
    if (recursionDepth <= 0 || r <= 0) {
        return local_color;
    }

    struct Vec3 R = reflectRay(multiplyVec3(D, -1), N);
    struct Color reflectedColor = traceRay(P, R, 0.001, INFINITY, spheres, sphereCount, LA, recursionDepth - 1);

    return addColor(multiplyColor(local_color, (1-r)), multiplyColor(reflectedColor, r));
}

void renderScene(SDL_Renderer* renderer, struct Canvas* canvas, struct Viewport* viewport, struct Sphere* spheres, int sphereCount, struct LightArray* LA) {
    int width = canvas->width;
    int height = canvas->height;
    struct Vec3 camera = {0.0, 0.0, 0.0};
    struct Vec3 rotationAxis = {0, 1, 0};
    double theta = 0.0;

    for (int x = -width / 2; x < width / 2; x++) {
        for (int y = -height / 2; y < height / 2; y++) {
            struct Vec3 P = canvas2viewport(canvas, viewport, x, y);
            P = rotateVec3(P, rotationAxis, theta);
            struct Vec3 rayDirection = subtractVec3(P, camera);
            struct Color color = traceRay(camera, rayDirection, 1, INFINITY, spheres, sphereCount, LA, 2);
            setPixel(canvas, renderer, x, y, color.r, color.g, color.b);
        }
    }
}

double computeLighting(struct Vec3 P, struct Vec3 N, struct Vec3 D, int sphereSpecular, double t_max, struct LightArray* LA, struct Sphere* spheres, int sphereCount) {
    double i = 0;
    int na = LA->ambientLightCount;
    int np = LA->pointLightCount;
    int nd = LA->directionalLightCount;

    struct AmbientLight* AL = LA->ambientLights;
    struct PointLight* PL = LA->pointLights;
    struct DirectionalLight* DL = LA->directionalLights;

    // Ambient
    for (int j = 0; j < na; j++) {
        struct AmbientLight* al = &AL[j];
        i += al->intensity;
    }

    // Point
    for (int j = 0; j < np; j++) {
        struct PointLight* pl = &PL[j];
        struct Vec3 L = subtractVec3(pl->position, P);

        double shadow_t = t_max;
        struct Shpere* shadow_sphere = closestIntersection(P, L, 0.001, t_max, &shadow_t ,spheres, sphereCount);

        if (shadow_sphere != NULL) {
            continue;
        }

        // Diffuse
        double LDotN = dotProduct(L, N);
        if (LDotN > 0) {
            i += pl->intensity * LDotN / (magnitude(L) * magnitude(N));
        }

        // Specular
        if (sphereSpecular != -1) {
            struct Vec3 R = subtractVec3(multiplyVec3(N, 2 * dotProduct(N, L)), L);
            double RDotD = dotProduct(R, D);
            if (RDotD > 0) {
                i += pl->intensity * pow(RDotD / (magnitude(R) * magnitude(D)), sphereSpecular);
            }
        }
    }

    // Directional
    for (int j = 0; j < nd; j++) {
        struct DirectionalLight* dl = &DL[j];
        struct Vec3 L = dl->direction;

        double shadow_t = t_max;
        struct Shpere* shadow_sphere = closestIntersection(P, L, 0.001, t_max, &shadow_t ,spheres, sphereCount);

        if (shadow_sphere != NULL) {
            continue;
        }

        // Diffuse
        double LDotN = dotProduct(L, N);
        if (LDotN > 0) {
            i += dl->intensity * LDotN /
                 (magnitude(L) * magnitude(N));
        }

        if (sphereSpecular != -1) {
            struct Vec3 R = subtractVec3(multiplyVec3(N, 2 * dotProduct(N, L)), L);
            double RDotD = dotProduct(R, D);
            if (RDotD > 0) {
                i += dl->intensity * pow(RDotD / (magnitude(R) * magnitude(D)), sphereSpecular);
            }
        }
    }

    return i;
}

struct Vec3 reflectRay(struct Vec3 I, struct Vec3 N) {
    return subtractVec3(multiplyVec3(N, 2 * dotProduct(N, I)), I);
}