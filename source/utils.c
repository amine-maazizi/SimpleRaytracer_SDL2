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
