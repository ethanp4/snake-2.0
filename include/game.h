#ifndef GAME_H
#define GAME_H
#include <raylib.h>

enum objects{ NONE, PLAYER, FOOD };
enum dirs { UP, DOWN, LEFT, RIGHT, NO_INPUT };
extern Vector2 dirs[4];
extern enum dirs movementDir;

extern float startTime;
extern float timeElapsed;
extern int highScore;

extern int playerLength;
extern int foodCount;
extern bool gameOverFlag;
extern Vector2 playerPos;

extern Vector2 positionHistory[200]; //i cant make this dynamically allocated
extern int playField[40][40]; //allocated on init

void movePlayer();
void initGame();
void spawnFood();
void restartGame();

#endif
