// Made by Gabriel Lüders
// GRR20190172 

#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro5.h>
#include "sprite.h"

typedef struct MAP{
  ALLEGRO_BITMAP* _sheet;
  Sprite* background;
}Map;

Map* mapConstructor();

void mapDestructor(Map* map);

void mapUpdate(Map* map, ALLEGRO_EVENT* event);

void mapDraw(Map* map);

#endif