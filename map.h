// Made by Gabriel Lüders
// GRR20190172 

#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro5.h>
#include "sprite.h"
#include "display.h"
#include "object.h"

typedef struct MAP{
  ALLEGRO_BITMAP* _sheet;
  Sprite* background;
  ObjectArr* rocks;
  ObjectArr* sand; 
  ObjectArr* walls;
  ObjectArr* diamonds;
}Map;

Map* mapConstructor();

void mapDestructor(Map* map);

void mapUpdate(Map* map, ALLEGRO_EVENT* event);

void mapDraw(Map* map, Display* display);

#endif