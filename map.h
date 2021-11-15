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
  int width;
  int height;
  ObjectArr* rocks;
  ObjectArr* sand; 
  ObjectArr* walls;
  ObjectArr* diamonds;
}Map;

Map* mapConstructor(Display* display);

void mapDestructor(Map* map);

void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames);

void mapDraw(Map* map, Display* display);

#endif