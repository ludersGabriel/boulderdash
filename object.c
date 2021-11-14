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
  bool visible,
  bool wall,
  bool dangerous,
  bool moving,
  const char* errorMessage
){
  Object* object = mallocSpace(sizeof(Object), errorMessage);

  object->pos.x = x;
  object->pos.y = y;
  object->_sprite = _sprite;
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

