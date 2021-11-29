// Made by Gabriel Lüders
// GRR20190172

#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "utils.h"

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

typedef struct SOUND_EFFECT{
  ALLEGRO_SAMPLE* soundEffect;
  ALLEGRO_SAMPLE_INSTANCE* instance;
}SoundEffect;

typedef struct AUDIO_MANAGER{
  SoundEffect* sounds;
  int length;
}AudioManager;


AudioManager* audioManagerConstructor();

void audioManagerDestructor(AudioManager* manager);

void playMusic(AudioManager* audioManager, Sounds soundIndex);

void playEffect(AudioManager* audioManager, Sounds soundIndex);

#endif