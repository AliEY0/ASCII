#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "color.h"


void init_rgb_colorgrid_bmp(struct BMPImage *image){
    image->colorgrid = malloc(sizeof(struct RGBPixelInfo*)  * image->header.height_px);
    int rowsize = (image->header.bits_per_pixel * image->header.width_px + 31) / 32 * 4; //https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
    image->rowsize = rowsize;
    for(int32_t i = 0; i < image->header.height_px; ++i){
        image->colorgrid[i] = malloc(sizeof(struct RGBPixelInfo) * image->header.width_px);
        for(int j = 0; j < image->header.width_px; ++j){
            int val = i * image->rowsize + j * 3;
            image->colorgrid[i][j].b = image->data[val];
            image->colorgrid[i][j].g = image->data[val + 1];
            image->colorgrid[i][j].r = image->data[val + 2];
        }
    }
}

void render_bmp_image_sdl2(struct BMPImage *image){
    SDL_Init(SDL_INIT_VIDEO);
    struct SDL_Window* window = SDL_CreateWindow("Render BMP Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image->header.width_px, image->header.height_px, 0);
    struct SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    int rowsize = (image->header.bits_per_pixel * image->header.width_px + 31) / 32 * 4; //https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
    for(int32_t i = 0; i < image->header.height_px; ++i){
        for(int j = 0; j < image->header.width_px; ++j){
            int val = i * rowsize + j * 3;
            unsigned char r = image->data[val];
            unsigned char g = image->data[val + 1];
            unsigned char b = image->data[val + 2];
            struct SDL_Rect rect = {j, (image->header.height_px-1)-i, 1, 1}; //Scan lines are stored bottom to top instead of top to bottom.
            SDL_SetRenderDrawColor(renderer, image->colorgrid[i][j].r , image->colorgrid[i][j].g ,image->colorgrid[i][j].b, 255); //RGB values are stored backwards i.e. BGR.
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Event event;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void free_bmp_image(struct BMPImage *image){
    free(image->data);
    for(int i = 0; i < image->header.height_px; ++i){
        free(image->colorgrid[i]);
    }
    
    free(image->colorgrid);
    free(image);
}

void print_data(struct BMPImage *image){
    printf("Bits per pixel %d\n", image->header.bits_per_pixel);
    printf("Size of data %d\n", image->header.image_size_bytes);    
    printf("Magic number: %x\n", image->header.type);
    printf("Width image: %d\n", image->header.width_px);
    printf("Height image: %d\n", image->header.height_px);
}
void write_colorgrid_to_data(struct BMPImage *image) {
    for(int y = 0; y < image->header.height_px; ++y) {
        for(int x = 0; x < image->header.width_px; ++x) {

            int val = y * image->rowsize + x * 3;

            image->data[val]     = image->colorgrid[y][x].b;
            image->data[val + 1] = image->colorgrid[y][x].g;
            image->data[val + 2] = image->colorgrid[y][x].r;
        }
    }
}

struct BMPImage* read_bmp_image(char *path){
    FILE *fptr = fopen(path, "r");
    struct BMPImage *image = malloc(sizeof(struct BMPImage));   
    fread(&image->header, sizeof(struct BMPHeader), 1, fptr);
    image->data = malloc(image->header.image_size_bytes);
    fseek(fptr, image->header.offset,SEEK_SET);
    fread(image->data, 1, image->header.image_size_bytes, fptr);
    fclose(fptr);
    return image;
}
