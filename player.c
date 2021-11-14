// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "player.h"
#include "utils.h"
#include "display.h"
#include "sprite.h"
#include "input.h"

Player* playerConstructor(){
  Player* player = mallocSpace(sizeof(Player), "player pointer null");

  player->alive = true;
  player->hp = 3;
  player->startPos.x = BUFFER_WIDTH/2;
  player->startPos.y = BUFFER_HEIGHT/2;
  player->currentPos = player->startPos;
  player->speed.x = PLAYER_SPEED_X;
  player->speed.y = PLAYER_SPPED_Y; 
  player->_sheet = loadSheet("./resources/playerSheet.png");
  player->_sprite = spriteConstructor(player->_sheet, 0, 0, 16, 16, "player sprite");
  player->fatigue_timer = 0;

  return player;
}

void playerDestructor(Player* player){
  sheetDestructor(player->_sheet);
  spriteDestructor(player->_sprite);
  free(player);
}

void controlPlayerMovement(Player* player){
  if(player->fatigue_timer){
    player->fatigue_timer--;
    return;
  }

  if(virtualKeyboard[ALLEGRO_KEY_D] || virtualKeyboard[ALLEGRO_KEY_RIGHT]){
    player->currentPos.x += player->speed.x;
    player->fatigue_timer = PLAYER_FATIGUE;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_A] || virtualKeyboard[ALLEGRO_KEY_LEFT]){
    player->currentPos.x -= player->speed.x;
    player->fatigue_timer = PLAYER_FATIGUE;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_W] || virtualKeyboard[ALLEGRO_KEY_UP]){
    player->currentPos.y -= player->speed.y;
    player->fatigue_timer = PLAYER_FATIGUE;
  }
  else if(virtualKeyboard[ALLEGRO_KEY_S] || virtualKeyboard[ALLEGRO_KEY_DOWN]){
    player->currentPos.y += player->speed.y;
    player->fatigue_timer = PLAYER_FATIGUE;
  }

  if(player->currentPos.x < 0){
    player->currentPos.x = 0;
  }

  if(player->currentPos.x + player->_sprite->width > BUFFER_WIDTH){
    player->currentPos.x = BUFFER_WIDTH - player->_sprite->width;
  }

  if(player->currentPos.y < 0){
    player->currentPos.y = 0;
  }

  if(player->currentPos.y + player->_sprite->height > BUFFER_HEIGHT){
    player->currentPos.y = BUFFER_HEIGHT - player->_sprite->height;
  }
}

void playerUpdate(Player* player, ALLEGRO_EVENT* event){
  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      controlPlayerMovement(player);

      break;
    default:
      break;
  }
}

void playerDraw(Player* player){
  if(!player) return;

  al_draw_bitmap(player->_sprite->bitmap, player->currentPos.x, player->currentPos.y, 0);
}