// Made by Gabriel Lüders
// GRR20190172 

#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro5.h>

ALLEGRO_BITMAP* loadSheet(const char* path);

ALLEGRO_BITMAP* loadSprite(ALLEGRO_BITMAP* sheet, int x, int y, int width, int height);

void spriteSystemInit();

#endif