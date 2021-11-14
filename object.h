// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "player.h"

typedef struct OBJECT{
  Point pos;
  Sprite* _sprite;
  bool visible;
  bool wall;
  bool dangerous;
  bool moving;
}Object;

typedef struct OBJECT_ARRAY{
  Object** objects;
  int length;
}ObjectArr;

ObjectArr* objArrConstructor(int size, const char* errorMessage);

void objArrDestructor(ObjectArr* objArr);

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