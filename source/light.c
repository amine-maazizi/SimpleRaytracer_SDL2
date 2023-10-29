#include "../header/light.h"

struct AmbientLight* createAmbientLight(double intensity) {
    struct AmbientLight* ambientLight = malloc(sizeof(struct AmbientLight));

    if (ambientLight == NULL) {
        perror("LIGHT::Memory allocation failed for struct AmbientLight");
        return NULL;
    }

    ambientLight->type = AMBIENT;
    ambientLight->intensity = intensity;

    return ambientLight;
}

void freeAmbientLight(struct AmbientLight* ambientLight) {
    if (ambientLight != NULL) {
        free(ambientLight);
    }
}

struct PointLight* createPointLight(double intensity, struct Vec3 position) {
    struct PointLight* pointLight = malloc(sizeof(struct PointLight));

    if (pointLight == NULL) {
        perror("LIGHT::Memory allocation failed for struct PointLight");
        return NULL;
    }

    pointLight->type = POINT;
    pointLight->intensity = intensity;
    pointLight->position = position;

    return pointLight;
}

void freePointLight(struct PointLight* pointLight) {
    if (pointLight != NULL) {
        free(pointLight);
    }
}

struct DirectionalLight* createDirectionalLight(double intensity, struct Vec3 direction) {
    struct DirectionalLight* directionalLight = malloc(sizeof(struct DirectionalLight));

    if (directionalLight == NULL) {
        perror("LIGHT::Memory allocation failed for struct DirectionalLight");
        return NULL;
    }

    directionalLight->type = DIRECTIONAL;
    directionalLight->intensity = intensity;
    directionalLight->direction = direction;

    return directionalLight;
}

void freeDirectionalLight(struct DirectionalLight* directionalLight) {
    if (directionalLight != NULL) {
        free(directionalLight);
    }
}

struct LightArray* createLightArray(struct AmbientLight* AL, int na, struct PointLight* PL, int np, struct DirectionalLight* DL, int nd)
{
    struct LightArray* lightArray = malloc(sizeof(struct LightArray));

    if (lightArray == NULL) {
        perror("LIGHT::Memory allocation failed for struct LightArray");
        return NULL;
    }

    lightArray->ambientLights = AL;
    lightArray->ambientLightCount = na;
    lightArray->pointLights = PL;
    lightArray->pointLightCount = np;
    lightArray->directionalLights = DL;
    lightArray->directionalLightCount = nd;

    return lightArray;
}

void freeLightArray(struct LightArray* lightArray) {
    if (lightArray != NULL) {
        free(lightArray);
    }
}