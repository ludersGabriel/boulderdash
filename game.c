// Made by Gabriel Lüders
// GRR20190172

#include "game.h"
#include "sprite.h"
#include "utils.h"

Game* gameConstructor(ALLEGRO_BITMAP* mapSheet){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");;
  
  game->frames = 0;
  game->score = 0;
  game->map = mapConstructor();

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;

  mapDestructor(game->map);

  free(game);
}

void gameUpdate(Game* game, ALLEGRO_EVENT* event){
  if(!game) return;
}