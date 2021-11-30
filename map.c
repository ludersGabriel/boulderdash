// Made by Gabriel Lüders
// GRR20190172 

#include <stdio.h>
#include "map.h"
#include "sprite.h"
#include "utils.h"
#include "display.h"

// helper function that initializes the virtual map grid
ObjectArr* initVirtualMap(Map* map){
  // here its times 2 because of the easter egg
  int length = map->width * map->height * 2;
  ObjectArr* virtualMap = objArrConstructor(
    length, 
    map->width * 2, 
    map->height, 
    "error allocating virtual map"
  );
  for(int i = 0; i < virtualMap->length; i++)
    virtualMap->objects[i] = NULL;
  
  FILE* codedMap = fopen(MAP1_PATH, "r");
  if(!codedMap){
    fprintf(stderr, "Failed to load map from file\n");
    exit(1);
  }

  char aux[10];
  fgets(aux, 10, codedMap);
  map->necessaryDiamonds = atoi(aux);
  fgets(aux, 10, codedMap);
  map->diamondValue = atoi(aux);
  fgets(aux, 10, codedMap);
  map->maxTime = atoi(aux);

  char* line;
  int value;
  for(int i = 0; i < virtualMap->lines && fscanf(codedMap, "%m[^\n]", &line) > 0; i++){
    // deals with the \n
    fgetc(codedMap);

    char* temp = line;
    int lineSize;
    for(int j = 0; j < virtualMap->cols && sscanf(temp, "%d %n", &value, &lineSize) > 0; j++){
      switch (value){
        case ROCK:
          virtualMap->objects[i*virtualMap->cols + j] = rockInit(map->_sheet, j, i);
          break;
        case WALL:
          virtualMap->objects[i*virtualMap->cols + j] = wallInit(map->_sheet, j, i);
          break;
        case SAND:
          virtualMap->objects[i*virtualMap->cols + j] = sandInit(map->_sheet, j, i);
          break;
        case PLAYER:
          virtualMap->objects[i*virtualMap->cols + j] = playerInit(map->_sheet, j, i);
          break;
        case DIAMOND:
          virtualMap->objects[i*virtualMap->cols + j] = diamondInit(map->_sheet, map->diamondValue, j, i);
          break;
        case DOOR:
          virtualMap->objects[i*virtualMap->cols + j] = doorInit(map->_sheet, j, i);
          break;
        case FALSE_WALL:
          virtualMap->objects[i*virtualMap->cols + j] = falseWallInit(map->_sheet, j, i);
          break;
        case PINK_DIAMOND:
          virtualMap->objects[i*virtualMap->cols + j] = pinkDiamondInit(map->_sheet, map->diamondValue, j, i);
          break;
        case EMPTY:
        default:
          break;
      }      
      temp += lineSize;
    }
    free(line);
  }
  fclose(codedMap);

  return virtualMap;
}

// creates and initializes a map object, returning it
Map* mapConstructor(Display* display){
  Map* map = mallocSpace(sizeof(Map), "map pointer null");

  map->_sheet = loadSheet("./resources/mapSheet.png");
  map->background = spriteConstructor(map->_sheet, 32, 128, TILE_SIZE, TILE_SIZE, "background");
  map->width = display->bufferWidth / TILE_SIZE;
  map->height = display->bufferHeight / TILE_SIZE;
  map->virtualMap = initVirtualMap(map);

  return map;
}

// destroys a given map object
void mapDestructor(Map* map){
  if(!map) return;

  spriteDestructor(map->background);
  sheetDestructor(map->_sheet);
  objArrDestructor(map->virtualMap);

  free(map);
}

// gets the real player position from the map structure
Point getPlayerPos(Map* map){
  ObjectArr* virtualMap = map->virtualMap;
  Point point;
  point.x = point.y = 1;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target || !target->visible || target->type != PLAYER) continue;

    point.x = target->pos.x * TILE_SIZE;
    point.y = target->pos.y * TILE_SIZE;
  }

  return point;
}

// gets the player position directly in the map structure
Point getPaddedPlayerPos(Map* map){
  ObjectArr* virtualMap = map->virtualMap;
  Point point;
  point.x = point.y = 1;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target || !target->visible || target->type != PLAYER) continue;

    point.x = target->pos.x;
    point.y = target->pos.y;
  }

  return point;
}

// set the position of the dummy player object inside the map structure
void setPlayerPos(Map* map, Point playerPos){
  ObjectArr* virtualMap = map->virtualMap;

  for(int i = 0; i < virtualMap->length; i++){
    Object* target = virtualMap->objects[i];
    if(!target || !target->visible || target->type != PLAYER) continue;

    target->pos.x = playerPos.x / TILE_SIZE;
    target->pos.y = playerPos.y /TILE_SIZE;
  }

}

// checks if there is an ojbect at a given coordinate
Object* objectInPos(ObjectArr* virtualMap, int x, int y){
  for(int i = 0; i < virtualMap->length; i++){
      Object* target = virtualMap->objects[i];
      if(!target || !target->visible) continue;

      if(target->pos.x == x && target->pos.y == y) return target;   
  }
  
  return NULL;
}

