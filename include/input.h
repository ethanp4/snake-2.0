#ifndef INPUT_H
#define INPUT_H
#include "game.h"

extern enum dirs currentInput;
extern enum dirs queuedInput;

void handleInput();

#endif