// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include "sprite.h"
#include "collision.h"

typedef struct OBJECT{
  Point pos;
  Sprite* _sprite;
  int score;
  int width;
  int height;
  int speed;
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
  int x,
  int y,
  Sprite* _sprite,
  int score,
  int width,
  int height,
  int speed,
  bool visible,
  bool wall,
  bool dangerous,
  bool moving,
  const char* errorMessage 
);

void objectDestructor(Object* object);

Object* collisionObjxObj(Object* obj, ObjectArr* objArr);

void sortObjArr(ObjectArr* objArr);

#endif