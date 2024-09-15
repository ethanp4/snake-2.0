#include "../include/game.h"
#include "../include/drawing.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

bool debug = true;
const Vector2 resolution = {800, 1000};

const int fontSize = 40;
const int debugFontSize = 20;

//color constants (for now)
const Color backgroundColor = {116, 115, 20, 255};
const Color borderColor = {80, 79, 14, 255};
const Color fontColor = borderColor;
const Color playerColor = {45,45,8,255};

//top 200 pixels will be for info text
const int borderThickness = 20;
Rectangle borderRect = {0, 200, resolution.x, resolution.x};
const int playAreaLength = resolution.x-(borderThickness*2);
//number of "units" across the play area (positions the player can be in)
const int playAreaLengthUnits = 40;

//size of those units in real monitor pixels
//(760 / 40 == 19)
const int unitPxlSize = playAreaLength / playAreaLengthUnits;

void drawText() {
  char infoText [100];
  double timeElapsed = GetTime();

  snprintf(infoText, 11, "Score: %i  ", playerLength);
  snprintf(infoText + strlen(infoText), 15, "Time: %.0f  ", timeElapsed);
  snprintf(infoText + strlen(infoText), 30, "High Score: %i  ", highScore);
  DrawText(infoText, 25, 25, fontSize, fontColor);

  if (!debug) { return; }

  char debugText [100];
  Vector2 mousePos = GetMousePosition();
  snprintf(debugText, 100, "Mouse position: x: %.0f y: %.0f", mousePos.x, mousePos.y);
  snprintf(debugText + strlen(debugText), 100, "\n\nFoodCount: %i", foodCount);
  DrawText(debugText, 25, 75, debugFontSize, fontColor);
}

void drawBackground() {
  ClearBackground(backgroundColor);
  DrawRectangleLinesEx(borderRect, borderThickness, borderColor);
}

void drawObjects() {

}