#pragma once
#include <vector>
#include <map>
#include <utility>
#include "board.h"

using namespace std;

using Board = Tile[8][8];

int playerMove(Board& board, Tile& t);

void declareWinner(Board& board);

void takeTurns(Board& board, Tile& player, Tile& opponent);

void play(Board& board);

