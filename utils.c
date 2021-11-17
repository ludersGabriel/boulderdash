// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "utils.h"

void checkAllegroComponent(bool component, const char* desc){
  if(component) 
    return;
  
  fprintf(stderr, "Error initializing %s\n", desc);
}

void* mallocSpace(int size, const char* desc){
  void* pointer = malloc(size);
  if(!pointer){
    fprintf(stderr, "Error allocating memory: %s\n", desc);
    exit(2);
  }

  return pointer;
}

bool comparePoints(Point a, Point b){
  return a.x == b.x && a.y == b.y;
}