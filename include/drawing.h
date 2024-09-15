#ifndef DRAWING_H
#define DRAWING_H
#include <raylib.h>

extern bool debug;

extern const Vector2 resolution;
extern const int playAreaLengthUnits;

void drawText(); //not to be confused with DrawText
void drawBackground();
void drawObjects();

#endif