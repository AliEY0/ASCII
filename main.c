#include <stdio.h>
#include "bmp.h"
#include "color.h"
#include "ascii.h"
void test(){
    struct BMPImage *image = read_bmp_image("out-001.bmp");
     if (!image) return;  
    init_rgb_colorgrid_bmp(image);
    //render_bmp_image_sdl2(image);
    generate_ascii(image);
    free_bmp_image(image);
}

int main() {
    test();

    
    //test_endian();
    return 0;
}


/*

Big Endian(16bit): 424d
Little Endian(16bit): 4d42
Big Endian(32bit): 78563412
Big Endian(32bit): 78563412
Big Endian(32bit): 3072
Bits per pixel 24
Size of data 786432
Magic number: 4d42
Width image: 512
Height image: 512

---------------------------

Big Endian(16bit): 424d
Little Endian(16bit): 4d42
Big Endian(32bit): 78563412
Big Endian(32bit): 78563412
Big Endian(32bit): 0
Bits per pixel 24
Size of data 0
Magic number: 4d42
Width image: 256
Height image: 256

*/
