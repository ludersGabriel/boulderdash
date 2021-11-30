#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro5.h>

#define KEY_SEEN     1
#define KEY_RELEASED 2

// global variable that represents the virtual keyboard
extern unsigned char virtualKeyboard[ALLEGRO_KEY_MAX];

// initializes allegro keyboard system
void keyboardInit();

// updates the state of the virtual keys
void keyboardUpdate(ALLEGRO_EVENT* event);

#endif