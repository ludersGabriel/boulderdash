// Made by Gabriel Lüders
// GRR20190172 

#include "sprite.h"
#include "utils.h"
#include <allegro5/allegro_image.h>

// responsible for loading a sprite sheet
ALLEGRO_BITMAP* loadSheet(const char* path){
  ALLEGRO_BITMAP* sheet = al_load_bitmap(path);
  checkAllegroComponent(sheet, path);

  return sheet;
}

// responsible for destroying a sprite sheet
void sheetDestructor(ALLEGRO_BITMAP* sheet){
  al_destroy_bitmap(sheet);
}

// responsible for loading a sprite
ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height){
  ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, width, height);
  checkAllegroComponent(sprite, "a sprite");

  return sprite;
}

// initializes allegro sprite system
void spriteSystemInit(){
  checkAllegroComponent(al_init_image_addon(), "image addon");
}

// creates and initializes a sprite object, returning it
Sprite* spriteConstructor(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height, const char* desc){
  Sprite* sprite = mallocSpace(sizeof(Sprite), desc);
  sprite->bitmap = loadSprite(sheet, x, y, width, height);
  sprite->height = height;
  sprite->width = width;

  return sprite;
}

// destroys a given sprite
void spriteDestructor(Sprite* sprite){
  if(!sprite) return;
  
  al_destroy_bitmap(sprite->bitmap);
  free(sprite);
}
