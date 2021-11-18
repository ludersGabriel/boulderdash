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
  player->hp = 3;
  player->startPos.x = map->playerPos.x * 16;
  player->startPos.y = map->playerPos.y * 16;
  player->currentPos = player->startPos;
  player->width = PLAYER_WIDTH;
  player->height = PLAYER_HEIGHT;
  player->speed.x = PLAYER_SPEED_X;
  player->speed.y = PLAYER_SPPED_Y; 
  player->_sheet = loadSheet("./resources/playerSheet.png");
  player->_sprite = spriteConstructor(player->_sheet, 0, 0, 16, 16, "player sprite");
  player->fatigue_timer = 0;
  player->fatigue = PLAYER_FATIGUE;

  return player;
}

void playerDestructor(Player* player){
  if(!player) return;
  
  sheetDestructor(player->_sheet);
  spriteDestructor(player->_sprite);
  free(player);
}

bool handleCollision(
  Point playerPos,
  ObjectArr* virtualMap,
  long int* score
){
  Point paddedPlayerPos;
  paddedPlayerPos.x = playerPos.x / 16;
  paddedPlayerPos.y = playerPos.y / 16;

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

      *score += target->score;
      switch(target->type){
        case ROCK:
        case WALL:
          return true;
        case DIAMOND:
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
  long int* score
){
  if(player->fatigue_timer){
    player->fatigue_timer--;
    return;
  }

  Point newPos = player->currentPos;

  if(virtualKeyboard[ALLEGRO_KEY_D] || virtualKeyboard[ALLEGRO_KEY_RIGHT]){
    newPos.x += player->speed.x;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_A] || virtualKeyboard[ALLEGRO_KEY_LEFT]){
    newPos.x -= player->speed.x;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_W] || virtualKeyboard[ALLEGRO_KEY_UP]){
    newPos.y -= player->speed.y;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_S] || virtualKeyboard[ALLEGRO_KEY_DOWN]){
    newPos.y += player->speed.y;
  }

  if(newPos.x != player->currentPos.x || newPos.y != player->currentPos.y){
    if(handleCollision(newPos, map->virtualMap, score)) return;

    player->currentPos = newPos;
    player->fatigue_timer = player->fatigue;
  }
}

void playerUpdate(
  Player* player, 
  ALLEGRO_EVENT* event, 
  Map* map,
  long int* score
){
  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      controlPlayerMovement(player, map, score);

      break;
    default:
      break;
  }
}

void playerDraw(Player* player){
  if(!player) return;

  al_draw_bitmap(player->_sprite->bitmap, player->currentPos.x, player->currentPos.y, 0);
}