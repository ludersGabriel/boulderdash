// Made by Gabriel Lüders
// GRR20190172

#include "object.h"
#include "utils.h"
#include "sprite.h"

ObjectArr* objArrConstructor(int size, int cols, int lines, const char* errorMessage){
  ObjectArr* objArr = mallocSpace(sizeof(ObjectArr), errorMessage);

  objArr->objects = mallocSpace(sizeof(Object*) * size, errorMessage);
  objArr->length = size;
  objArr->cols = cols;
  objArr->lines = lines;

  for(int i = 0; i < size; i++){
    objArr->objects[i] = NULL;
  }

  return objArr;
}

void objArrDestructor(ObjectArr* objArr){
  if(!objArr) return;

  for(int i = 0; i < objArr->length; i++){
    Object* target = objArr->objects[i];
    if(!target) continue;
    
    spriteDestructor(target->_sprite);
    free(objArr->objects[i]);
  }
  free(objArr->objects);
  free(objArr);
}

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
){
  Object* object = mallocSpace(sizeof(Object), errorMessage);

  object->state = IDLE;
  object->pos.x = x;
  object->pos.y = y;
  object->initialPos.x = x;
  object->initialPos.y = y;
  object->score = score;
  object->width = width;
  object->height = height;
  object->_sprite = _sprite;
  object->speed = speed;
  object->visible = visible;
  object->wall = wall;
  object->dangerous = dangerous;
  object->moving = moving;
  object->type = type;
  object->anim = anim;

  return object;
}

void objectDestructor(Object* object){
  if(!object) return;

  spriteDestructor(object->_sprite);
  if(object->anim)
    free(object->anim);
  free(object);
}

Object* collisionObjxObj(Object* obj, ObjectArr* objArr){
  for(int i = 0; i < objArr->length; i++){
    Object* target = objArr->objects[i];
    if(!target || !target->visible || target == obj)
      continue;

    if(
      collide(
        obj->pos.x,
        obj->pos.y,
        target->pos.x,
        target->pos.y
      )
    ){
      return target;
    }
  }

  return NULL;
}

void handleCollisionObjects(
  Object* obj,
  Point oldPos, 
  ObjectArr* objArr
){
  Object* target = collisionObjxObj(obj, objArr);
  if(!target) return;
  
  obj->pos = oldPos;
  return;

}

void sortObjArr(ObjectArr* objArr){
  int minIdx;
  Object** target = objArr->objects;
  
  for(int i = 0; i < objArr->length - 1; i++){
    minIdx = i;
    for(int j = i + 1; j < objArr->length; j++){
      if(!target[j]) continue;
      if(
        !target[minIdx]
        || target[minIdx]->pos.y > target[j]->pos.y 
      ){
        minIdx = j;
      } 
    }
    Object* temp = target[minIdx];
    target[minIdx] = target[i];
    target[i] = temp;
  }
}

Object* rockInit(ALLEGRO_BITMAP* mapSheet, int x, int y){
  return objectConstructor(
    x,
    y,
    spriteConstructor(mapSheet, 3*TILE_SIZE, TILE_SIZE*TILE_SIZE, TILE_SIZE, TILE_SIZE, "loadin rock"),
    NULL,
    0,
    TILE_SIZE,
    TILE_SIZE,
    1,
    ROCK,
    true,
    true,
    true,
    false,
    "init rock"
  );
}

Object* wallInit(ALLEGRO_BITMAP* mapSheet, int x, int y){
  return objectConstructor(
    x,
    y,
    spriteConstructor(mapSheet, 0*TILE_SIZE, 8*TILE_SIZE, TILE_SIZE, TILE_SIZE, "loding wall"),
    NULL,
    0,
    TILE_SIZE,
    TILE_SIZE,
    0,
    WALL,
    true,
    true,
    false,
    false,
    "init wall"
  );
}

Object* sandInit(ALLEGRO_BITMAP* mapSheet, int x, int y){
  return objectConstructor(
    x,
    y,
    spriteConstructor(mapSheet, 1*TILE_SIZE, 8*TILE_SIZE, TILE_SIZE, TILE_SIZE, "loding sand"),
    NULL,
    0,
    TILE_SIZE,
    TILE_SIZE,
    0,
    SAND,
    true,
    false,
    false,
    false,
    "init sand"
  );
}

Object* playerInit(ALLEGRO_BITMAP* mapSheet, int x, int y){
  return objectConstructor(
    x,
    y,
    NULL,
    NULL,
    0,
    TILE_SIZE,
    TILE_SIZE,
    0,
    PLAYER,
    true,
    false,
    false,
    false,
    "init player map object"
  );
}

Object* diamondInit(ALLEGRO_BITMAP* mapSheet, int diamondValue, int x, int y){
  return objectConstructor(
    x,
    y,
    spriteConstructor(mapSheet, 4*TILE_SIZE, 9*TILE_SIZE, TILE_SIZE, TILE_SIZE, "loading diamond"),
    animConstructor(4, 8, 4, 0, 8, mapSheet),
    diamondValue,
    TILE_SIZE,
    TILE_SIZE,
    1,
    DIAMOND,
    true,
    false,
    false,
    false,
    "init diamond"
  );
}

Object* doorInit(ALLEGRO_BITMAP* mapSheet, int x, int y){
  return objectConstructor(
    x,
    y,
    spriteConstructor(mapSheet, 7*TILE_SIZE, 8*TILE_SIZE, TILE_SIZE, TILE_SIZE, "loading door"),
    animConstructor(7, 8, 4, 0, 10, mapSheet),
    0,
    TILE_SIZE,
    TILE_SIZE,
    0,
    DOOR,
    true,
    false,
    false,
    false,
    "init door"
  );
}

