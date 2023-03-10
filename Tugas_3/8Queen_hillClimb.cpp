#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define vi vector<int>
#define vvi vector<vi>

int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

void makeRandom(vvi &board, vi &state)
{
	for(int i = 0; i < 8; ++i){
		state[i] = rand() % 8;
		board[state[i]][i] = 1;
	}
}

void printBoard(vvi &board)
{
	cout << endl;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
			cout << board[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

vvi translate(vi state)
{
	vvi res(8, vi(8));
	for(int i = 0; i < 8; ++i)
		res[state[i]][i] = 1;
	return res;
}

bool validPos(int r, int c)
{
	return (r >= 0 and r < 8 and c >= 0 and c < 8);
}

int calcAttacked(vvi &board, vi &state)
{
	int res = 0;
	
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
		{
			int r = state[i] + dr[j];
			int c = i + dc[j];
			
			while(validPos(r, c) and board[r][c] != 1){
				r += dr[j];
				c += dc[j];
			}
			if(validPos(r, c) and board[r][c] == 1)
				res++;
		}
	}
	return res / 2;
}

void getNext(vvi &board, vi &state)
{
	vi resState, nextState;
	resState = nextState = state;
	vvi resBoard, nextBoard;
	resBoard = nextBoard = translate(state);
	
	int minAttacked = calcAttacked(board, state);
	
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
		{
			if(j != state[i])
			{
				nextState[i] = j;
				nextBoard[j][i] = 1;
				nextBoard[state[i]][i] = 0;
				
				int temp = calcAttacked(nextBoard, nextState);
				
				if(temp <= minAttacked){
					minAttacked = temp;
					resState = nextState;
					resBoard = translate(resState);
				}
				nextBoard[state[i]][i] = 1;
				nextBoard[j][i] = 0;
				nextState[i] = state[i];
			}
		}
	}
	state = resState;
	board = translate(state);
}

void hillClimbing(vvi &board, vi &state)
{
	vi nextState = state;
	vvi nextBoard = translate(state);
	
	while(1)
	{
		state = nextState;
		board = translate(state);
		getNext(nextBoard, nextState);
		
		if(state == nextState){
			printBoard(board);
			break;
		}
		else if(calcAttacked(board, state) == calcAttacked(nextBoard, nextState))
		{
			nextState[rand() % 8] = rand() % 8;
			nextBoard = translate(nextState);
		}
	}
}

int main()
{
	srand(time(NULL));
	vi state(8);
	vvi board(8, vi(8));
	
	makeRandom(board, state);
	hillClimbing(board, state);
	return 0;
}
