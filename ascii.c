#pragma once
#include <stdio.h>
#include "ascii.h"
#include <stdlib.h>

void generate_ascii(struct BMPImage *image){
    char **map = (char*)malloc(sizeof(char*) * image->header.height_px);
    

    for(int i = 0; i < image->header.height_px; ++i)
        map[i] = malloc(image->header.width_px);
   
    for(int i = image->header.height_px - 1; i >= 0; i--){
        for(int j = 0; j < image->header.width_px; ++j){
            float gray = 0.299 * image->colorgrid[i][j].r + 0.587 * image->colorgrid[i][j].g + 0.114 * image->colorgrid[i][j].b ;
            gray *= 13;
            int val = (int)(gray / 255);
            if(val == 13) --val;
            map[i][j] = characters[val];

            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < image->header.height_px; ++i)
        free(map[i]);
    free(map);
    
}
