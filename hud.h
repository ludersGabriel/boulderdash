// Made by Gabriel Lüders
// GRR20190172

#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "sprite.h"

// draws the hud at the top of the screen
void drawHud(
  int score,
  int necessaryDiamonds,
  int currentDiamonds, 
  int diamondValue,
  int time,
  ALLEGRO_FONT* font
);

// draws the end screen
void drawEndScreen(int* ranking, int length, ALLEGRO_FONT* font);

// draws the help screen
void drawHowToPlay(ALLEGRO_FONT* font, bool help);

// draws start screen
void drawStartScreen(ALLEGRO_FONT* font);

#endif