// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "utils.h"

void checkAllegroComponent(bool component, const char* desc){
  if(component) 
    return;
  
  fprintf(stderr, "Error initializing %s\n", desc);
}