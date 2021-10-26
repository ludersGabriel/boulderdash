#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>

#define KEY_SEEN     1
#define KEY_RELEASED 2

extern unsigned char virtualKeyboard[ALLEGRO_KEY_MAX];

void keyboardInit();

void keyboardUpdate(ALLEGRO_EVENT* event);

#endif