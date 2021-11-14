// Made by Gabriel Lüders
// GRR20190172 

#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>
#include "sprite.h"
#include "display.h"

#define PLAYER_FATIGUE 5
#define PLAYER_SPEED_X 16
#define PLAYER_SPPED_Y 16
typedef struct POINT{
  int x;
  int y;
}Point;

typedef struct PLAYER{
  int hp;
  bool alive;
  Point startPos;
  Point currentPos;
  Point speed;
  int fatigue_timer;
  int fatigue;

  ALLEGRO_BITMAP* _sheet;
  Sprite* _sprite;
}Player;

Player* playerConstructor(Display* display);

void playerDestructor(Player* player);

void playerUpdate(Player* player, ALLEGRO_EVENT* event, Display* display);

void playerDraw(Player* player);

#endif