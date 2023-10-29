#include "../header/utils.h"

void ensureFolderExists(const char* folderPath) {
    struct stat st = {0};
    if (stat(folderPath, &st) == -1) {
        if (mkdir(folderPath) != 0) {
            perror("Error creating folder");
        } else {
            printf("Folder created: %s\n", folderPath);
        }
    } else {
        printf("Folder already exists: %s\n", folderPath);
    }
}

void saveImage(SDL_Window* window, SDL_Renderer* renderer, const char* filename) {
    int WIDTH, HEIGHT;
    SDL_GetWindowSize(window, &WIDTH, &HEIGHT);

    SDL_Surface* surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, filename);
    SDL_FreeSurface(surface);
}

double dotProduct(struct Vec3 v1, struct Vec3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

struct Vec3 subtractVec3(struct Vec3 v1, struct Vec3 v2)
{
    return (struct Vec3) {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

struct Vec3 addVec3(struct Vec3 v1, struct Vec3 v2) {
    return (struct Vec3) {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

struct Vec3 multiplyVec3(struct Vec3 v1, double k) {
    return (struct Vec3) {v1.x * k, v1.y * k, v1.z * k};
}

struct Color multiplyColor(struct Color c, double k)
{
    return  (struct Color) {c.r * k, c.g * k, c.b * k};
}