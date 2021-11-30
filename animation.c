// Made by Gabriel Lüders
// GRR20190172

#include "animation.h"
#include "sprite.h"
#include "utils.h"
#include <stdio.h>

// function that creates and initializes an animation
Animation* animConstructor(
  int x, 
  int y, 
  int frameCount,
  int currentFrame,
  int refreshRate,
  ALLEGRO_BITMAP* sheet  
){
  Animation* anim = mallocSpace(sizeof(Animation), "Init animation");

  anim->currentFrame = currentFrame;
  anim->frameCount = frameCount;
  anim->sheet = sheet;
  anim->x = x * TILE_SIZE;
  anim->y = y * TILE_SIZE;
  anim->refreshRate = refreshRate;

  return anim;
}

// plays a given animation at a position with a frame limitation with a given offset
void playAnimation(
  Animation* anim,
  Point* pos,
  int frames,
  bool horizontal,
  int offset
){
  if(!anim) return;

  horizontal 
    ? al_draw_bitmap_region(
        anim->sheet,
        anim->x + TILE_SIZE*anim->currentFrame,
        anim->y,
        TILE_SIZE,
        TILE_SIZE,
        pos->x + offset,
        pos->y,
        0
      )
    : al_draw_bitmap_region(
        anim->sheet,
        anim->x,
        anim->y + TILE_SIZE*anim->currentFrame,
        TILE_SIZE,
        TILE_SIZE,
        pos->x + offset,
        pos->y,
        0
      );

  // goes to the next frame only when frames hit the refresh rate
  if(frames % anim->refreshRate == 0){
    anim->currentFrame += 1;
  }
  if(anim->currentFrame >= anim->frameCount)
    anim->currentFrame = 0;

}

// destroys a given animation
void animationDestructor(Animation* anim){
  if(!anim) return;

  free(anim);
}