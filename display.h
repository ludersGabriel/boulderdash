// Made by Gabriel Lüders
// GRR 20190172

#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro5.h>

#define BUFFER_WIDTH 320
#define BUFFER_HEIGHT 180

#define DISPLAY_SCALE 2
#define DISPLAY_WIDTH (BUFFER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * DISPLAY_SCALE)

extern ALLEGRO_DISPLAY* mainDisplay;
extern ALLEGRO_BITMAP* bitmapBuffer;

void displayInit();

void displayFree();

void selectBitmapBuffer();

void flipDisplay();

#endif