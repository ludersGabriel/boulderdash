// Made by Gabriel Lüders
// GRR20190172 

#include <stdio.h>
#include "map.h"
#include "sprite.h"
#include "utils.h"
#include "display.h"

void rocksInit(ObjectArr* rocks, ALLEGRO_BITMAP* sheet){
  for(int i = 0; i < rocks->length; i++){
    rocks->objects[i] = objectConstructor(
      16*15,
      16*(i+5),
      spriteConstructor(sheet, 3*16, 16*16, 16, 16, "loadin rock"),
      0,
      16,
      16,
      16,
      true,
      true,
      true,
      false,
      "rocky rock"
    );
  }

  sortObjArr(rocks);
}

void sandInit(ObjectArr* sand, ALLEGRO_BITMAP* sheet){
  for(int i = 0; i < sand->length; i++){
    sand->objects[i] = objectConstructor(
      16*(13+i),
      16*10,
      spriteConstructor(sheet, 1*16, 8*16, 16, 16, "loading sand"),
      10,
      16,
      16,
      0,
      true,
      false,
      true,
      false,
      "sandy sand"
    );
  }
}

void diamondsInit(ObjectArr* diamonds, ALLEGRO_BITMAP* sheet){
  for(int i = 0; i < diamonds->length; i++){
    diamonds->objects[i] = objectConstructor(
      16*(13+i),
      16*15,
      spriteConstructor(sheet, 4*16, 8*16, 16, 16, "diamonds"),
      1000,
      16,
      16,
      16,
      true,
      false,
      true,
      false,
      "diamooond"
    );
  }
}

void wallsInit(ObjectArr* walls, ALLEGRO_BITMAP* sheet, Map* map){
  int k = 0;
  for(int i = 0; i < map->height; i += map->height - 1){
    for(int j = 0; j < map->width; j += 1){
      if(k > walls->length) break;

      walls->objects[k++] = objectConstructor(
        16*j,
        16*i,
        spriteConstructor(sheet, 0*16, 8*16, 16, 16, "walls"),
        1000,
        16,
        16,
        0,
        true,
        true,
        true,
        false,
        "wallls"
      );
    }
  }

  for(int i = 0; i < map->width; i += map->width - 1){
    for(int j = 0; j < map->height; j += 1){
      if(k > walls->length) break;

      walls->objects[k++] = objectConstructor(
        16*i,
        16*j,
        spriteConstructor(sheet, 0*16, 8*16, 16, 16, "walls"),
        1000,
        16,
        16,
        0,
        true,
        true,
        true,
        false,
        "wallls"
      );
    }
  }
}

Map* mapConstructor(Display* display){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, 16, 16, "background");
  map->width = display->bufferWidth / 16;
  map->height = display->bufferHeight / 16;
  map->rocks = objArrConstructor(5, "failed to malloc rocks");
  map->sand = objArrConstructor(5, "failed to malloc sand");
  map->walls = objArrConstructor(5, "failed to malloc walls");
  map->diamonds = objArrConstructor(5, "failed to malloc diamonds");
  map->walls = objArrConstructor(
    map->width*2 + map->height*2, 
    "failed to malloc walls"
  );


  rocksInit(map->rocks, map->_sheet);
  sandInit(map->sand, map->_sheet);
  diamondsInit(map->diamonds, map->_sheet);
  wallsInit(map->walls, map->_sheet, map);

  return map;
}

void mapDestructor(Map* map){
  if(!map) return;

  objArrDestructor(map->rocks);
  objArrDestructor(map->sand);
  objArrDestructor(map->walls);
  spriteDestructor(map->background);
  sheetDestructor(map->_sheet);
  free(map);
}

void rockHeights(ObjectArr* rocks){
  Object** target = rocks->objects;
  for(int i = 0; i < rocks->length; i++){
    if(!target[i]) continue;
    printf("rock height: %d\n", target[i]->pos.y);
  }
  printf("\n\n");
}

void updateRocks(ObjectArr* rocks, long int frames, Map* map){
  if(frames % 45 != 0) return;

  Object** target = rocks->objects;
  for(int i = 0; i < rocks->length; i++){
    if(!target[i]) continue;

    Point oldPos = target[i]->pos;
    target[i]->pos.y += target[i]->speed;
    handleCollisionObjects(target[i], oldPos, map->sand);
    handleCollisionObjects(target[i], oldPos, map->diamonds);
    handleCollisionObjects(target[i], oldPos, map->walls);
    handleCollisionObjects(target[i], oldPos, map->rocks);
  }
}

void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames){
  if(!map) return;

  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      updateRocks(map->rocks, frames, map);
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

void drawObjArr(ObjectArr* objArr, Display* display){
  for(int i = 0; i < objArr->length; i++){
    Object* target = objArr->objects[i];
    if(!target || !target->visible) continue;
    al_draw_bitmap(
      target->_sprite->bitmap,
      target->pos.x, 
      target->pos.y, 
      0
    );
  }
}

void mapDraw(Map* map, Display* display){
  if(!map) return;

  drawBackground(map->background, display);
  drawObjArr(map->rocks, display);
  drawObjArr(map->sand, display);
  drawObjArr(map->diamonds, display);
  drawObjArr(map->walls, display);
  
}