// Made by Gabriel Lüders
// GRR20190172

#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "map.h"
#include "player.h"
#include "display.h"
#include "input.h"

typedef enum GAME_STATE{
  beginning,
  playing,
  quit
}GameState;

typedef struct GAME{
  long frames;
  long score;
  GameState state;
  Map* map;
  Player* player;
  Display* display;
  ALLEGRO_TIMER* timer;
  ALLEGRO_FONT* font;
  ALLEGRO_EVENT_QUEUE* queue;
  ALLEGRO_EVENT event;
  
  bool redraw;
}Game;

void allegroInit(Game* game);

Game* gameConstructor();

void gameDestructor(Game* game);

void playGame(Game* game);

void gameUpdate(Game* game);

void gameDraw(Game* game);

#endif