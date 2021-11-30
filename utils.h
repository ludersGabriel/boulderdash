// Made by Gabriel Lüders
// GRR20190172

#include <allegro5/allegro5.h>

#ifndef UTILS_H
#define UTILS_H

// struct that defines a point
typedef struct POINT{
  int x;
  int y;
}Point;

// helper function that mallocs a space and checks if it worked
void* mallocSpace(int size, const char* desc);

// compares if two points are at the same place
bool comparePoints(Point a, Point b);

// checks if an allegro component has been initialized
void checkAllegroComponent(bool component, const char* desc);

// return the index of the smallest number in an int array
int indexOfSmallest(int* arr, int length);

// sort an int array by descending order
void sortArray(int* arr, int length);

#endif