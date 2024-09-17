#include "game.h"
#include "drawing.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

bool debug = false;
const Vector2 resolution = {800, 1000};

const int fontSize = 40;
const int debugFontSize = 20;
const int gameOverFontSize = 100;

//color constants (for now)
const Color backgroundColor = {116, 115, 20, 255};
const Color borderColor = {80, 79, 14, 255};
const Color playerColor = {45,45,8,255};
const Color foodColor = {207, 143, 8, 255};
const Color fontColor = borderColor;
const Color gameOverFontColor = { 102, 20, 0, 255 };

//top 200 pixels will be for info text
Rectangle borderRect = {0, 200, resolution.x, resolution.x};
const int borderThickness = 20;
const int playAreaLength = resolution.x-(borderThickness*2);
//number of "units" across the play area (positions the player can be in)
const int playAreaLengthUnits = 40;

//size of those units in real monitor pixels
//(760 / 40 == 19)
const int unitPxlSize = playAreaLength / playAreaLengthUnits;

void drawText() {
  if (gameOverFlag) { 
    DrawText("Gameover", 170, resolution.y/2, gameOverFontSize, gameOverFontColor);
    DrawText("Press space to restart", 210, resolution.y/2+100, gameOverFontSize/3, gameOverFontColor);
    // return; 
  } 
  char infoText [100];

  snprintf(infoText, 11, "Score: %i  ", playerLength);
  snprintf(infoText + strlen(infoText), 15, "Time: %.0f  ", timeElapsed);
  snprintf(infoText + strlen(infoText), 30, "High Score: %i  ", highScore);
  DrawText(infoText, 25, 25, fontSize, fontColor);

  if (!debug) { return; }

  char debugText [200];
  Vector2 mousePos = GetMousePosition();
  snprintf(debugText, 100, "Mouse position: x: %.0f y: %.0f", mousePos.x, mousePos.y);
  snprintf(debugText + strlen(debugText), 100, "\n\nFoodCount: %i", foodCount);
  snprintf(debugText + strlen(debugText), 100, "\n\nMovement dir: %i", playerMovementDir);
  snprintf(debugText + strlen(debugText), 100, "\n\nGetTime: %.2f", GetTime());
  snprintf(debugText + strlen(debugText), 100, "  GetFrameTime: %.4f", GetFrameTime());
  DrawText(debugText, 25, 75, debugFontSize, fontColor);

  snprintf(debugText, 100, "PlayerPosition x: %.2f, y: %.2f", playerPos.x, playerPos.y);
  // snprintf(debugText, 100, "Length: %i, histSize: %i", playerLength);
  for (int i = 0; i < playerLength; i++) {
    snprintf(debugText + strlen(debugText), 100, "\n%i: %.0f, %.0f", i, playerPositionHistory[i].x, playerPositionHistory[i].y);
  }
  DrawText(debugText, 350, 75, debugFontSize, fontColor);
}

void drawBackground() {
  ClearBackground(backgroundColor);
  DrawRectangleLinesEx(borderRect, borderThickness, borderColor);
}

void drawObjects() {
  Color pixelColor = {0,0,0,0};
  Rectangle pixel = {0, 0, unitPxlSize, unitPxlSize};
  for (int x = 0; x < playAreaLengthUnits; x++) {
    for (int y = 0; y < playAreaLengthUnits; y++) {
      pixel.x = x*unitPxlSize+borderThickness;
      pixel.y = y*unitPxlSize+borderRect.y+borderThickness;
      switch (playField[x][y]) {
        case NONE:
          pixelColor = backgroundColor;
        break;
        case FOOD:
          pixelColor = foodColor;
        break;
        case PLAYER:
          pixelColor = playerColor;
        break;
      }
      DrawRectangleRec(pixel, pixelColor);
    }
  }
}
