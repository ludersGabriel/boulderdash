// Made by Gabriel Lüders
// GRR20190172

#include "hud.h"

void drawHud(
  int score,
  int necessaryDiamonds,
  int currentDiamonds,
  int diamondValue, 
  int time, 
  ALLEGRO_FONT* font
){
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*4, 5, 0, "%02d/", necessaryDiamonds);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*5, 5, 0, " %02d", diamondValue);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*10, 5, 0, "%02d", currentDiamonds);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*20, 5, 0, "%03d", time);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*30, 5, 0, "%06d", score);
}