#pragma once
#include <vector>
#include <utility>
#include <map>
#include "board.h"

using namespace std;
using Board = Tile[8][8];

vector<pair<int, int>> legalMoves(Board& board, Tile t);

int machineMove(Board& board, Tile t);

Board* copyBoard(const Board& b);

// Simulates one of the legal moves. Adds the move and outcome on board to map of legal moves 
void simulateFirstMoves(Board& board, vector<pair<int, int>>& moves, 
				map<pair<int, int>, float>& standings, Tile& machine);

float simulateMove(Board& board, pair<int, int>& move, Tile& t);


// Iterates through map of legal moves and their outcomes.
// Returns the move that corresponds to the best outcome.
pair<int, int> selectBestMove(vector<pair<int, int>>& moves, 
						map<pair<int, int>, float>& standings);


int smartMachineMove(Board& board, Tile& machine, Tile& player, int maxDepth, int depth);

