// Made by Gabriel Lüders
// GRR20190172 

#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro5.h>

typedef struct MAP{
  ALLEGRO_BITMAP* _sheet;
  ALLEGRO_BITMAP* background;
}Map;

Map* mapConstructor();

void mapDestructor(Map* map);

#endif