#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "board.h"
#include "place.h"
#include "computerMoves.h"

using namespace std;

using Board = Tile[8][8];

vector<pair<int, int>> legalMoves(Board& board, Tile t)
{
	vector<pair<int, int>> moves;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j] == empty)
			{
				for(int dx = -1; dx < 2; dx++)
				{
					for(int dy = -1; dy < 2; dy++)
					{
						if(dx == 0 && dy ==0) { continue; }
						if(checkEnclosed(board, i, j, dx, dy, t))
						{
							moves.push_back(make_pair(i, j));
						}
					}
				}
			}
		}
	}
	// Some info that can be used for debugging
	//cout << "Available machine moves:" << endl;
	//for(int i = 0; i < moves.size(); i++)
	//{
		//cout << moves[i].first << "\t" << moves[i].second << endl;
	//}
	return moves;
}

int machineMove(Board& board, Tile t)
{
	vector<pair<int, int>> moves = legalMoves(board, t);
	if(moves.size())
	{
		int move = rand() % moves.size();
		placeTile(board, moves[move].second, moves[move].first, t);
		cout << "Selected machine move:";
		cout << endl  << moves[move].second << "\t" 
			<< moves[move].first << endl;
	}
	return moves.size();
}

// Simulates one of the legal moves. Adds the move and outcome on board to map of legal moves 
void simulateMove(Board& board, vector<pair<int, int>>& moves, map<pair<int, int>, float>& standings, Tile& machine)
{
	for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
	{
		Board copy;
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				copy[i][j] = board[i][j];
			}
		}
		placeTile(copy, it->second, it->first, machine);

		pair<int, int> scores = count(copy);
		standings[*it] = static_cast<float>(scores.first)/static_cast<float>(scores.second);
		//printBoard(copy); // Might be useful when debugging
	}
}

// Iterates through map of legal moves and their outcomes.
// Returns the move that corresponds to the best outcome.
pair<int, int> selectBestMove(vector<pair<int, int>>& moves, map<pair<int, int>, float>& standings)
{
	pair<int, int> bestMove = moves[0];
	for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
	{
		if(standings[*it] < standings[bestMove])
		{
			bestMove.first = it->first;
			bestMove.second = it->second;
		}
	}
	return bestMove;
}

int smartMachineMove(Board& board, Tile& machine, Tile& player, map<pair<int, int>, float>& standings, int maxDepth=1, int depth=0)
{
	vector<pair<int, int>> moves = legalMoves(board, machine);
	if(moves.size())
	{
		simulateMove(board, moves, standings, machine);
		pair<int, int> bestMove = selectBestMove(moves, standings);
		placeTile(board, bestMove.second, bestMove.first, machine);	
	}
	return moves.size();
}
