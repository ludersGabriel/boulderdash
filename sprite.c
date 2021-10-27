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

ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height){
  ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, width, height);
  checkAllegroComponent(sprite, "a sprite");

  return sprite;
}

void spriteSystemInit(){
  checkAllegroComponent(al_init_image_addon(), "image addon");
}
