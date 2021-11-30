// Made by Gabriel Lüders
// GRR20190172

#ifndef ANIMATION_H
#define ANIMATION_H

#include <allegro5/allegro5.h>
#include "utils.h"

// struct that represents an animation
typedef struct ANIMATION_STRUCT{
  int x;
  int y;
  int frameCount;
  int currentFrame;
  int refreshRate;
  ALLEGRO_BITMAP* sheet;
}Animation;

// function that creates and initializes an animation, returning it
Animation* animConstructor(
  int x, 
  int y, 
  int frameCount,
  int currentFrame,
  int refreshRate,
  ALLEGRO_BITMAP* sheet  
);

// plays a given animation at a position with a frame limitation with a given offset
void playAnimation(
  Animation* anim,
  Point* pos,
  int frames,
  bool horizontal,
  int offset
);

// destroys a given animation
void animationDestructor(Animation* anim);

#endif