all: main.cpp
	g++ -g -Wall -o othello main.cpp othello.cpp board.cpp
clean:
	$(RM) othello
