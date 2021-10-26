// Made by Gabriel Lüders
// GRR20190172

#include "display.h"
#include "utils.h"

ALLEGRO_DISPLAY* mainDisplay = NULL;
ALLEGRO_BITMAP* bitmapBuffer = NULL;

void displayInit(){
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  mainDisplay = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  checkAllegroComponent(mainDisplay, "main display");

  bitmapBuffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
  checkAllegroComponent(bitmapBuffer, "bitmap buffer");
}

void displayFree(){
  al_destroy_bitmap(bitmapBuffer);
  al_destroy_display(mainDisplay);
}

void selectBitmapBuffer(){
  al_set_target_bitmap(bitmapBuffer);
}

void flipDisplay(){
  al_set_target_backbuffer(mainDisplay);
  al_draw_scaled_bitmap(
    bitmapBuffer,
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