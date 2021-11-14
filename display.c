// Made by Gabriel Lüders
// GRR20190172

#include "display.h"
#include "utils.h"

void displayInit(){
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
}

Display* displayConstructor(){
  Display* display = mallocSpace(sizeof(Display), "display pointer null");
  
  display->mainDisplay = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  checkAllegroComponent(display->mainDisplay, "main display");

  display->bitmapBuffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
  checkAllegroComponent(display->bitmapBuffer, "bitmap buffer");

  return display;
}

void displayDestructor(Display* display){
  if(!display) return;

  al_destroy_bitmap(display->bitmapBuffer);
  al_destroy_display(display->mainDisplay);

  free(display);
}

void selectBitmapBuffer(Display* display){
  al_set_target_bitmap(display->bitmapBuffer);
}

void flipDisplay(Display* display){
  al_set_target_backbuffer(display->mainDisplay);
  al_draw_scaled_bitmap(
    display->bitmapBuffer,
    0, 
    0,
    BUFFER_WIDTH,
    BUFFER_HEIGHT,
    0, 
    0,
    DISPLAY_WIDTH,
    DISPLAY_HEIGHT,
    0
  );

  al_flip_display();
}