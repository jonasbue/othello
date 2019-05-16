#include "board.h"
#include "place.h"
#include "computerMoves.h"
#include "computerMoves.h"
#include "othello.h"

int main()
{
	srand(time(nullptr));
	Board b;
	initBoard(b);
	play(b);
	return 0;
}
