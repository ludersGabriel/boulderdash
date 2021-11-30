// Made by Gabriel Lüders
// GRR20190172 

#ifndef SPRITE_H
#define SPRITE_H

#define TILE_SIZE 16

#include <allegro5/allegro5.h>

// struct that define a sprite object
typedef struct SPRITE{
  ALLEGRO_BITMAP* bitmap;
  int width;
  int height; 
}Sprite;

// creates and initializes a sprite object, returning it
Sprite* spriteConstructor(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height, const char* desc);

// destroys a given sprite
void spriteDestructor(Sprite* sprite);

// responsible for loading a sprite sheet
ALLEGRO_BITMAP* loadSheet(const char* path);

// responsible for destroying a sprite sheet
void sheetDestructor(ALLEGRO_BITMAP* sheet);

// responsible for loading a sprite
ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height);

// initializes allegro sprite system
void spriteSystemInit();

#endif