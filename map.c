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
          map->playerPos.x = j;
          map->playerPos.y = i;
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

void rockFall(Object* rock, ObjectArr* virtualMap){
  if(objectInPos(virtualMap, rock->pos.x, rock->pos.y + 1)) {
    rock->state = IDLE;
    return;
  }
  
  rock->state = FALLING;
  rock->pos.y += rock->speed;
}

bool objectInPosIsFalling(ObjectArr* virtualMap, int x, int y){
  Object* target = objectInPos(virtualMap, x, y);
  return target && target->state == FALLING;
}

bool canRoll(Object* rock, ObjectArr* virtualMap){
  Object* objUnder = objectInPos(virtualMap, rock->pos.x, rock->pos.y + 1);
  if(!objUnder) return false;
  if(
    objUnder->type != ROCK 
    && objUnder->type != WALL 
    && objUnder->type != DIAMOND
  ) return false;

  return true;
}

bool rockRoll(Object* rock, ObjectArr* virtualMap){
  if(!canRoll(rock, virtualMap)) return false;

  Object* objRight = objectInPos(virtualMap, rock->pos.x + 1, rock->pos.y);
  Object* objDownRight = objectInPos(virtualMap, rock->pos.x + 1, rock->pos.y + 1);
  Object* objLeft = objectInPos(virtualMap, rock->pos.x - 1, rock->pos.y);
  Object* objDownLeft = objectInPos(virtualMap, rock->pos.x - 1, rock->pos.y + 1);

  if(!objLeft && !objDownLeft){
    rock->pos.x -= rock->speed;
    return true;
  } 
  else if(!objRight && !objDownRight){
    rock->pos.x += rock->speed;
    return true;
  } 
  

  return false;
}

void updateRock(Object* rock, long int frames, ObjectArr* virtualMap){
  if(frames % 6 != 0) return;
  bool rolled = rockRoll(rock, virtualMap);
  if(rolled) return;

  rockFall(rock, virtualMap);
}

void updateMapObjects(ObjectArr* virtualMap, long int frames){
  sortObjArr(virtualMap);
  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target) continue;

      switch (target->type){
        case ROCK:
          updateRock(target, frames, virtualMap);
          break;
        
        case EMPTY:
        default:
          break;
      }

    }
  }
}

void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames, Point playerPos){
  if(!map) return;

  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      map->playerPos.x = playerPos.x / 16;
      map->playerPos.y = playerPos.y / 16;
      updateMapObjects(map->virtualMap, frames);
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

      al_draw_bitmap(
        target->_sprite->bitmap,
        target->pos.x*16,
        target->pos.y*16, 
        0
      ); 
    }
  }
  
  return;
}


void mapDraw(Map* map, Display* display){
  if(!map) return;

  drawBackground(map->background, display);
  drawVirtualMap(map, display);
  
}