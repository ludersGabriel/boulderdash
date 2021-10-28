// Made by Gabriel Lüders
// GRR20190172 

#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro5.h>

typedef struct SPRITE{
  ALLEGRO_BITMAP* bitmap;
  int width;
  int height; 
}Sprite;

Sprite* spriteConstructor(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height, const char* desc);

void spriteDestructor(Sprite* sprite);

ALLEGRO_BITMAP* loadSheet(const char* path);

void sheetDestructor(ALLEGRO_BITMAP* sheet);

ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height);

void spriteSystemInit();

#endif