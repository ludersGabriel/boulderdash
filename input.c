// Made by Gabriel Lüders
// GRR20190172

#include "input.h"
#include "utils.h"

// global variable that represents the virtual keyboard
unsigned char virtualKeyboard[ALLEGRO_KEY_MAX];

// initializes allegro keyboard system
void keyboardInit(){
  checkAllegroComponent(al_install_keyboard(), "keyboard");

  memset(virtualKeyboard, 0, sizeof(virtualKeyboard));
}

// updates the state of the virtual keys
void keyboardUpdate(ALLEGRO_EVENT* event){
  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
        virtualKeyboard[i] &= KEY_SEEN;
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      virtualKeyboard[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
      break;
    case ALLEGRO_EVENT_KEY_UP:
      virtualKeyboard[event->keyboard.keycode] &= KEY_RELEASED;
      break;
  }
}