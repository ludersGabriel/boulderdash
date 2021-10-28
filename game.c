// Made by Gabriel Lüders
// GRR20190172

#include "game.h"
#include "sprite.h"
#include "utils.h"
#include "player.h"

Game* gameConstructor(ALLEGRO_BITMAP* mapSheet){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");
  
  game->frames = 0;
  game->score = 0;
  game->map = mapConstructor();
  game->player = playerConstructor();

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;

  mapDestructor(game->map);
  playerDestructor(game->player);

  free(game);
}

void gameUpdate(Game* game, ALLEGRO_EVENT* event){
  if(!game || !event) return;

  mapUpdate(game->map, event);
  playerUpdate(game->player, event);
}

void gameDraw(Game* game){
  if(!game) return;

  mapDraw(game->map);
  playerDraw(game->player);
}