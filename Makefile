all: main.cpp
	g++ -g -Wall -o othello main.cpp othello.cpp board.cpp place.cpp computerMoves.cpp
clean:
	$(RM) othello
