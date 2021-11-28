// Made by Gabriel Lüders
// GRR20190172

#include "animation.h"
#include "sprite.h"
#include "utils.h"
#include <stdio.h>

Animation* animConstructor(
  int x, 
  int y, 
  int frameCount,
  int currentFrame,
  ALLEGRO_BITMAP* sheet  
){
  Animation* anim = mallocSpace(sizeof(Animation), "Init animation");

  anim->currentFrame = currentFrame;
  anim->frameCount = frameCount;
  anim->sheet = sheet;
  anim->x = x * TILE_SIZE;
  anim->y = y * TILE_SIZE;

  return anim;
}

void playAnimation(
  Animation* anim,
  Point* pos,
  int frames,
  int refresh
){
  if(!anim) return;

  al_draw_bitmap_region(
    anim->sheet,
    anim->x + TILE_SIZE*anim->currentFrame,
    anim->y,
    TILE_SIZE,
    TILE_SIZE,
    pos->x,
    pos->y,
    0
  );

  if(frames % refresh == 0){
    anim->currentFrame += 1;
  }
  if(anim->currentFrame >= anim->frameCount)
    anim->currentFrame = 0;

}