// Made by Gabriel Lüders
// GRR20190172 

#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>


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

  ALLEGRO_BITMAP* _sheet;
  ALLEGRO_BITMAP* _sprite;
}Player;

Player* playerConstructor();

void playerDestructor(Player* player);

void playerUpdate(Player* player, ALLEGRO_EVENT* event);

void playerDraw(Player* player);

#endif