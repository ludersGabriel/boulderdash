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
        case rock:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 3*16, 16*16, 16, 16, "loadin rock"),
            0,
            16,
            16,
            1,
            rock,
            true,
            true,
            true,
            false,
            "init rock"
          );
          
          break;
        case wall:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 0*16, 8*16, 16, 16, "loding wall"),
            0,
            16,
            16,
            0,
            wall,
            true,
            true,
            false,
            false,
            "init wall"
          );
          break;

        case sand:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 1*16, 8*16, 16, 16, "loading sand"),
            10,
            16,
            16,
            0,
            sand,
            true,
            false,
            false,
            false,
            "init sand"
          );
          break;
        case diamond:
          virtualMap->objects[i*virtualMap->cols + j] = objectConstructor(
            j,
            i,
            spriteConstructor(map->_sheet, 4*16, 9*16, 16, 16, "loading diamond"),
            1000,
            16,
            16,
            0,
            sand,
            true,
            false,
            false,
            false,
            "init diamond"
          );
        case empty:
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

Map* mapConstructor(Display* display, Point playerPos){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, 16, 16, "background");
  map->width = display->bufferWidth / 16;
  map->height = display->bufferHeight / 16;
  map->virtualMap = initVirtualMap(map);
  map->playerPos.x = playerPos.x / 16;
  map->playerPos.y = playerPos.y / 16;

  return map;
}

void mapDestructor(Map* map){
  if(!map) return;

  spriteDestructor(map->background);
  sheetDestructor(map->_sheet);
  objArrDestructor(map->virtualMap);

  free(map);
}

void rockFall(ObjectArr* rocks){
  for(int i = 0; i < rocks->length; i++){
    Object* rock = rocks->objects[i];
    if(!rock) continue;

    rock->pos.y += rock->speed;
  }
}

void updateRocks(ObjectArr* rocks, long int frames, Map* map){
  if(frames % 45 != 0) return;
  rockFall(rocks);
}

void updateMapObjects(ObjectArr* virtualMap, long int frames){
  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target) continue;

      switch (target->type){
        case rock:
          break;
        
        case empty:
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
      printf("player pos in map: (%d,%d)\n", map->playerPos.x, map->playerPos.y);
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