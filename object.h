// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

typedef struct OBJECT{
  Point pos;
  Sprite* _sprite;
  bool visible;
  bool wall;
  bool dangerous;
  bool moving;
}Object;

Object* objectConstructor(
  Point pos,
  Sprite* _sprite,
  bool visible,
  bool wall,
  bool dangerous,
  bool moving,
  const char* errorMessage 
);

void objectDestructor(Object* object);

#endif