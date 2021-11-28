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
  al_draw_textf(font, al_map_rgb(255, 255, 121), TILE_SIZE*4, 5, 0, "%02d", necessaryDiamonds);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*5, 5, 0, "/%02d", diamondValue);
  al_draw_textf(font, al_map_rgb(255, 255, 121), TILE_SIZE*10, 5, 0, "%02d", currentDiamonds);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*20, 5, 0, "%03d", time);
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*30, 5, 0, "%06d", score);
}

void drawEndScreen(int* ranking, int length, ALLEGRO_FONT* font){
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*15, TILE_SIZE*3, 0, "RANKING");

  int i;
  for(i = 0; i < length; i++){
    if(!ranking[i]) break;
    
    al_draw_textf(
      font, al_map_rgb(255, 255, 255), 
      TILE_SIZE*15 + 5, 
      TILE_SIZE*(5 + i), 
      0, 
      "%06d",
      ranking[i]
    );
  }

  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*15, TILE_SIZE*(6 + i), 0, "Press anything to quit...");
  al_draw_textf(font, al_map_rgb(255, 255, 255), TILE_SIZE*15, TILE_SIZE*(7 + i), 0, "The End!");

}