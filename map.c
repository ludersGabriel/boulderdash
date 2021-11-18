// Made by Gabriel Lüders
// GRR20190172 

#include <stdio.h>
#include "map.h"
#include "sprite.h"
#include "utils.h"
#include "display.h"

ObjectArr* initVirtualMap(Map* map){
  int length = map->width * map->height;
  ObjectArr* virtualMap = objArrConstructor(
    length, 
    map->width, 
    map->height, 
    "error allocating virtual map"
  );
  virtualMap->length = length;
  for(int i = 0; i < virtualMap->length; i++)
    virtualMap->objects[i] = NULL;
  
  FILE* codedMap = fopen(MAP1_PATH, "r");
  if(!codedMap){
    fprintf(stderr, "Failed to load map from file\n");
    exit(1);
  }

  char* line;
  int value;
  for(int i = 0; i < virtualMap->lines && fscanf(codedMap, "%m[^\n]", &line) > 0; i++){
    fgetc(codedMap);

    char* temp = line;
    int lineSize;
    for(int j = 0; j < virtualMap->cols && sscanf(temp, "%d %n", &value, &lineSize) > 0; j++){
      switch (value){
        case ROCK:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 3*16, 16*16, 16, 16, "loadin rock"),
            0,
            16,
            16,
            1,
            ROCK,
            true,
            true,
            true,
            false,
            "init rock"
          );
          
          break;
        case WALL:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 0*16, 8*16, 16, 16, "loding wall"),
            0,
            16,
            16,
            0,
            WALL,
            true,
            true,
            false,
            false,
            "init wall"
          );
          break;

        case SAND:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 1*16, 8*16, 16, 16, "loading sand"),
            10,
            16,
            16,
            0,
            SAND,
            true,
            false,
            false,
            false,
            "init sand"
          );
          break;
        case PLAYER:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            NULL,
            10,
            16,
            16,
            0,
            PLAYER,
            true,
            false,
            false,
            false,
            "init player"
          );
          break;
        case DIAMOND:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 4*16, 9*16, 16, 16, "loading diamond"),
            1000,
            16,
            16,
            0,
            DIAMOND,
            true,
            false,
            false,
            false,
            "init diamond"
          );
        case EMPTY:
        default:
          break;
      }      
      temp += lineSize;
    }
    free(line);
  }
  fclose(codedMap);

  return virtualMap;
}

Map* mapConstructor(Display* display){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, 16, 16, "background");
  map->width = display->bufferWidth / 16;
  map->height = display->bufferHeight / 16;
  map->virtualMap = initVirtualMap(map);

  return map;
}

void mapDestructor(Map* map){
  if(!map) return;

  spriteDestructor(map->background);
  sheetDestructor(map->_sheet);
  objArrDestructor(map->virtualMap);

  free(map);
}

Point getPlayerPos(Map* map){
  ObjectArr* virtualMap = map->virtualMap;
  Point point;
  point.x = point.y = 1;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target || !target->visible || target->type != PLAYER) continue;

    point.x = target->pos.x * 16;
    point.y = target->pos.y * 16;
  }

  return point;
}

void setPlayerPos(Map* map, Point playerPos){
  ObjectArr* virtualMap = map->virtualMap;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target || !target->visible || target->type != PLAYER) continue;

    target->pos.x = playerPos.x / 16;
    target->pos.y = playerPos.y /16;
  }

}

Object* objectInPos(ObjectArr* virtualMap, int x, int y){
  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i * virtualMap->cols + j];
      if(!target || !target->visible) continue;

      if(target->pos.x == x && target->pos.y == y) return target;      
    }
  }
  return NULL;
}

void objectFall(Object* target, Map* map){
  ObjectArr* virtualMap = map->virtualMap;

  if(objectInPos(virtualMap, target->pos.x, target->pos.y + 1)) {
    target->state = IDLE;
    return;
  }
  
  target->state = FALLING;
  target->pos.y += target->speed;
}

bool objectInPosIsFalling(ObjectArr* virtualMap, int x, int y){
  Object* target = objectInPos(virtualMap, x, y);
  return target && target->state == FALLING;
}

bool canRoll(Object* target, ObjectArr* virtualMap){
  Object* objUnder = objectInPos(virtualMap, target->pos.x, target->pos.y + 1);
  if(!objUnder) return false;
  if(
    objUnder->type != ROCK 
    && objUnder->type != WALL 
    && objUnder->type != DIAMOND
  ) return false;

  return true;
}

bool objectRoll(Object* target, Map* map){
  ObjectArr* virtualMap = map->virtualMap;

  if(!canRoll(target, virtualMap)) return false;

  Object* objRight = objectInPos(virtualMap, target->pos.x + 1, target->pos.y);
  Object* objDownRight = objectInPos(virtualMap, target->pos.x + 1, target->pos.y + 1);
  Object* objLeft = objectInPos(virtualMap, target->pos.x - 1, target->pos.y);
  Object* objDownLeft = objectInPos(virtualMap, target->pos.x - 1, target->pos.y + 1);

  if(!objLeft && !objDownLeft){
    target->pos.x -= target->speed;
    return true;
  } 
  else if(!objRight && !objDownRight){
    target->pos.x += target->speed;
    return true;
  } 
  

  return false;
}

void updateRock(Object* rock, long int frames, Map* map){
  if(frames % 7 != 0) return;
  bool rolled = objectRoll(rock, map);
  if(rolled) return;

  objectFall(rock, map);
}

void updateMapObjects(Map* map, long int frames){
  ObjectArr* virtualMap = map->virtualMap;
  sortObjArr(virtualMap);
  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target) continue;

      switch (target->type){
        case ROCK:
          updateRock(target, frames, map);
          break;
        
        case EMPTY:
        default:
          break;
      }

    }
  }
}

void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames){
  if(!map) return;

  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      updateMapObjects(map, frames);
      break;
    default:
      break;
  }
}

void drawBackground(Sprite* background, Display* display){
  for(int i = 0; i < display->bufferHeight; i += background->height){
    for(int j = 0; j < display->bufferWidth; j += background->width){
      al_draw_bitmap(background->bitmap, j, i, 0);
    }
  }
}

void drawVirtualMap(Map* map, Display* display){
  ObjectArr* virtualMap = map->virtualMap;

  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target || !target->visible) continue;

      switch(target->type){
        case PLAYER:
          break;
        default: 
          al_draw_bitmap(
            target->_sprite->bitmap,
            target->pos.x*16,
            target->pos.y*16, 
            0
          ); 
      }
    }
  }
  
  return;
}


void mapDraw(Map* map, Display* display){
  if(!map) return;

  drawBackground(map->background, display);
  drawVirtualMap(map, display);
  
}