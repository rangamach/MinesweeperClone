#pragma once

#include "Board.h"

class Gameloop
{
private:
	Board board;

public:
	Gameloop();
	~Gameloop();

	void StartGame();
};
