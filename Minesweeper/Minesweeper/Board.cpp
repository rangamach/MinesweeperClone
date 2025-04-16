#include <iostream>
#include "Board.h"
#include <ctime>

Board::Board()
{
	size = 9;
	mine_count = 10;
	grid.resize(size, vector<Cell>(size));
}

void Board::PlaceMines(int first_x, int first_y)
{
	srand(time(0));
	mines.clear();

	while (mines.size() < mine_count)
	{
		//Getting new pair of x and y coordinates to place mine.
		int x = rand() % size;
		int y = rand() % size;
		//Checking if the coordinate is valid as in if the cell is not a mine.
		if ((x != first_x || y != first_y) && find(mines.begin(), mines.end(), make_pair(x, y)) == mines.end())
			mines.push_back(make_pair(x, y));
	}
	//Place mines on the grid.
	for (auto mine : mines)
	{
		grid[mine.first][mine.second].is_mine = true;
		grid[mine.first][mine.second].display = 'M';
	}
	//Update the adjacent cells with mine counts.
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j].is_mine) continue;
			int count = 0;
			//Traverse all adjacent cells.
			for (int adj_x = -1; adj_x <= 1; adj_x++)
			{
				for (int adj_y = -1; adj_y <= 1; adj_y++)
				{
					//x,y coordinates of one of the 8 adjacent cells.
					int adj_i = i + adj_x;
					int adj_j = j + adj_y;
					//Check if the cell is mine or not and checking if it is the current cell.
					if (!(adj_i == 0 && adj_j == 0) && adj_i >= 0 && adj_i < size && adj_j >= 0 && adj_j < size && grid[adj_i][adj_j].is_mine)
						count++;
				}
			}
			//Update the mine count in the current cell.
			if (count > 0)
				grid[i][j].display = '0' + count;
		}
	}
}

bool Board::RevealCell(int x, int y)
{
	//Skips revealed cells.
	if (grid[x][y].is_revealed) return false;
	//Marks cell as revealed.
	grid[x][y].is_revealed = true;
	//Returns true if the cell is mine.
	return grid[x][y].is_mine;
}

bool Board::CheckWin()
{
	//Check if there are any unrevealed cells on the board.
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!grid[i][j].is_mine && !grid[i][j].is_revealed)
				return false;
		}
	}
	return true;
}

void Board::DisplayBoard()
{
	cout << "X ";
	//Print the column headers.
	for (int i = 0; i < size; i++)
		cout << i << " ";
	cout << endl;
	//Print each row of the board.
	for (int i = 0; i < size; i++)
	{
		cout << i << " ";
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j].is_revealed)
				cout << grid[i][j].display << " ";
			else
				cout << "# ";
		}
		cout << endl;
	}
}
