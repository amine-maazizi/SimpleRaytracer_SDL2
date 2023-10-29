#ifndef SIMPLERAYTRACER_SDL2_LIGHT_H
#define SIMPLERAYTRACER_SDL2_LIGHT_H

#include "utils.h"

enum LightType {
    AMBIENT,
    POINT,
    DIRECTIONAL
};

struct AmbientLight {
    enum LightType type;
    double intensity;
};

struct PointLight {
    enum LightType type;
    double intensity;
    struct Vec3 position;
};

struct DirectionalLight {
    enum LightType type;
    double intensity;
    struct Vec3 direction;
};

struct LightArray {
    struct AmbientLight* ambientLights;
    int ambientLightCount;
    struct PointLight* pointLights;
    int pointLightCount;
    struct DirectionalLight* directionalLights;
    int directionalLightCount;
};

struct AmbientLight* createAmbientLight(double);
void freeAmbientLight(struct AmbientLight*);

struct PointLight* createPointLight(double, struct Vec3);
void freePointLight(struct PointLight*);

struct DirectionalLight* createDirectionalLight(double, struct Vec3);
void freeDirectionalLight(struct DirectionalLight*);

struct LightArray* createLightArray(struct AmbientLight*, int, struct PointLight*, int, struct DirectionalLight*, int);
void freeLightArray(struct LightArray*);

#endif
