// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include "sprite.h"
#include "collision.h"

typedef enum OBJECT_TYPE{
  empty = 0,
  rock,
  wall,
  sand,
  diamond,
  objectTypeAmount
}ObjectType;

typedef struct OBJECT{
  Point pos;
  Sprite* _sprite;
  int score;
  int width;
  int height;
  int speed;
  ObjectType type;
  bool visible;
  bool wall;
  bool dangerous;
  bool moving;
}Object;

typedef struct OBJECT_ARRAY{
  Object** objects;
  int cols;
  int lines;
  int length;
}ObjectArr;

ObjectArr* objArrConstructor(int size, int cols, int lines, const char* errorMessage);

void objArrDestructor(ObjectArr* objArr);

Object* objectConstructor(
  int x,
  int y,
  Sprite* _sprite,
  int score,
  int width,
  int height,
  int speed,
  ObjectType type,
  bool visible,
  bool wall,
  bool dangerous,
  bool moving,
  const char* errorMessage 
);

void objectDestructor(Object* object);

Object* collisionObjxObj(Object* obj, ObjectArr* objArr);

void sortObjArr(ObjectArr* objArr);

void handleCollisionObjects(Object* obj, Point oldPos, ObjectArr* objArr);

#endif