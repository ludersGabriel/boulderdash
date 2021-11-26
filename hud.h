// Made by Gabriel Lüders
// GRR20190172

#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "sprite.h"

void drawHud(
  int score,
  int necessaryDiamonds,
  int currentDiamonds, 
  int diamondValue,
  int time,
  ALLEGRO_FONT* font
);

#endif