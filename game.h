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

// represents the states that the game can be at
typedef enum GAME_STATE{
  START,
  PLAYING,
  QUIT,
  END_INIT,
  END,
  HELP
}GameState;

// struct that represents how my program sees the game
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
  ALLEGRO_BITMAP* maziero;
  ALLEGRO_BITMAP* mario;
  ALLEGRO_BITMAP* megaman;
  ALLEGRO_TIMER* timer;
  ALLEGRO_FONT* font;
  ALLEGRO_EVENT_QUEUE* queue;
  ALLEGRO_EVENT event;
}Game;

// initializes all allegro essential systems
void allegroInit(Game* game);

// creates and initializes the game, returning it
// also calls all other necessary constructors
Game* gameConstructor();

// destroys a given game object
// and calls all other necessary destructors
void gameDestructor(Game* game);

// responsible for the main game loop
void playGame(Game* game);

// responsible for updating all game objects
// also calls all other necessary update methods
void gameUpdate(Game* game);

// responsible for drawing the game objects
// also calls all other draw functions
void gameDraw(Game* game);

// responsible for showing and controlling the end screen
void endScreen(Game* game);

// responsible for showing and controlling the start screen
void startScreen(Game* game);

// responsible for displaying the help screen
void helpScreen(Game* game);

// initializes the variables necessary to show the end screen
// like score and ranking
void endInit(Game* game);

#endif