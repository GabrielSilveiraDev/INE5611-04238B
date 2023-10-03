#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <exception>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <pthread.h>
#include <sstream>
#include <string>
#include <io.h>
#include <utility>
#include <vector>


class Game {


	void checkMinimumDimensions(int x, int y);
	void checkOverState(void);
	void constructGameStructures(int x, int y);
	void startGameThreads(void);
	void startGame(void);
};

#endif