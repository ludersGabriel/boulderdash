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

// struct that represents the map object
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

// creates and initializes a map object, returning it
Map* mapConstructor(Display* display);

// destroys a given map object
void mapDestructor(Map* map);

// responsible for update all map objects
void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames, AudioManager* audioManager);

// set the position of the dummy player object inside the map structure
void setPlayerPos(Map* map, Point playerPos);

// gets the real player position from the map structure
Point getPlayerPos(Map* map);

// gets the player position directly in the map structure
Point getPaddedPlayerPos(Map* map);

// checks if there is an ojbect at a given coordinate
Object* objectInPos(ObjectArr* virtualMap, int x, int y);

// draws the backgound
void drawBackground(Sprite* background, Display* display);

// draws the map objects
void mapDraw(Map* map, Display* display, int frames);

#endif