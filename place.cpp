#include <iostream>
#include "board.h"
#include "place.h"

using namespace std;

using Board = Tile[8][8];

bool checkEnclosed(Board& board, int x, int y, int dx, int dy, Tile t)
{
	Tile colour = t;

	Tile opp; // Opposite colour
	if(colour == black) { opp = white; }
	else if(colour == white) { opp = black; }
	else throw invalid_argument("Tile not recognized as black or white."); 

	int posX = x + dx;
	int posY = y + dy;
	int i = 0;
	while(board[posX][posY] != empty 
			&& posX <= 7 && posY <= 7 && posX >= 0 && posY >= 0)
	{
		if(board[posX][posY] == opp)
		{
			i++;
			posX += dx;
			posY += dy;
		}
		else if(board[posX][posY] == colour && i > 0)
		{
			return true;
		}
		else return false;
	}
	return false;
}

void turnTiles(Board& board, int x, int y, int dx, int dy, Tile t)
{
	Tile colour = t; 
	Tile opp; // Opposite colour
	
	if(colour == black) { opp = white; }
	else if(colour == white) { opp = black; }
	else throw invalid_argument("Tile not recognized as black or white.");

	int posX = x + dx;
	int posY = y + dy;
	while(board[posX][posY] == opp)
	{
		board[posX][posY] = colour;
		posX += dx;
		posY += dy;
	}
}
	
// Input: board, x, y, farge. x og y er feil.
bool placeTile(Board& board, int y, int x, Tile t)
{
	if(t == empty) { throw invalid_argument("Cannot place an empty tile."); }
	if(board[x][y] != empty) 
	{
		//printBoard(board);
		//cout << t <<  "That move is invalid. "
			//<< "You cannot place a piece on an occupied tile." << endl;
		return 0;
	}
	board[x][y] = t;
	bool turned = 0;
	for(int dx = -1; dx <= 1; dx++)
	{
		for(int dy = -1; dy <= 1; dy++)
		{
			if(dx == 0 && dy ==0) { continue; }
			if(checkEnclosed(board, x, y, dx, dy, t))
			{
				turnTiles(board, x, y, dx, dy, t);
				turned = 1;
			}
		}
	}
	if(!turned)
	{
		board[x][y] = empty;
		//cout << "That move is invalid. "
		//<< "You must enclose at least one tile of your opponents color." 
		//<< endl;
	}
	return turned;
}
