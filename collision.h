// Made by Gabriel Lüders
// GRR20190172

#ifndef COLLISION_H
#define COLLISION_H

#include <allegro5/allegro5.h>
#include "object.h"

bool collide(
  int ax1, 
  int ax2, 
  int ay1, 
  int ay2, 
  int bx1, 
  int bx2, 
  int by1, 
  int by2
);

#endif