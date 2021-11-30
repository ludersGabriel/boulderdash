// Made by Gabriel Lüders
// GRR20190172

#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include "sprite.h"
#include "animation.h"

// enum for all the possible object types
typedef enum OBJECT_TYPE{
  EMPTY = 0,
  ROCK,
  WALL,
  SAND,
  DIAMOND,
  PLAYER,
  DOOR,
  FALSE_WALL,
  PINK_DIAMOND,
  OBJECT_TYPE_AMOUNT
}ObjectType;

// enum to represent the possible object states
typedef enum OBJECT_STATE{
  IDLE,
  FALLING
}ObjectState;

// struct that defines an object
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

// struct that represents an object array
typedef struct OBJECT_ARRAY{
  Object** objects;
  int cols;
  int lines;
  int length;
}ObjectArr;

// creates and initializes an object array, returning it
ObjectArr* objArrConstructor(int size, int cols, int lines, const char* errorMessage);

// destroys an object array
void objArrDestructor(ObjectArr* objArr);

// creates and initializes an object, returning it
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

// destroys a given object
void objectDestructor(Object* object);

// sort an object array by object height
void sortObjArr(ObjectArr* objArr);

// function that initializes a rock object
Object* rockInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a wall object
Object* wallInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a sand object
Object* sandInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a dummy player object
Object* playerInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a diamond object
Object* diamondInit(ALLEGRO_BITMAP* mapSheet, int diamondValue, int x, int y);

// initializes a door object
Object* doorInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a false wall object
Object* falseWallInit(ALLEGRO_BITMAP* mapSheet, int x, int y);

// initializes a pink diamond for the easter egg
Object* pinkDiamondInit(ALLEGRO_BITMAP* mapSheet, int diamondValue, int x, int y);

#endif