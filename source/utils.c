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

double magnitude(struct Vec3 v)
{
    return sqrt(dotProduct(v, v));
}

struct Vec3 rotateVec3(struct Vec3 vec, struct Vec3 axis, double theta) {
    double x = vec.x;
    double y = vec.y;
    double z = vec.z;

    double u = axis.x;
    double v = axis.y;
    double w = axis.z;

    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    double dot = x * u + y * v + z * w;

    double xPrime = u * dot * (1 - cosTheta) + x * cosTheta + (-w * y + v * z) * sinTheta;
    double yPrime = v * dot * (1 - cosTheta) + y * cosTheta + (w * x - u * z) * sinTheta;
    double zPrime = w * dot * (1 - cosTheta) + z * cosTheta + (-v * x + u * y) * sinTheta;

    return (struct Vec3) {xPrime, yPrime, zPrime};
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
    return  (struct Color) {(c.r * k > 255) ? 255 : c.r * k,
                            (c.g * k > 255) ? 255 : c.g * k,
                            (c.b * k > 255) ? 255 : c.b * k};
}

struct Color addColor(struct Color c1, struct Color c2)
{
    return (struct Color) {(c1.r + c2.r > 255) ? 255 : c1.r + c2.r,
                           (c1.g + c2.g > 255) ? 255 : c1.g + c2.g,
                           (c1.b + c2.b > 255) ? 255 : c1.b + c2.b};
}