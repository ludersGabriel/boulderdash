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

int indexOfSmallest(int* arr, int length){
  if(!arr) return -1;
  
  int smaller = 0;
  for(int i = 1; i < length; i++){
    if(arr[i] < arr[smaller])
      smaller = i;
  }

  return smaller;
}

void sortArray(int* arr, int length){
  int i, j, maxIndex;
 
  for (i = 0; i < length-1; i++){
    maxIndex = i;
    for (j = i+1; j < length; j++)
      if (arr[j] > arr[maxIndex])
        maxIndex = j;

    int aux = arr[i];
    arr[i] = arr[maxIndex];
    arr[maxIndex] = aux;
  }

}