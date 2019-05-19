#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "board.h"
#include "place.h"
#include "computerMoves.h"
#include "othello.h"

using namespace std;

using Board = Tile[8][8];

int playerMove(Board& board, Tile& t)
{
	int x = -1;
	int y = -1;
	cout << "Your turn" << endl;
	while(x < 0 || x > 7 || y < 0 || y > 7)
	{
		cout << "Select coordinates (0-7)." << endl
			<< "If no legal move is available, type '9'"
			<< endl	<< "x = ";
		cin >> x;
		if(x == 9) { return -1; }
		cout << "y = ";
		cin >> y;
	}
	if(x != 9) 
	{
		return placeTile(board, x, y, t);
	}
	else return 0;
}

void declareWinner(Board& board)
{
	pair<int, int> result = count(board);
	int b = result.first;
	int w = result.second;
	if(b > w)
	{
		cout << "Black wins with " << b << " tiles to " << w << "!" << endl;
	}
	else if(b < w)
	{
		cout << "White wins with " << w << " tiles to " << b << "!" << endl;
	}
	else
	{
		cout << "We are all winners here" << endl;
	}
}
			
void takeTurns(Board& board, Tile& player, Tile& opponent)
{
	if(player == black)
	{	
		while(true)
		{
			int legalPlayerMoves = 0;
			int legalMachineMoves = 1;
			pair<int, int> scores = count(board);

			if(scores.first == 0 || scores.second == 0) break;
			while(legalPlayerMoves == 0)
			{
				legalPlayerMoves = playerMove(board, player);
			}
			printBoard(board);

			if(scores.first == 0 || scores.second == 0) break;
			legalMachineMoves = smartMachineMove(board, opponent, player, 1, 0);
			cout << "Computer's turn... " << endl;
			printBoard(board);

			if(legalPlayerMoves == -1 && !legalMachineMoves) break;
		}
	}
	else
	{
		while(true)
		{
			int legalPlayerMoves = 0;
			int legalMachineMoves = 1;
			pair<int, int> scores = count(board);

			if(scores.first == 0 || scores.second == 0) break;
			cout << "Computer's turn... " << endl;
			legalMachineMoves = machineMove(board, opponent);
			printBoard(board);

			if(scores.first == 0 || scores.second == 0) break;
			while(legalPlayerMoves == 0)
			{
				legalPlayerMoves = playerMove(board, player);
			}
			printBoard(board);

			if(legalPlayerMoves == -1 && !legalMachineMoves) break;
		}
	}	
}

void play(Board& board)
{
	cout << "Othello" << endl << endl;
	printBoard(board);
	Tile player;
	Tile opponent;
	int in;
	while(in != 1 && in != 2)
	{
		cout << "Select your colour:" << endl
			<< "1: Black" << endl
			<< "2: White" << endl
			<< "Color: ";
		cin >> in;
	}

	player = Tile(in);
	if(player == black) { opponent = white; }
	else opponent = black;

	takeTurns(board, player, opponent);
	declareWinner(board);
}
