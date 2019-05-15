#include <iostream>
#include <vector>
#include <utility>
#include "board.h"

using namespace std;

void initBoard(Board& board)
{
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			board[x][y] = empty;
		}
	}
	board[3][3] = white;
	board[3][4] = black;
	board[4][3] = black;
	board[4][4] = white;
}

void printTile(const Tile& t)
{
	switch(t)
	{
		case empty:
			cout << "_";
			break;
		case black:
			cout << "o";
			break;
		case white:
			cout << "x";
			break;
		default:
			throw invalid_argument("Tile not valid");
	}
}

pair<int, int> count(const Board& board)
{
	int b = 0;
	int w = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[j][i] == white) w++;
			else if(board[j][i] == black) b++;
		}
	}
	return make_pair(b, w);
}

void printBoard(const Board& board)
{
	pair<int, int> scores = count(board);
	cout << "  _ _ _ _ _ _ _ _  " << endl;
	for(int y = 0; y < 8; y++)
	{
		cout << " ";
		for(int x = 0; x < 8; x++)
		{
			cout << "|";
			printTile(board[y][x]);
		}
		cout << "|" << y;
		if(y == 1)
		{
			cout << "\tBlack: ";
			printTile(black);
		}
		if(y == 2)
		{
			cout << "\tWhite: ";
			printTile(white);
		}
		if(y == 4)
		{
			cout << "\tScores:";
		}
		if(y == 5)
		{
			cout << "\tBlack: " << scores.first;
		}
		if(y == 6)
		{
			cout << "\tWhite: " << scores.second;
		}
		cout << endl;
	}
	cout << "  0 1 2 3 4 5 6 7 " << endl;
}

void turnTile(Tile& t)
{
	switch(t)
	{
		case black:
			t = white;
			break;
		case white:
			t = black;
			break;
		default:
			throw invalid_argument("Tile not recognized as black or white.");
			break;
	}
}
