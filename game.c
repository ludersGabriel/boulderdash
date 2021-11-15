// Made by Gabriel Lüders
// GRR20190172

#include "game.h"
#include "sprite.h"
#include "utils.h"
#include "player.h"
#include "display.h"


Game* gameConstructor(){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");
  
  game->frames = 0;
  game->score = 0;
  game->display = displayConstructor();
  game->map = mapConstructor(game->display);
  game->player = playerConstructor(game->display);
  

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;
  
  mapDestructor(game->map);
  playerDestructor(game->player);
  displayDestructor(game->display);

  free(game);
}

void gameUpdate(Game* game, ALLEGRO_EVENT* event){
  if(!game || !event) return;

  mapUpdate(game->map, event, game->frames);
  playerUpdate(
    game->player, 
    event, 
    game->display, 
    game->map,
    &game->score
  );
}

void scoreDraw(int score, ALLEGRO_FONT* font){
  al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Score: %d", score);
}

void gameDraw(Game* game, ALLEGRO_FONT* font){
  if(!game) return;

  mapDraw(game->map, game->display);
  playerDraw(game->player);
  scoreDraw(game->score, font);
}