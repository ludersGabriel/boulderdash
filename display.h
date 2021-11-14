// Made by Gabriel Lüders
// GRR 20190172

#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro5.h>

#define BUFFER_WIDTH 640
#define BUFFER_HEIGHT 360

#define DISPLAY_SCALE 2.5
#define DISPLAY_WIDTH (BUFFER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * DISPLAY_SCALE)

typedef struct DISPLAY{
  ALLEGRO_DISPLAY* mainDisplay;
  ALLEGRO_BITMAP* bitmapBuffer;
}Display;


void displayInit();

Display* displayConstructor();

void displayDestructor(Display* display);

void selectBitmapBuffer(Display* display);

void flipDisplay(Display* display);

#endif