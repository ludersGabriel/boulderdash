// Made by Gabriel Lüders
// GRR20190172

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include "map.h"

typedef struct GAME{
  long frames;
  long score;
  Map* map;
}Game;

Game* gameConstructor();

void gameDestructor(Game* game);

#endif