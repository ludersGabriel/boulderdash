// Made by Gabriel Lüders
// GRR20190172

#include "game.h"
#include "sprite.h"
#include "utils.h"
#include "player.h"
#include "display.h"


Game* gameConstructor(ALLEGRO_BITMAP* mapSheet){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");
  
  game->frames = 0;
  game->score = 0;
  game->display = displayConstructor();
  game->map = mapConstructor();
  game->player = playerConstructor(game->display);
  game->rocks = objArrConstructor(5, "failed to malloc rocks");
  game->sand = objArrConstructor(5, "failed to malloc sand");
  game->walls = objArrConstructor(5, "failed to malloc walls");

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;

  objArrDestructor(game->rocks);
  objArrDestructor(game->sand);
  objArrDestructor(game->walls);
  mapDestructor(game->map);
  playerDestructor(game->player);
  displayDestructor(game->display);

  free(game);
}

void gameUpdate(Game* game, ALLEGRO_EVENT* event){
  if(!game || !event) return;

  mapUpdate(game->map, event);
  playerUpdate(game->player, event, game->display);
}

void gameDraw(Game* game){
  if(!game) return;

  mapDraw(game->map, game->display);
  playerDraw(game->player);
}