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
#include "input.h"
#include "game.h"

int main(void){
	checkAllegroComponent(al_init(), "allegro");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
	checkAllegroComponent(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	checkAllegroComponent(queue, "queue");

	// TODO: move this into a hud lib
	ALLEGRO_FONT* font = al_create_builtin_font();
	checkAllegroComponent(font, "font");

	displayInit();
	keyboardInit();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(mainDisplay));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;
	
	for(al_start_timer(timer);;){
		al_wait_for_event(queue, &event);

		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
				if(virtualKeyboard[ALLEGRO_KEY_ESCAPE] || virtualKeyboard[ALLEGRO_KEY_Q])
					done = true;

				redraw = true;
				frames++;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				frames++;
				break;
		}

		if(done) break;

		keyboardUpdate(&event);

		if(redraw && al_is_event_queue_empty(queue)){
			selectBitmapBuffer();
			al_clear_to_color(al_map_rgb(0,0,0));

			flipDisplay();
			redraw = false;	
		}
	}

	displayFree();

  return 0;
}