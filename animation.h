// Made by Gabriel Lüders
// GRR20190172

#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro5/allegro5.h>
#include "utils.h"

typedef struct ANIMATION_STRUCT{
  int x;
  int y;
  int frameCount;
  int currentFrame;
  int refreshRate;
  ALLEGRO_BITMAP* sheet;
}Animation;

Animation* animConstructor(
  int x, 
  int y, 
  int frameCount,
  int currentFrame,
  int refreshRate,
  ALLEGRO_BITMAP* sheet  
);

void playAnimation(
  Animation* anim,
  Point* pos,
  int frames
);


#endif