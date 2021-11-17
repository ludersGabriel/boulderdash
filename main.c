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

	for(al_start_timer(game->timer); game->state != quit;){
		switch(game->state){
			case playing: 
				playGame(game);
				break;
			case quit:
			default:
				break;
		}
	}

	gameDestructor(game);

  return 0;
}