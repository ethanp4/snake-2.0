#include "game.h"
#include "drawing.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

int playerLength = 0;
int highScore = 0;
int foodCount = 0;

Vector2 dirs[4] = { {0,-1}, {0,1}, {-1,0}, {1,0}};
enum dirs movementDir = UP; //might change this

//using local coordinates
//(playAreaLengthUnits)
Vector2 playerPos = {20,20};

int** playField;
Vector2** positionHistory;
int positionHistorySize;

void initGame() {
  int squares = playAreaLengthUnits*playAreaLengthUnits;
  //realloc dimension x
  playField = realloc(playField, sizeof(int)*playAreaLengthUnits);

  //malloc each row (dimension y)
  for (int x = 0; x < playAreaLengthUnits; x++) {
    playField[x] = (int*)malloc(sizeof(int)*playAreaLengthUnits);

    //initialize the array
    for (int y = 0; y < playAreaLengthUnits; y++) {
      if (GetRandomValue(0, squares) < 10) { // shoot for 10
        playField[x][y] = FOOD;
        foodCount++;
      } else {
        playField[x][y] = NONE;
      }
    }
  }
  movementDir = GetRandomValue(0, 3);
  // printf("Made %i food and %i none", foodCount, squares-foodCount);
  positionHistory = realloc(positionHistory, sizeof(Vector2)*(playerLength+1));
  positionHistorySize = 0;
}

void movePlayer() {
  playField[(int)playerPos.x][(int)playerPos.y] = NONE;

  // no need to rearrange when theres only one element
  // if (playerLength == 1) {
  //   positionHistorySize = 1;
  // }
  if (playerLength > positionHistorySize) {
    positionHistory = realloc(positionHistory, sizeof(Vector2)*(playerLength+1));
    positionHistorySize += 1;
  }

  // for (int i = 0; i < playerLength-1; i++) {
  for (int i = playerLength; i > 1; i--) {
    positionHistory[i-1] = positionHistory[i]; 
  }
  positionHistory[0] = &playerPos;

  playerPos = Vector2Add(playerPos, dirs[movementDir]);
  if (playerPos.x > playAreaLengthUnits) {
    playerPos.x = 0;
  }
  if (playerPos.x < 0) {
    playerPos.x = playAreaLengthUnits-1;
  }
  if (playerPos.y > playAreaLengthUnits) {
    playerPos.y = 0;
  }
  if (playerPos.y < 0) {
    playerPos.y = playAreaLengthUnits-1;
  }

  if (playField[(int)playerPos.x][(int)playerPos.y] == FOOD) {
    playerLength++;
    foodCount--;
  }

  playField[(int)playerPos.x][(int)playerPos.y] = PLAYER;
}
