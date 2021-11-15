// Made by Gabriel Lüders
// GRR20190172

#include "collision.h"
#include "player.h"

bool collide(
  int ax1, 
  int ay1, 
  int bx1, 
  int by1
){
  if(ax1 == bx1 && ay1 == by1) return true;

  return false;
}

