// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "player.h"
#include "utils.h"
#include "display.h"
#include "sprite.h"

Player* playerConstructor(){
  Player* player = mallocSpace(sizeof(Player), "player pointer null");

  player->alive = true;
  player->hp = 3;
  player->startPos.x = BUFFER_WIDTH/2;
  player->startPos.y = BUFFER_HEIGHT/2;
  player->currentPos = player->startPos;
  player->speed.x = 16;
  player->speed.y = 16; 
  player->_sheet = loadSheet("./playerSheet.png");
  player->_sprite = loadSprite(player->_sheet, 0, 0, 16, 16);


  fprintf(stderr, "currentPos (x,y): (%d,%d)\n", player->currentPos.x, player->currentPos.y);
  return player;
}

void playerDestructor(Player* player);

void playerUpdate(Player* player, ALLEGRO_EVENT* event);

void playerDraw(Player* player){
  if(!player) return;

  al_draw_bitmap(player->_sprite, player->currentPos.x, player->currentPos.y, 0);
}