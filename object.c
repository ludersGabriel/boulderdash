// Made by Gabriel Lüders
// GRR20190172

#include "object.h"
#include "utils.h"
#include "sprite.h"

ObjectArr* objArrConstructor(int size, const char* errorMessage){
  ObjectArr* objArr = mallocSpace(sizeof(ObjectArr), errorMessage);

  objArr->objects = mallocSpace(sizeof(Object*) * size, errorMessage);
  objArr->length = size;

  for(int i = 0; i < size; i++){
    objArr->objects[i] = NULL;
  }

  return objArr;
}

void objArrDestructor(ObjectArr* objArr){
  if(!objArr) return;

  for(int i = 0; i < objArr->length; i++){
    if(!objArr->objects[i]) continue;

    free(objArr->objects[i]);
  }
  free(objArr->objects);
  free(objArr);
}

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
){
  Object* object = mallocSpace(sizeof(Object), errorMessage);

  object->pos.x = x;
  object->pos.y = y;
  object->score = score;
  object->width = width;
  object->height = height;
  object->_sprite = _sprite;
  object->speed = speed;
  object->visible = visible;
  object->wall = wall;
  object->dangerous = dangerous;
  object->moving = moving;

  return object;
}

void objectDestructor(Object* object){
  if(!object) return;

  spriteDestructor(object->_sprite);
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
  int maxIdx;
  Object** target = objArr->objects;
  
  for(int i = 0; i < objArr->length - 1; i++){
    maxIdx = i;
    for(int j = i + 1; j < objArr->length; j++){
      if(!target[j]) continue;
      if(
        !target[maxIdx]
        || target[maxIdx]->pos.y < target[j]->pos.y 
      ){
        maxIdx = j;
      } 
    }
    Object* temp = target[maxIdx];
    target[maxIdx] = target[i];
    target[i] = temp;
  }
}