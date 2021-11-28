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
#include "animation.h"

#define PLAYER_FATIGUE 7
#define PLAYER_SPEED_X 16
#define PLAYER_SPPED_Y 16
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 16
#define PLAYER_HP 3
#define GAME_END 3

typedef enum PLAYER_STATER{
  PLAYER_IDLE,
  MOVING_RIGHT,
  MOVING_LEFT,
  MOVING_DOWN,
  MOVING_UP
}PlayerState;

typedef struct PLAYER{
  int hp;
  bool alive;
  Point startPos;
  Point currentPos;
  Point speed;
  PlayerState state;
  PlayerState lastHorizontal;
  int width;
  int height;
  int fatigue_timer;
  int fatigue;
  int diamondHeld;
  float scoreMultiplier;
  ALLEGRO_BITMAP* _sheet;
  Animation* idleAnim;
  Animation* leftAnim;
  Animation* rightAnim;
}Player;

Player* playerConstructor(Map* map);

void playerDestructor(Player* player);

void playerUpdate(
  Player* player, 
  ALLEGRO_EVENT* event, 
  Map* map,
  long int* score,
  int* gameState
);

void playerDraw(Player* player, int frames);

Object* collisionPlayerxObj(Player* player, ObjectArr* objArr);

#endif