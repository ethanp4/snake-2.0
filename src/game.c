#include "game.h"
#include "drawing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int playerLength = 0;
int highScore = 0;
int foodCount = 0;

Vector2 dirs[4] = { {0,1}, {0,-1}, {-1,0}, {1,0}};
enum dirs movementDir = UP; //might change this

//using local coordinates
//(playAreaLengthUnits)
Vector2 playerPos = {20,20}; 

int** playField;

void initGame() {
  srand(time(NULL));

  int squares = playAreaLengthUnits*playAreaLengthUnits;
  //realloc dimension x
  playField = (int**)realloc(playField, sizeof(int)*playAreaLengthUnits);

  //malloc each row (dimension y)
  for (int i = 0; i < playAreaLengthUnits; i++) {
    playField[i] = (int*)malloc(sizeof(int)*playAreaLengthUnits);

    //initialize the array
    for (int j = 0; j < playAreaLengthUnits; j++) {
      if ((rand() % squares) < 10) { // approx 10
        playField[i][j] = FOOD;
        foodCount++;
      } else {
        playField[i][j] = NONE;
      }
    }
  }
  printf("Made %i food and %i none", foodCount, squares-foodCount);

}
