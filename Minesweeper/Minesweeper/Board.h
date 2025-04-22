#pragma once

#include "Cell.h"
#include <vector>

using namespace std;

class Board
{
private:
	int board_size;
	int mine_count;
	vector<vector<Cell>> grid;
	vector<pair<int, int>> mines;

public:
	//Board();

	void InitializeBoard(int size);
	void PlaceMines(int first_x, int first_y);
	void FloodFill(int x, int y);
	bool RevealCell(int x, int y);
	bool CheckWin();
	void DisplayBoard();
};

