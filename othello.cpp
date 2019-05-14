#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// a)

enum Tile {empty, black, white};

// b)

using Board = Tile[8][8];

Board& initBoard(Board& board)
{
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			board[x][y] = empty;
		}
	}
	board[3][3] = white;
	board[3][4] = black;
	board[4][3] = black;
	board[4][4] = white;
	return board;
}

void printTile(const Tile& t)
{
	switch(t)
	{
		case empty:
			cout << "_";
			break;
		case black:
			cout << "o";
			break;
		case white:
			cout << "x";
			break;
		default:
			throw invalid_argument("Tile not valid");
	}
}

pair<int, int> count(const Board& board);

void printBoard(const Board& board)
{
	pair<int, int> scores = count(board);
	cout << "  _ _ _ _ _ _ _ _  " << endl;
	for(int y = 0; y < 8; y++)
	{
		cout << " ";
		for(int x = 0; x < 8; x++)
		{
			cout << "|";
			printTile(board[y][x]);
		}
		cout << "|" << y;
		if(y == 1)
		{
			cout << "\tBlack: ";
			printTile(black);
		}
		if(y == 2)
		{
			cout << "\tWhite: ";
			printTile(white);
		}
		if(y == 4)
		{
			cout << "\tScores:";
		}
		if(y == 5)
		{
			cout << "\tBlack: " << scores.first;
		}
		if(y == 6)
		{
			cout << "\tWhite: " << scores.second;
		}
		cout << endl;
	}
	cout << "  0 1 2 3 4 5 6 7 " << endl;
}

// d)

void turnTile(Tile& t)
{
	switch(t)
	{
		case black:
			t = white;
			break;
		case white:
			t = black;
			break;
		default:
			throw invalid_argument("Tile not recognized as black or white.");
			break;
	}
}

bool checkEnclosed(Board& board, int x, int y, int dx, int dy, Tile t)
{
	Tile colour = t;

	Tile opp; // Opposite colour
	if(colour == black) { opp = white; }
	else if(colour == white) { opp = black; }
	else throw invalid_argument("Tile not recognized as black or white.");

	int posX = x + dx;
	int posY = y + dy;
	int i = 0;
	while(board[posX][posY] != empty 
			&& posX <= 7 && posY <= 7 && posX >= 0 && posY >= 0)
	{
		if(board[posX][posY] == opp)
		{
			i++;
			posX += dx;
			posY += dy;
		}
		else if(board[posX][posY] == colour && i > 0)
		{
			return true;
		}
		else return false;
	}
	return false;
}

void turnTiles(Board& board, int x, int y, int dx, int dy, Tile t)
{
	Tile colour = t; 
	Tile opp; // Opposite colour
	
	if(colour == black) { opp = white; }
	else if(colour == white) { opp = black; }
	else throw invalid_argument("Tile not recognized as black or white.");

	int posX = x + dx;
	int posY = y + dy;
	while(board[posX][posY] == opp)
	{
		board[posX][posY] = colour;
		posX += dx;
		posY += dy;
	}
}
	
// Input: board, x, y, farge. x og y er feil.
bool placeTile(Board& board, int y, int x, Tile t)
{
	if(t == empty) { throw invalid_argument("Cannot place an empty tile."); }
	if(board[x][y] != empty) 
	{
		cout << "That move is invalid. "
			<< "You cannot place a piece on an occupied tile." << endl;
		return 0;
	}
	board[x][y] = t;
	bool turned = 0;
	for(int dx = -1; dx <= 1; dx++)
	{
		for(int dy = -1; dy <= 1; dy++)
		{
			if(dx == 0 && dy ==0) { continue; }
			if(checkEnclosed(board, x, y, dx, dy, t))
			{
				turnTiles(board, x, y, dx, dy, t);
				turned = 1;
			}
		}
	}
	if(!turned)
	{
		board[x][y] = empty;
		cout << "That move is invalid. "
		<< "You must enclose at least one tile of your opponents color." 
		<< endl;
	}
	return turned;
}

vector<pair<int, int>> legalMoves(Board& board, Tile t)
{
	vector<pair<int, int>> moves;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j] == empty)
			{
				for(int dx = -1; dx < 2; dx++)
				{
					for(int dy = -1; dy < 2; dy++)
					{
						if(dx == 0 && dy ==0) { continue; }
						if(checkEnclosed(board, i, j, dx, dy, t))
						{
							moves.push_back(make_pair(i, j));
						}
					}
				}
			}
		}
	}
	// Some info that can be used for debugging
	//cout << "Available machine moves:" << endl;
	//for(int i = 0; i < moves.size(); i++)
	//{
		//cout << moves[i].first << "\t" << moves[i].second << endl;
	//}
	return moves;
}

