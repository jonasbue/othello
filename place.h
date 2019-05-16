#pragma once
#include "board.h"

using namespace std;

using Board = Tile[8][8];

bool checkEnclosed(Board& board, int x, int y, int dx, int dy, Tile t);

void turnTiles(Board& board, int x, int y, int dx, int dy, Tile t);

// Input: board, x, y, farge. x og y er feil.
bool placeTile(Board& board, int y, int x, Tile t);

