// Made by Gabriel Lüders
// GRR20190172

#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "utils.h"

// enum that represents all the sounds the manager can play
typedef enum{
  DEATH_SOUND,
  SAND_SOUND,
  DIAMOND_SOUND,
  MUSIC,
  DIAMOND_LEVELUP,
  FIREWORK,
  ROCK_TUMP,
  SOUND_AMOUNT
}Sounds;

// struct that represents a sound effect or music
typedef struct SOUND_EFFECT{
  ALLEGRO_SAMPLE* soundEffect;
  ALLEGRO_SAMPLE_INSTANCE* instance;
}SoundEffect;

// struct that represents my sound manager
typedef struct AUDIO_MANAGER{
  SoundEffect* sounds;
  int length;
}AudioManager;


// creates and initializes a audio manager, returning it
AudioManager* audioManagerConstructor();

// destroys a given audio manager
void audioManagerDestructor(AudioManager* manager);

// plays a music at the given index
void playMusic(AudioManager* audioManager, Sounds soundIndex);

// plays a sound effect at the given index
void playEffect(AudioManager* audioManager, Sounds soundIndex);

#endif