// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include "sprite.h"
#include "collision.h"
#include "animation.h"

typedef enum OBJECT_TYPE{
  EMPTY = 0,
  ROCK,
  WALL,
  SAND,
  DIAMOND,
  PLAYER,
  DOOR,
  OBJECT_TYPE_AMOUNT
}ObjectType;

typedef enum OBJECT_STATE{
  IDLE,
  FALLING
}ObjectState;

typedef struct OBJECT{
  Point pos;
  Point initialPos;
  Sprite* _sprite;
  Animation* anim;
  int score;
  int width;
  int height;
  int speed;
  ObjectType type;
  ObjectState state;
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
  Animation* anim,
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

Object* rockInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

Object* wallInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

Object* sandInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

Object* playerInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

Object* diamondInit(ALLEGRO_BITMAP* mapSheet, int diamondValue, int x, int y);

Object* doorInit(ALLEGRO_BITMAP* mapSheet, int x, int y);



#endif