// Made by Gabriel Lüders
// GRR20190172 

#include "map.h"
#include "sprite.h"
#include "utils.h"
#include "display.h"

Map* mapConstructor(){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, 16, 16, "background");

  return map;
}

void mapDestructor(Map* map){
  if(!map) return;

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

void mapDraw(Map* map, Display* display){
  if(!map) return;

  drawBackground(map->background, display);
  
}