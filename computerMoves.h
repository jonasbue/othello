#pragma once
#include <vector>
#include <utility>
#include <map>
#include "board.h"

using namespace std;
using Board = Tile[8][8];

vector<pair<int, int>> legalMoves(Board& board, Tile t);

int machineMove(Board& board, Tile t);


// Simulates one of the legal moves. Adds the move and outcome on board to map of legal moves 
void simulateMove(Board& board, vector<pair<int, int>>& moves, 
				map<pair<int, int>, float>& standings, Tile& machine);


// Iterates through map of legal moves and their outcomes.
// Returns the move that corresponds to the best outcome.
pair<int, int> selectBestMove(vector<pair<int, int>>& moves, 
						map<pair<int, int>, float>& standings);


int smartMachineMove(Board& board, Tile& machine, Tile& player, 
					map<pair<int, int>, float>& standings, 
					int maxDepth, int depth);

