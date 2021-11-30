// Made by Gabriel Lüders
// GRR20190172

#include <stdio.h>
#include "utils.h"

// checks if an allegro component has been initialized
void checkAllegroComponent(bool component, const char* desc){
  if(component) 
    return;
  
  fprintf(stderr, "Error initializing %s\n", desc);
}

// helper function that mallocs a space and checks if it worked
void* mallocSpace(int size, const char* desc){
  void* pointer = malloc(size);
  if(!pointer){
    fprintf(stderr, "Error allocating memory: %s\n", desc);
    exit(2);
  }

  return pointer;
}

// compares if two points are at the same place
bool comparePoints(Point a, Point b){
  return a.x == b.x && a.y == b.y;
}

// return the index of the smallest number in an int array
int indexOfSmallest(int* arr, int length){
  if(!arr) return -1;
  
  int smaller = 0;
  for(int i = 1; i < length; i++){
    if(arr[i] < arr[smaller])
      smaller = i;
  }

  return smaller;
}

// sort an int array by descending order
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