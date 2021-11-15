// Made by Gabriel Lüders
// GRR20190172

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "map.h"
#include "player.h"
#include "display.h"

typedef struct GAME{
  long frames;
  long score;
  Map* map;
  Player* player;
  Display* display;
}Game;

Game* gameConstructor();

void gameDestructor(Game* game);

void gameUpdate(Game* game, ALLEGRO_EVENT* event);

void gameDraw(Game* game, ALLEGRO_FONT* font);

#endif