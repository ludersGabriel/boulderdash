// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "player.h"
#include "utils.h"
#include "display.h"
#include "sprite.h"
#include "input.h"

Player* playerConstructor(Display* display){
  Player* player = mallocSpace(sizeof(Player), "player pointer null");

  player->alive = true;
  player->hp = 3;
  player->startPos.x = display->bufferWidth/2 + (display->bufferWidth/2) % 16;
  player->startPos.y = display->bufferHeight/2 + (display->bufferHeight/2) % 16;
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

Object* collisionPlayerxObj(Player* player, ObjectArr* objArr){
  for(int i = 0; i < objArr->length; i++){
    Object* target = objArr->objects[i];
    if(!target || !target->visible)
      continue;

    if(
      collide(
        player->currentPos.x,
        player->currentPos.y,
        target->pos.x,
        target->pos.y
      )
    ){
      return target;
    }
  }

  return NULL;
}

void handleCollision(
  Player* player,
  Point oldPos, 
  ObjectArr* objArr, 
  long int* score
){
  Object* target = collisionPlayerxObj(player, objArr);
  if(!target) return;
  
  if(target->wall){
    player->currentPos = oldPos;
    return;
  }

  target->visible = false;
  *score += target->score;
}

void controlPlayerMovement(
  Player* player, 
  Display* display,
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
    Point oldPos = player->currentPos;
    player->currentPos = newPos;

    handleCollision(player, oldPos,  map->rocks, score);
    handleCollision(player, oldPos,  map->sand, score);
    handleCollision(player, oldPos,  map->diamonds, score);
    handleCollision(player, oldPos, map->walls, score);

    player->fatigue_timer = player->fatigue;
  }
}

void playerUpdate(
  Player* player, 
  ALLEGRO_EVENT* event, 
  Display* display,
  Map* map,
  long int* score
){
  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      controlPlayerMovement(player, display, map, score);

      break;
    default:
      break;
  }
}

void playerDraw(Player* player){
  if(!player) return;

  al_draw_bitmap(player->_sprite->bitmap, player->currentPos.x, player->currentPos.y, 0);
}