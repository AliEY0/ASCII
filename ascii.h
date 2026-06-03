#pragma once
#include "bmp.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>

static const char characters[13] = {' ', '.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@'};

void generate_ascii(struct BMPImage *image);
