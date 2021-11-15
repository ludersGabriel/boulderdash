// Made by Gabriel Lüders
// GRR20190172

#include <allegro5/allegro5.h>

#ifndef UTILS_H
#define UTILS_H

typedef struct POINT{
  int x;
  int y;
}Point;

void* mallocSpace(int size, const char* desc);

void checkAllegroComponent(bool component, const char* desc);

#endif