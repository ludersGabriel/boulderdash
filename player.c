// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "player.h"
#include "utils.h"
#include "display.h"
#include "sprite.h"
#include "input.h"

Player* playerConstructor(Map* map){
  Player* player = mallocSpace(sizeof(Player), "player pointer null");

  player->alive = true;
  player->hp = PLAYER_HP;
  player->startPos = getPlayerPos(map);
  player->currentPos = player->startPos;
  player->width = PLAYER_WIDTH;
  player->height = PLAYER_HEIGHT;
  player->speed.x = PLAYER_SPEED_X;
  player->speed.y = PLAYER_SPPED_Y; 
  player->_sheet = loadSheet("./resources/playerSheet.png");
  player->_sprite = spriteConstructor(player->_sheet, 0, 0, TILE_SIZE, TILE_SIZE, "player sprite");
  player->fatigue_timer = 0;
  player->fatigue = PLAYER_FATIGUE;
  player->diamondHeld = 0;
  player->scoreMultiplier = 1;
  player->state = PLAYER_IDLE;
  player->idleAnim = animConstructor(0, 0, 2, 0, 12, player->_sheet);
  player->rightAnim = animConstructor(0, 3, 3, 0, 20, player->_sheet);
  player->leftAnim = animConstructor(0, 1, 3, 0, 20, player->_sheet);
  player->lastHorizontal = MOVING_RIGHT;

  return player;
}

bool checkDeath(Map* map){
  ObjectArr* virtualMap = map->virtualMap;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(
      !target
      || !target->visible
      || target->type == PLAYER
      || target->state != FALLING
      || !comparePoints(target->pos, getPaddedPlayerPos(map))
    ){
      continue;
    }

    return true;
  }

  return false;
}

void playerDestructor(Player* player){
  if(!player) return;
  
  sheetDestructor(player->_sheet);
  spriteDestructor(player->_sprite);
  free(player->idleAnim);
  free(player->leftAnim);
  free(player->rightAnim);
  free(player);
}

bool handleCollision(
  Player* player,
  Point newPos,
  int xDiff,
  Map* map,
  long int* score,
  int* gameState
){
  Point paddedPlayerPos;
  ObjectArr* virtualMap = map->virtualMap;
  paddedPlayerPos.x = newPos.x / TILE_SIZE;
  paddedPlayerPos.y = newPos.y / TILE_SIZE;

  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(
        !target 
        || !target->visible
        || !comparePoints(target->pos, paddedPlayerPos)
      ){
        continue;
      }

      switch(target->type){
        case ROCK:
          if(
            target->state == IDLE 
            && xDiff
            && !objectInPos(virtualMap, target->pos.x + xDiff, target->pos.y)
          ){
            target->pos.x += xDiff;
            return false;
          }
        case WALL:
          return true;
        case DOOR:
          if(player->diamondHeld >= map->necessaryDiamonds){
            *gameState = GAME_END;
          }
          return false;
        case DIAMOND:
          player->diamondHeld += 1;
          *score += target->score * player->scoreMultiplier;
          if(
            player->diamondHeld >= map->necessaryDiamonds
            && player->scoreMultiplier < 1.5
          ){
            player->scoreMultiplier = 1.5;
          }
        case SAND:
          target->visible = false;
          break;
        case EMPTY:
        default:
          break;
      }

    }
  }

  return false;
}

void controlPlayerMovement(
  Player* player, 
  Map* map,
  long int* score,
  int* gameState
){
  if(player->fatigue_timer){
    player->fatigue_timer--;
    return;
  }

  Point newPos = player->currentPos;

  if(virtualKeyboard[ALLEGRO_KEY_D] || virtualKeyboard[ALLEGRO_KEY_RIGHT]){
    newPos.x += player->speed.x;
    player->state = MOVING_RIGHT;
    player->lastHorizontal = MOVING_RIGHT;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_A] || virtualKeyboard[ALLEGRO_KEY_LEFT]){
    newPos.x -= player->speed.x;
    player->state = MOVING_LEFT;
    player->lastHorizontal = MOVING_LEFT;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_W] || virtualKeyboard[ALLEGRO_KEY_UP]){
    newPos.y -= player->speed.y;
    player->state = MOVING_UP;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_S] || virtualKeyboard[ALLEGRO_KEY_DOWN]){
    newPos.y += player->speed.y;
    player->state = MOVING_DOWN;
  }

  if(!comparePoints(newPos, player->currentPos)){
    int xDiff = (newPos.x - player->currentPos.x)/TILE_SIZE;
    if(handleCollision(player, newPos, xDiff, map, score, gameState)){
      player->state = PLAYER_IDLE;
      return;
    } 

    player->currentPos = newPos;
    setPlayerPos(map, newPos);
    player->fatigue_timer = player->fatigue;
  }else{
    player->state = PLAYER_IDLE;
  }
}

void playerUpdate(
  Player* player, 
  ALLEGRO_EVENT* event, 
  Map* map,
  long int* score,
  int* gameState
){
  if(!player || !player->alive){
    return;
  }

  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      if(checkDeath(map)){
        player->alive = false;
        return;
      }
      controlPlayerMovement(player, map, score, gameState);

      break;
    default:
      break;
  }
}

void playerDraw(Player* player, int frames){
  if(!player) return;

  switch(player->state){
    case PLAYER_IDLE:
      playAnimation(player->idleAnim, &player->currentPos, frames);
      break;
    case MOVING_RIGHT:
      playAnimation(player->rightAnim, &player->currentPos, frames);
      break;
    case MOVING_LEFT:
      playAnimation(player->leftAnim, &player->currentPos, frames);
      break;
    case MOVING_DOWN:
    case MOVING_UP:
      if(player->lastHorizontal == MOVING_RIGHT){
        playAnimation(player->rightAnim, &player->currentPos, frames);
        break;
      }

      playAnimation(player->leftAnim, &player->currentPos, frames);
      break;
    default:
      break;
  }
}