// Made by Gabriel Lüders
// GRR20190172 

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
      true,
      false,
      true,
      false,
      "rocky rock"
    );
  }
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
      10,
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

Map* mapConstructor(){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, 16, 16, "background");
  map->rocks = objArrConstructor(5, "failed to malloc rocks");
  map->sand = objArrConstructor(5, "failed to malloc sand");
  map->walls = objArrConstructor(5, "failed to malloc walls");
  map->diamonds = objArrConstructor(5, "failed to malloc diamonds");

  rocksInit(map->rocks, map->_sheet);
  sandInit(map->sand, map->_sheet);
  diamondsInit(map->diamonds, map->_sheet);

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

void mapUpdate(Map* map, ALLEGRO_EVENT* event){
  if(!map) return;
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
    if(!objArr->objects[i]) continue;
    al_draw_bitmap(
      objArr->objects[i]->_sprite->bitmap,
      objArr->objects[i]->pos.x, 
      objArr->objects[i]->pos.y, 
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
  
}