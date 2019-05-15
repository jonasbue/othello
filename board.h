#pragma once
#include <utility>

using namespace std;

enum Tile {empty, black, white};

using Board = Tile[8][8];

void initBoard(Board& board);

void printTile(const Tile& t);

pair<int, int> count(const Board& board);

void printBoard(const Board& board);

void turnTile(Tile& t);

