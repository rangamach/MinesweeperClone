#pragma once

#include "Cell.h"
#include <vector>

using namespace std;

class Board
{
private:
	int size;
	int mine_count;
	vector<vector<Cell>> grid;
	vector<pair<int, int>> mines;

public:
	Board();

	void PlaceMines(int first_x, int first_y);
	bool RevealCell(int x, int y);
	bool CheckWin();
	void DisplayBoard();
};

