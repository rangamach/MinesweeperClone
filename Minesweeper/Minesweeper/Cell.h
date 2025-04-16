#pragma once
class Cell
{
public:
	bool is_mine;
	char display;
	bool is_revealed;

	Cell()
	{
		is_mine = false;
		display = ' ';
		is_revealed = false;
	}
};

