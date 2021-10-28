// Made by Gabriel Lüders
// GRR20190172 

#include "map.h"
#include "sprite.h"
#include "utils.h"
#include "display.h"

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

void mapUpdate(Map* map, ALLEGRO_EVENT* event){
  if(!map) return;
}

void mapDraw(Map* map){
  if(!map) return;

  for(int i = 0; i < BUFFER_HEIGHT; i += 16){
    for(int j = 0; j < BUFFER_WIDTH; j += 16){
      al_draw_bitmap(map->background, j, i, 0);
    }
  }
}