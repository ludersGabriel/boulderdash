// Made by Gabriel Lüders
// GRR20190172

#include "game.h"
#include "sprite.h"
#include "utils.h"
#include "player.h"
#include "display.h"

void allegroInit(Game* game){
	checkAllegroComponent(al_init(), "allegro");

	displayInit();
	keyboardInit();
	spriteSystemInit();

  game->timer = al_create_timer(1.0 / 60);
	checkAllegroComponent(game->timer, "timer");

	game->queue = al_create_event_queue();
	checkAllegroComponent(game->queue, "queue");

	game->font = al_create_builtin_font();
	checkAllegroComponent(game->font, "font");

  game->display = displayConstructor();

  al_register_event_source(game->queue, al_get_keyboard_event_source());
	al_register_event_source(game->queue, al_get_display_event_source(game->display->mainDisplay));
	al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

}

Game* gameConstructor(){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");

  allegroInit(game);

  game->frames = 0;
  game->score = 0;
  game->redraw = true;
  game->map = mapConstructor(game->display);
  game->player = playerConstructor(game->map);
  game->state = playing;  

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;
  
  mapDestructor(game->map);
  playerDestructor(game->player);
  displayDestructor(game->display);

  free(game);
}

void gameUpdate(Game* game){
  ALLEGRO_EVENT* event = &game->event;
  
  if(!game || !event) return;

  playerUpdate(
    game->player, 
    event, 
    game->map,
    &game->score
  );
  mapUpdate(game->map, event, game->frames, game->player->currentPos);
}

void scoreDraw(int score, ALLEGRO_FONT* font){
  al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Score: %d", score);
}

void gameDraw(Game* game){
  if(!game) return;

  mapDraw(game->map, game->display);
  playerDraw(game->player);
  scoreDraw(game->score, game->font);
}

void playGame(Game* game){
  al_wait_for_event(game->queue, &game->event);

		switch(game->event.type){
			case ALLEGRO_EVENT_TIMER:
				if(virtualKeyboard[ALLEGRO_KEY_ESCAPE] || virtualKeyboard[ALLEGRO_KEY_Q])
					game->state = quit;

				game->redraw = true;
				game->frames++;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				game->state = quit;
				break;
		}

		if(game->state == quit) return;

		gameUpdate(game);
		keyboardUpdate(&game->event);

		if(game->redraw && al_is_event_queue_empty(game->queue)){
			selectBitmapBuffer(game->display);
			al_clear_to_color(al_map_rgb(0,0,0));

			gameDraw(game);

			flipDisplay(game->display);
			game->redraw = false;	
		}
}