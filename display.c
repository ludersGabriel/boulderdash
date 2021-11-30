// Made by Gabriel Lüders
// GRR20190172

#include "display.h"
#include "utils.h"

// responsible for initializing the allegro display system
void displayInit(){
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
}

// creates and initializes a display object, returning it
Display* displayConstructor(){
  Display* display = mallocSpace(sizeof(Display), "display pointer null");
  
  display->mainDisplay = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  checkAllegroComponent(display->mainDisplay, "main display");

  display->bitmapBuffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
  checkAllegroComponent(display->bitmapBuffer, "bitmap buffer");

  display->height = DISPLAY_HEIGHT;
  display->width = DISPLAY_WIDTH;
  display->bufferHeight = BUFFER_HEIGHT;
  display->bufferWidth = BUFFER_WIDTH;

  return display;
}

// destroys a given display object
void displayDestructor(Display* display){
  if(!display) return;

  al_destroy_bitmap(display->bitmapBuffer);
  al_destroy_display(display->mainDisplay);

  free(display);
}

// selects the actual game grid
void selectBitmapBuffer(Display* display){
  al_set_target_bitmap(display->bitmapBuffer);
}

// flips the drawings to the display
void flipDisplay(Display* display){
  al_set_target_backbuffer(display->mainDisplay);
  al_draw_scaled_bitmap(
    display->bitmapBuffer,
    0, 
    0,
    display->bufferWidth,
    display->bufferHeight,
    0, 
    0,
    display->width,
    display->height,
    0
  );

  al_flip_display();
}