int machineMove(Board& board, Tile t)
{
	vector<pair<int, int>> moves = legalMoves(board, t);
	if(moves.size())
	{
		int move = rand() % moves.size();
		placeTile(board, moves[move].second, moves[move].first, t);
		cout << "Selected machine move:";
		cout << endl  << moves[move].second << "\t" 
			<< moves[move].first << endl;
	}
	return moves.size();
}

int smartMachineMove(Board& board, Tile& machine, Tile& player, map<pair<int, int>, float>& standings, int maxDepth = 1, int depth=0)
{
	vector<pair<int, int>> moves = legalMoves(board, machine);
	if(moves.size())
	{
		for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
		{
			Board copy;
			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					copy[i][j] = board[i][j];
				}
			}
			placeTile(copy, it->second, it->first, machine);

			pair<int, int> scores = count(copy);
			standings[*it] = static_cast<float>(scores.first)/static_cast<float>(scores.second);
			//printBoard(copy); // Might be useful when debugging
		}

		pair<int, int> bestMove = moves[0];
		for(vector<pair<int, int>>::iterator it = moves.begin(); it != moves.end(); it++)
		{
			if(standings[*it] < standings[bestMove])
			{
				bestMove.first = it->first;
				bestMove.second = it->second;
			}
		}
		placeTile(board, bestMove.second, bestMove.first, machine);	
	}
	return moves.size();
}


int playerMove(Board& board, Tile& t)
{
	int x = -1;
	int y = -1;
	cout << "Your turn" << endl;
	while(x < 0 || x > 7 || y < 0 || y > 7)
	{
		cout << "Select coordinates (0-7)." << endl
			<< "If no legal move is available, type '9'"
			<< endl	<< "x = ";
		cin >> x;
		if(x == 9) { return -1; }
		cout << "y = ";
		cin >> y;
	}
	if(x != 9) 
	{
		return placeTile(board, x, y, t);
	}
	else return 0;
}

pair<int, int> count(const Board& board)
{
	int b = 0;
	int w = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(board[j][i] == white) w++;
			else if(board[j][i] == black) b++;
		}
	}
	return make_pair(b, w);
}

void declareWinner(Board& board)
{
	pair<int, int> result = count(board);
	int b = result.first;
	int w = result.second;
	if(b > w)
	{
		cout << "Black wins with " << b << " tiles to " << w << "!" << endl;
	}
	else if(b < w)
	{
		cout << "White wins with " << w << " tiles to " << b << "!" << endl;
	}
	else
	{
		cout << "We are all winners here" << endl;
	}
}
			
void takeTurns(Board& board, Tile& player, Tile& opponent)
{
	if(player == black)
	{	
		while(true)
		{
			int legalPlayerMoves = 0;
			int legalMachineMoves = 1;
			pair<int, int> scores = count(board);

			if(scores.first == 0 || scores.second == 0) break;
			while(legalPlayerMoves == 0)
			{
				legalPlayerMoves = playerMove(board, player);
			}
			printBoard(board);

			if(scores.first == 0 || scores.second == 0) break;
			map<pair<int, int>, float> standings;
			legalMachineMoves = smartMachineMove(board, opponent, player, standings);
			cout << "Computer's turn... " << endl;
			printBoard(board);

			if(legalPlayerMoves == -1 && !legalMachineMoves) break;
		}
	}
	else
	{
		while(true)
		{
			int legalPlayerMoves = 0;
			int legalMachineMoves = 1;
			pair<int, int> scores = count(board);

			if(scores.first == 0 || scores.second == 0) break;
			cout << "Computer's turn... " << endl;
			legalMachineMoves = machineMove(board, opponent);
			printBoard(board);

			if(scores.first == 0 || scores.second == 0) break;
			while(legalPlayerMoves == 0)
			{
				legalPlayerMoves = playerMove(board, player);
			}
			printBoard(board);

			if(legalPlayerMoves == -1 && !legalMachineMoves) break;
		}
	}	
}


void play(Board& board)
{
	cout << "Othello" << endl << endl;
	printBoard(board);
	Tile player;
	Tile opponent;
	int in;
	while(in != 1 && in != 2)
	{
		cout << "Select your colour:" << endl
			<< "1: Black" << endl
			<< "2: White" << endl
			<< "Color: ";
		cin >> in;
	}

	player = Tile(in);
	if(player == black) { opponent = white; }
	else opponent = black;

	takeTurns(board, player, opponent);
	declareWinner(board);
}

int main()
{
	srand(time(nullptr));

	Board b;
	initBoard(b);
	play(b);
	return 0;
}