// helper function that makes an object fall
void objectFall(Object* target, Map* map, AudioManager* audioManager){
  ObjectArr* virtualMap = map->virtualMap;

  Object* objUnder = objectInPos(virtualMap, target->pos.x, target->pos.y + 1);
  if(
    objUnder 
    && !(target->state == FALLING && objUnder->type == PLAYER)
  ) {
    if(!target->state == IDLE)
      playEffect(audioManager, ROCK_TUMP);
    target->state = IDLE;
    return;
  }
  
  target->state = FALLING;
  target->pos.y += target->speed;
}

// helper function that checks if a given object can roll
bool canRoll(Object* target, ObjectArr* virtualMap){
  Object* objUnder = objectInPos(virtualMap, target->pos.x, target->pos.y + 1);
  if(!objUnder) return false;
  if(
    objUnder->type != ROCK 
    && objUnder->type != WALL 
    && objUnder->type != DIAMOND
  ) return false;

  return true;
}

// helper function that rolls an object
bool objectRoll(Object* target, Map* map, AudioManager* audioManager){
  ObjectArr* virtualMap = map->virtualMap;

  if(!canRoll(target, virtualMap)) return false;

  Object* objRight = objectInPos(virtualMap, target->pos.x + 1, target->pos.y);
  Object* objDownRight = objectInPos(virtualMap, target->pos.x + 1, target->pos.y + 1);
  Object* objLeft = objectInPos(virtualMap, target->pos.x - 1, target->pos.y);
  Object* objDownLeft = objectInPos(virtualMap, target->pos.x - 1, target->pos.y + 1);

  if(
    (!objLeft && !objDownLeft )
    || (!objLeft && target->state == FALLING && objDownLeft->type == PLAYER)
  ){
    target->pos.x -= target->speed;
    if(target->state != IDLE)
      playEffect(audioManager, ROCK_TUMP);
    target->state = FALLING;
    return true;
  } 
  else if(
    (!objRight && !objDownRight)
    || (!objRight && target->state == FALLING && objDownRight->type == PLAYER)
  ){
    target->pos.x += target->speed;
    if(target->state != IDLE)
      playEffect(audioManager, ROCK_TUMP);
    target->state = FALLING;
    return true;
  } 
  

  return false;
}

// helper function that updaes rocks and diamonds (diamond is a particular rock)
void updateRock(Object* rock, long int frames, Map* map, AudioManager* audioManager){
  if(frames % 8 != 0) return;
  bool rolled = objectRoll(rock, map, audioManager);
  if(rolled) return;

  objectFall(rock, map, audioManager);
}

// loops through all objects on the virtual grid and updates them
void updateMapObjects(Map* map, long int frames, AudioManager* audioManager){
  ObjectArr* virtualMap = map->virtualMap;
  sortObjArr(virtualMap);
  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target || !target->visible) continue;

      switch (target->type){
        case DIAMOND:
        case ROCK:
          updateRock(target, frames, map, audioManager);
          break;
        case EMPTY:
        default:
          break;
      }
    }
  }
}

// responsible for update all map objects
void mapUpdate(Map* map, ALLEGRO_EVENT* event, long int frames, AudioManager* audioManager){
  if(!map) return;

  switch(event->type){
    case ALLEGRO_EVENT_TIMER:
      updateMapObjects(map, frames, audioManager);
      break;
    default:
      break;
  }
}

// draws the backgound
void drawBackground(Sprite* background, Display* display){
  for(int i = TILE_SIZE; i < display->bufferHeight; i += background->height){
    for(int j = 0; j < display->bufferWidth; j += background->width){
      al_draw_bitmap(background->bitmap, j, i, 0);
    }
  }
}


// helper function that draws the virtual map
void drawVirtualMap(Map* map, Display* display, int frames){
  ObjectArr* virtualMap = map->virtualMap;

  int offset = 0;

  Point playerPos = getPlayerPos(map);
  if(playerPos.x >= BUFFER_WIDTH)
    offset = - BUFFER_WIDTH;

  for(int i = 0; i < virtualMap->lines; i++){
    for(int j = 0; j < virtualMap->cols; j++){
      Object* target = virtualMap->objects[i*virtualMap->cols + j];
      if(!target || !target->visible) continue;

      Point unppadedPos;
      unppadedPos.x = target->pos.x * TILE_SIZE;
      unppadedPos.y = target->pos.y * TILE_SIZE;
      switch(target->type){
        case PLAYER:
          break;
        default: 
          if(target->anim){
            playAnimation(
              target->anim,
              &unppadedPos,
              frames,
              false,
              offset
            );
          }
          else
            al_draw_bitmap(
              target->_sprite->bitmap,
              target->pos.x*TILE_SIZE + offset,
              target->pos.y*TILE_SIZE, 
              0
            ); 
      }
    }
  }
  
  return;
}

// draws the map objects
void mapDraw(Map* map, Display* display, int frames){
  if(!map) return;

  drawVirtualMap(map, display, frames);
  
}