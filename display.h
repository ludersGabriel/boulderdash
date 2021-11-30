// Made by Gabriel Lüders
// GRR 20190172

#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro5.h>

// actual size of the game grid
#define BUFFER_WIDTH 640
#define BUFFER_HEIGHT 368

// size displayed to the player
#define DISPLAY_SCALE 2.5
#define DISPLAY_WIDTH (BUFFER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * DISPLAY_SCALE)

// struct that represents a display object
typedef struct DISPLAY{
  ALLEGRO_DISPLAY* mainDisplay;
  ALLEGRO_BITMAP* bitmapBuffer;
  int width;
  int height;
  int bufferWidth;
  int bufferHeight;
}Display;

// responsible for initializing the allegro display system
void displayInit();

// creates and initializes a display object, returning it
Display* displayConstructor();

// destroys a given display object
void displayDestructor(Display* display);

// selects the actual game grid
void selectBitmapBuffer(Display* display);

// flips the drawings to the display
void flipDisplay(Display* display);

#endif