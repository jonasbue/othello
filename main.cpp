#include "othello.h"
#include "board.h"

int main()
{
	srand(time(nullptr));
	Board b;
	initBoard(b);
	play(b);
	return 0;
}
