// Made by Gabriel Lüders
// GRR20190172 

#ifndef MAP_H
#define MAP_H

#define MAP1_PATH "./resources/map1.txt"

#include <allegro5/allegro5.h>
#include "sprite.h"
#include "display.h"
#include "object.h"
#include "audio.h"

typedef struct MAP{
  ALLEGRO_BITMAP* _sheet;
  Sprite* background;
  int width;
  int height;
  int necessaryDiamonds;
  int diamondValue;
  int maxTime;
  ObjectArr* virtualMap;
}Map;

Map* mapConstructor(Display* display);

void mapDestructor(Map* map);

void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames, AudioManager* audioManager);

void setPlayerPos(Map* map, Point playerPos);

Point getPlayerPos(Map* map);

Point getPaddedPlayerPos(Map* map);

Object* objectInPos(ObjectArr* virtualMap, int x, int y);

void drawBackground(Sprite* background, Display* display);

void mapDraw(Map* map, Display* display, int frames);

#endif