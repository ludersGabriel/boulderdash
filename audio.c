// Made by Gabriel Lüders
// GRR20190172

#include "audio.h"

AudioManager* audioManagerConstructor(){
  al_reserve_samples(SOUND_AMOUNT);

  AudioManager* manager = mallocSpace(sizeof(AudioManager), "audio manager pointer null");
  manager->length = SOUND_AMOUNT;
  manager->sounds = mallocSpace(sizeof(SoundEffect) * manager->length, "sound effects pointer null");

  SoundEffect* sounds = manager->sounds;

  for(int i = 0; i < manager->length; i++){
    sounds[i].soundEffect = NULL;
    sounds[i].instance = NULL;
  }

  sounds[DEATH_SOUND].soundEffect 
    = al_load_sample("./resources/soundEffects/hit3.ogg");
  
  sounds[SAND_SOUND].soundEffect 
    = al_load_sample("./resources/soundEffects/sand4.ogg");

  sounds[DIAMOND_SOUND].soundEffect 
    = al_load_sample("./resources/soundEffects/orb.ogg");

  sounds[DIAMOND_LEVELUP].soundEffect 
    = al_load_sample("./resources/soundEffects/levelup.ogg");

  sounds[FIREWORK].soundEffect 
    = al_load_sample("./resources/soundEffects/launch1.ogg");

  sounds[MUSIC].soundEffect 
    = al_load_sample("./resources/music/piano1.ogg");
  sounds[MUSIC].instance 
    = al_create_sample_instance(sounds[MUSIC].soundEffect);
  al_set_sample_instance_playmode(sounds[MUSIC].instance, ALLEGRO_PLAYMODE_LOOP);
  al_attach_sample_instance_to_mixer(sounds[MUSIC].instance, al_get_default_mixer());


  return manager;
}

void playEffect(AudioManager* audioManager, Sounds soundIndex){
  SoundEffect* sounds = audioManager->sounds;
  
  al_play_sample(sounds[soundIndex].soundEffect, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

void playMusic(AudioManager* audioManager, Sounds soundIndex){
  SoundEffect* sounds = audioManager->sounds;
  al_play_sample_instance(sounds[soundIndex].instance);

}
void audioManagerDestructor(AudioManager* manager){
  SoundEffect* sounds = manager->sounds;
  for(int i = 0; i < manager->length; i++){
    if(sounds[i].instance)
      al_destroy_sample_instance(sounds[i].instance);

    if(sounds[i].soundEffect)
      al_destroy_sample(sounds[i].soundEffect);
  }

  free(sounds);
  free(manager);
}