// Made by Gabriel Lüders
// GRR20190172 

#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>
#include "sprite.h"
#include "display.h"
#include "utils.h"
#include "object.h"
#include "collision.h"
#include "map.h"

#define PLAYER_FATIGUE 5
#define PLAYER_SPEED_X 16
#define PLAYER_SPPED_Y 16
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 16

typedef struct PLAYER{
  int hp;
  bool alive;
  Point startPos;
  Point currentPos;
  Point speed;
  int width;
  int height;
  int fatigue_timer;
  int fatigue;

  ALLEGRO_BITMAP* _sheet;
  Sprite* _sprite;
}Player;

Player* playerConstructor(Display* display);

void playerDestructor(Player* player);

void playerUpdate(
  Player* player, 
  ALLEGRO_EVENT* event, 
  Map* map,
  long int* score
);

void playerDraw(Player* player);

Object* collisionPlayerxObj(Player* player, ObjectArr* objArr);

#endif