#ifndef GAME_H
#define GAME_H
#include <raylib.h>

extern int playerLength;
extern int highScore;
extern int foodCount;
enum objects{ NONE, PLAYER, FOOD};
enum dirs { UP, DOWN, LEFT, RIGHT };
extern Vector2 dirs[4];

extern enum dirs movementDir;
extern Vector2 playerPos;
extern Vector2 positionHistory[1]; //adjust size as needed

extern int** playField;

void initGame();

#endif