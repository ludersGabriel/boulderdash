// Made by Gabriel Lüders
// GRR20190172

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "utils.h"
#include "display.h"
#include "game.h"
#include "map.h"
#include "sprite.h"

int main(void){
	Game* game = gameConstructor();

	for(al_start_timer(game->timer); game->state != QUIT;){
		switch(game->state){
			case START:
				startScreen(game);
				break;
			case PLAYING: 
				playGame(game);
				break;
			case HELP:
				helpScreen(game);
				break;
			case END_INIT:
				endInit(game);
				break;
			case END:
				endScreen(game);
				break;
			case QUIT:
			default:
				break;
		}
	}

	gameDestructor(game);

  return 0;
}