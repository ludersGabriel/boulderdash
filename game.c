// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
  al_install_audio();
  al_init_acodec_addon();  

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

void countTime(int* time, int frames, Player* player){
  if(frames % 60 != 0) return;

  *time -= 1;
  if(*time) return;

  player->alive = false;
  player->death_timer = PLAYER_DEATH_TIMER;
}

Game* gameConstructor(){
  Game* game = mallocSpace(sizeof(Game), "game pointer null");

  allegroInit(game);

  game->frames = 0;
  game->score = 0;
  game->redraw = true;
  game->map = mapConstructor(game->display);
  game->timeAvailabe = game->map->maxTime;
  game->player = playerConstructor(game->map);
  game->state = PLAYING; 
  game->audioManager = audioManagerConstructor();
  playMusic(game->audioManager, MUSIC);

  FILE* rankFile = fopen(RANK_PATH, "r");
  if(!rankFile){
    fprintf(stderr, "Failed to ranking from file\n");
    exit(1);
  } 

  for(int i = 0; i < RANKING_SIZE; i++)
    game->ranking[i] = 0;
  

  char* line;
  for(int i = 0; i < RANKING_SIZE && fscanf(rankFile, "%m[^\n]", &line) > 0; i++){
    fgetc(rankFile);
    
    game->ranking[i] = atoi(line);
    free(line);
  }

  fclose(rankFile);

  return game;    
}

void gameDestructor(Game* game){
  if(!game) return;
  
  mapDestructor(game->map);
  playerDestructor(game->player);
  displayDestructor(game->display);
  audioManagerDestructor(game->audioManager);
  al_destroy_event_queue(game->queue);
  al_destroy_timer(game->timer);
  al_destroy_font(game->font);

  free(game);
}

void resetLevel(Game* game){
  Player* player = game->player;
  if(player->alive && game->timeAvailabe != -1) return;

  if(player->death_timer){
    player->death_timer--;
    return;
  }

  ObjectArr* virtualMap = game->map->virtualMap;
  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target) continue;

    target->visible = true;
    target->state = IDLE;
    target->pos = target->initialPos;

    if(target->type == DIAMOND)
      target->score = game->map->diamondValue;
  }

  player->currentPos = player->startPos;
  player->alive = true;
  player->diamondHeld = 0;
  player->scoreMultiplier = 1;
  game->timeAvailabe = game->map->maxTime;
  player->death_timer = 0;
}

void gameUpdate(Game* game){
  ALLEGRO_EVENT* event = &game->event;
  
  if(!game || !event) return;

  resetLevel(game);

  if(!game->player->alive) return;

  playerUpdate(
    game->player, 
    event, 
    game->map,
    &game->score,
    (int*) &game->state,
    game->audioManager
  );
  countTime(&game->timeAvailabe, game->frames, game->player);
  mapUpdate(game->map, event, game->frames);
}

void endScreen(Game* game){
  al_wait_for_event(game->queue, &game->event);

  switch(game->event.type){
    case ALLEGRO_EVENT_KEY_DOWN:
      game->state = QUIT;

      FILE* rankFile = fopen(RANK_PATH, "w");
      if(!rankFile){
        fprintf(stderr, "Failed to ranking from file\n");
        exit(1);
      }

      for(int i = 0; i < RANKING_SIZE; i++)
        fprintf(rankFile,"%d\n", game->ranking[i]);
      
      fclose(rankFile);
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      game->state = QUIT;
      break;
  }

  if(al_is_event_queue_empty(game->queue)){
    selectBitmapBuffer(game->display);
    al_clear_to_color(al_map_rgb(0,0,0));

    drawEndScreen(game->ranking, RANKING_SIZE, game->font);

    flipDisplay(game->display);
  }
}

void gameDraw(Game* game){
  if(!game) return;

  mapDraw(game->map, game->display, game->frames);
  playerDraw(game->player, game->frames);
  drawHud(
    game->score, 
    game->map->necessaryDiamonds, 
    game->player->diamondHeld,
    game->map->diamondValue * game->player->scoreMultiplier, 
    game->timeAvailabe, 
    game->font
  );
}

void endInit(Game* game){
  int smallerIndex = indexOfSmallest(game->ranking, RANKING_SIZE);
  if(game->score > game->ranking[smallerIndex])
    game->ranking[smallerIndex] = game->score;
  
  sortArray(game->ranking, RANKING_SIZE);
  al_stop_sample_instance(game->audioManager->sounds[MUSIC].instance);
  game->state = END;
}

void playGame(Game* game){
  al_wait_for_event(game->queue, &game->event);

  switch(game->event.type){
    case ALLEGRO_EVENT_TIMER:
      if(virtualKeyboard[ALLEGRO_KEY_ESCAPE] || virtualKeyboard[ALLEGRO_KEY_Q]){
        game->state = END_INIT;
      }

      game->redraw = true;
      game->frames++;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      game->state = END_INIT;
      break;
  }

  if(game->state == END_INIT) return;

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