// Made by Gabriel Lüders
// GRR20190172 

#include "map.h"
#include "sprite.h"
#include "utils.h"

Map* mapConstructor(){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("mapSheet.png");
  map->background = loadSprite(map->_sheet, 32, 128, 16, 16);


  return map;
}

void mapDestructor(Map* map){
  if(!map) return;

  al_destroy_bitmap(map->background);
  al_destroy_bitmap(map->_sheet);
  free(map);
}

void mapUpdate(Map* map){
  
}