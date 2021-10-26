#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

void mustInit(bool test, const char* description){
	if(test) return;

	fprintf(stderr, "Error initializing %s\n", description);
	exit(1);
}

int main(){
	mustInit(al_init(), "allegro");
	mustInit(al_install_keyboard(), "keyboard");
	mustInit(al_init_primitives_addon(), "primitives");
	mustInit(al_install_mouse(), "mouse");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	mustInit(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	mustInit(queue, "queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	ALLEGRO_DISPLAY* disp = al_create_display(1600, 900);
	mustInit(disp, "display");

	ALLEGRO_FONT* font = al_create_builtin_font();
	mustInit(font, "fonts");

	
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_hide_mouse_cursor(disp);
	al_grab_mouse(disp);

	bool redraw = true;
	bool done = false;
	ALLEGRO_EVENT event;

	float x, y;
	x = y = 100;

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	for(al_start_timer(timer);;){
		al_wait_for_event(queue, &event);

		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
				// game logic goes here
				if(key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_W]) y--;
				if(key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_S]) y++;
				if(key[ALLEGRO_KEY_RIGHT] || key[ALLEGRO_KEY_D]) x++;
				if(key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_A]) x--;

				if(key[ALLEGRO_KEY_ESCAPE]) done = true;

				for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
					key[i] &= KEY_SEEN;

				// end of game logic
				redraw = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				break;
		}

		if(done) break;

		if(redraw && al_is_event_queue_empty(queue)){
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// render space
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "(x, y): (%.1f, %.1f)", x, y);
			al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
			// end of render space

			al_flip_display();
			redraw = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}

