// Made by Gabriel Lüders
// GRR20190172 

#include "sprite.h"
#include "utils.h"
#include <allegro5/allegro_image.h>

ALLEGRO_BITMAP* loadSheet(const char* path){
  ALLEGRO_BITMAP* sheet = al_load_bitmap(path);
  checkAllegroComponent(sheet, path);

  return sheet;
}

void sheetDestructor(ALLEGRO_BITMAP* sheet){
  al_destroy_bitmap(sheet);
}

ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height){
  ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, width, height);
  checkAllegroComponent(sprite, "a sprite");

  return sprite;
}

void spriteSystemInit(){
  checkAllegroComponent(al_init_image_addon(), "image addon");
}

Sprite* spriteConstructor(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height, const char* desc){
  Sprite* sprite = mallocSpace(sizeof(Sprite), desc);
  sprite->bitmap = loadSprite(sheet, x, y, width, height);
  sprite->height = height;
  sprite->width = width;

  return sprite;
}

void spriteDestructor(Sprite* sprite){
  if(!sprite) return;
  
  al_destroy_bitmap(sprite->bitmap);
  free(sprite);
}
