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
#include "hud.h"
#include "audio.h"

#define RANK_PATH "./resources/score.txt"
#define RANKING_SIZE 10

typedef enum GAME_STATE{
  BEGINNING,
  PLAYING,
  QUIT,
  END_INIT,
  END
}GameState;

typedef struct GAME{
  long frames;
  long score;
  int timeAvailabe;
  bool redraw;
  int ranking[RANKING_SIZE];
  GameState state;
  Map* map;
  Player* player;
  Display* display;
  AudioManager* audioManager;
  ALLEGRO_TIMER* timer;
  ALLEGRO_FONT* font;
  ALLEGRO_EVENT_QUEUE* queue;
  ALLEGRO_EVENT event;
}Game;

void allegroInit(Game* game);

Game* gameConstructor();

void gameDestructor(Game* game);

void playGame(Game* game);

void gameUpdate(Game* game);

void gameDraw(Game* game);

void endScreen(Game* game);

void endInit(Game* game);

#endif