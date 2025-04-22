#include <iostream>
#include "Board.h"
#include <ctime>


void Board::InitializeBoard(int size)
{
	mines.clear();
	board_size = size;
	mine_count = board_size * board_size * 0.15;
	grid.resize(board_size, vector<Cell>(board_size));
}

void Board::PlaceMines(int first_x, int first_y)
{
	//Place mines randomly on the board.
	int count = 0;
	while (count < mine_count)
	{
		int x = rand() % board_size;
		int y = rand() % board_size;

		if ((x == first_x && y == first_y) || grid[y][x].is_mine)
			continue;

		grid[y][x].is_mine = true;
		mines.push_back({ x,y });
		count++;
	}
	//Update adjacent mines numbers.
	for (int y = 0; y < board_size; y++)
	{
		for (int x = 0; x < board_size; x++)
		{
			if (grid[y][x].is_mine) continue;
			int adj_mines = 0;
			for (int adj_x = -1; adj_x <= 1; adj_x++)
			{
				for (int adj_y = -1; adj_y <= 1; adj_y++)
				{
					if (!(adj_x == 0 && adj_y == 0))
					{
						int adj_cell_x = adj_x + x;
						int adj_cell_y = adj_y + y;
						if (adj_cell_x >= 0 && adj_cell_x < board_size && adj_cell_y >= 0 && adj_cell_y < board_size && grid[adj_cell_y][adj_cell_x].is_mine)
							adj_mines++;
					}
				}
			}
			if (adj_mines > 0)
				grid[y][x].display = '0' + adj_mines;
		}
	}
}
//Fills the board until number cell appears.
void Board::FloodFill(int x, int y)
{
	if (x < 0 || x >= board_size || y < 0 || y >= board_size) return;
	if (grid[y][x].is_revealed || grid[y][x].is_mine) return;

	grid[y][x].is_revealed = true;

	if (grid[y][x].display != ' ') return;

	for (int adj_x = -1; adj_x <= 1; adj_x++)
	{
		for (int adj_y = -1; adj_y <= 1; adj_y++)
		{
			if (adj_x == 0 && adj_y == 0) continue;
			FloodFill(x + adj_x, y + adj_y);
		}
	}
}

bool Board::RevealCell(int x, int y)
{
	//Returns true if the cell is mine.
	if (grid[y][x].is_mine)
	{
		grid[y][x].is_revealed = true;
		return true;
	}
	//If cell is empty.
	if (grid[y][x].display == ' ')
		FloodFill(x, y);
	//Marks cell as revealed.
	else
		grid[y][x].is_revealed = true;
	return false;
}

bool Board::CheckWin()
{
	//Check if there are any unrevealed cells on the board.
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (!grid[i][j].is_mine && !grid[i][j].is_revealed)
				return false;
		}
	}
	return true;
}

void Board::DisplayBoard()
{
	// Print top X-axis labels
	cout << "   "; // spacing for Y-axis labels
	for (int x = 0; x < board_size; x++) {
		if (x < 10) cout << x << "  ";
		else cout << x << " ";
	}
	cout << "\n";

	// Print each row
	for (int y = 0; y < board_size; y++) {
		if (y < 10) cout << " " << y << " ";
		else cout << y << " ";

		for (int x = 0; x < board_size; x++) {
			if (!grid[y][x].is_revealed)
				cout << "#  ";
			else if (grid[y][x].is_mine)
				cout << "M  ";
			else
				cout << grid[y][x].display << "  ";
		}
		cout << endl;
	}
}