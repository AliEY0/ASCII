#include "bmp.h"

void print_data(struct BMPImage *image){
    printf("Bits per pixel %d\n", image->header.bits_per_pixel);
    printf("Size of data %d\n", image->header.image_size_bytes);    
    printf("Magic number: %x\n", image->header.type);
    printf("Width image: %d\n", image->header.width_px);
    printf("Height image: %d\n", image->header.height_px);
}

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

void free_bmp_image(struct BMPImage *image){
    free(image->data);
    for(int i = 0; i < image->header.height_px; ++i){
        free(image->colorgrid[i]);
    }
    free(image->colorgrid);
    free(image);
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
