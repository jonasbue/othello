#pragma once
#include <vector>
#include <map>
#include <utility>

using namespace std;

enum Tile {empty, black, white};

using Board = Tile[8][8];

Board& initBoard(Board& board);

void printTile(const Tile& t);

pair<int, int> count(const Board& board);

void printBoard(const Board& board);

void turnTile(Tile& t);

bool checkEnclosed(Board& board, int x, int y, int dx, int dy, Tile t);

void turnTiles(Board& board, int x, int y, int dx, int dy, Tile t);

bool placeTile(Board& board, int y, int x, Tile t);

vector<pair<int, int>> legalMoves(Board& board, Tile t);

int machineMove(Board& board, Tile t);

int smartMachineMove(Board& board, Tile& machine, Tile& player, 
					map<pair<int, int>, float>& standings, 
					int maxDepth, int depth);

int playerMove(Board& board, Tile& t);

void declareWinner(Board& board);

void takeTurns(Board& board, Tile& player, Tile& opponent);

void play(Board& board);

