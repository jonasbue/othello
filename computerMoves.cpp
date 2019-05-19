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
	/*
	cout << "Available machine moves:" << endl;
	for(int i = 0; i < moves.size(); i++)
	{
	cout << moves[i].first << "\t" << moves[i].second << endl;
	}
	*/
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

// Simulates the legal moves. Adds each move and its outcome on the board to map of legal moves 
void simulateFirstMoves(Board& board, vector<pair<int, int>>& moves, map<pair<int, int>, float>& standings, Tile& machine)
{
	if(!standings.size())
	{
		for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
		{
			standings[*it] = simulateMove(board, *it, machine);
			//printBoard(copy); // Might be useful when debugging
		}
	}
}

map<pair<int, int>, float>& simulateNextMoves(Board& board, vector<pair<int, int>> moves, 
			map<pair<int, int>, float>& firstMoves, Tile& machine, Tile& player, int depth)
{
	//static int i = 0;
	//cout << i << endl;
	if(depth > 5) return firstMoves;
	for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
	{
	//if(depth == 0) cout << "/////////////////////////////////////////////" << endl << "/////////////////////////////////////////" << endl;
	//if(depth == 1) cout << "---------------------------------------------" << endl << "-----------------------------------------" << endl;

		//for(int d = 0; d < 2; d++)
		//{
			Board copy;
			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					copy[i][j] = board[i][j];
				}
			}
			vector<pair<int, int>> nextMoves;
			if(depth % 2)
			{
				//printBoard(copy);
				/*
				cout << "Selected machine move:";
				cout << endl  << it->second << "\t" 
					<< it->first << endl;
				*/

				map<pair<int, int>, float> playerMoveMap;
				//simulateFirstMoves(board, nextMoves, playerMoveMap, player);
				simulateNextMoves(board, nextMoves, playerMoveMap, machine, player, depth);
				pair<int, int> bestMove = selectBestMove(moves, playerMoveMap);

				placeTile(copy, bestMove.second, bestMove.first, player);
				firstMoves[*it] = simulateMove(copy, *it, player);
				nextMoves = legalMoves(copy, machine);
			}
			else
			{
				//printBoard(copy);
				/*
				cout << "Selected machine move:";
				cout << endl  << it->second << "\t" 
					<< it->first << endl;
				*/
				placeTile(copy, it->second, it->first, machine);
				firstMoves[*it] = simulateMove(copy, *it, machine);
				nextMoves = legalMoves(copy, player);
			}
			firstMoves = simulateNextMoves(copy, nextMoves, firstMoves, machine, player, depth + 1);

			/*
			if(i<2)
			{
				placeTile(copy, it->second, it->first, player);
				firstMoves[*it] = simulateMove(copy, *it, player);
				cout << i << endl;
				//i++;
				//printBoard(copy);
				//simulateNextMoves(copy, legalMoves(copy, machine), firstMoves, player, machine);
			}
			else
			{
				//cout << i << endl;
				continue;
			}
			*/
		//}
	}
	return firstMoves;
}

// Simulates one legal move. Returns the ratio between black and white tiles.
float simulateMove(Board& board, pair<int, int>& move, Tile& t)
{
	Board copy;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			copy[i][j] = board[i][j];
		}
	}
	placeTile(copy, move.second, move.first, t);

	pair<int, int> scores = count(copy);
	return static_cast<float>(scores.first)/static_cast<float>(scores.second);
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

int smartMachineMove(Board& board, Tile& machine, Tile& player, int maxDepth=1, int depth=0)
{
	vector<pair<int, int>> moves = legalMoves(board, machine);
	if(!moves.size()) return 0;

	map<pair<int, int>, float> standings;
	//simulateFirstMoves(board, moves, standings, machine);
	simulateNextMoves(board, moves, standings, machine, player, 0);
	pair<int, int> bestMove = selectBestMove(moves, standings);
	placeTile(board, bestMove.second, bestMove.first, machine);	

	return moves.size();
}
