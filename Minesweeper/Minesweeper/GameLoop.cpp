#include <iostream>
#include "Gameloop.h"

using namespace std;

Gameloop::Gameloop()
{
	//board = new Board();
}

Gameloop::~Gameloop()
{
	//delete board;
}

void Gameloop::StartGame()
{
	int first_x;
	int first_y;
	int size;
	cout << "Enter size of board: ";
	cin >> size;
	board.InitializeBoard(size);
	cout << "Enter the first co-ordinates to reveal: ";
	cin >> first_x >> first_y;

	board.PlaceMines(first_x, first_y);
	board.RevealCell(first_x, first_y);
	board.DisplayBoard();

	while (true)
	{
		int x;
		int y;
		cout << "Enter next co-ordinates to reveal: ";
		cin >> x >> y;

		bool hit_mine = board.RevealCell(x, y);
		board.DisplayBoard();

		if (hit_mine)
		{
			cout << "Game Over!!! You hit a mine :(" << endl;
			break;
		}
		
		if(board.CheckWin())
		{
			cout << "Congratulations!!! You have won :)" << endl;
			break;
		}
	}
}
