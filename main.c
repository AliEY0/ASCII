#include <stdio.h>
#include "bmp.h"
#include "color.h"
#include "ascii.h"

static inline void transform_bmp_image_to_ascii(){
    struct BMPImage *image = read_bmp_image("output.bmp");
     if (!image) return;  
    init_rgb_colorgrid_bmp(image);
    generate_ascii(image);
    print_data(image);
    free_bmp_image(image);
}

int main() {
    transform_bmp_image_to_ascii();
    return 0;
}

