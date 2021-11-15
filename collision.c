// Made by Gabriel Lüders
// GRR20190172

#include "collision.h"
#include "player.h"

bool collide(
  int ax1, 
  int ax2, 
  int ay1, 
  int ay2, 
  int bx1, 
  int bx2, 
  int by1, 
  int by2
){
  if(ax1 > bx2) return false;
  if(ax2 < bx1) return false;
  if(ay1 > by2) return false;
  if(ay2 < by1) return false;

  return true;
}

