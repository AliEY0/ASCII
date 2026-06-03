all:
	gcc -g -Wall -Wextra main.c bmp.c ascii.c -o main `sdl2-config --cflags --libs` -lSDL2_ttf
	./main
	rm main
