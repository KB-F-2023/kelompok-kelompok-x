#include <bits/stdc++.h>
using namespace std;
#define fr front
#define tab '\t'
#define endl '\n'

typedef struct
{
	string str;
	int col, numQueens;
}
state;

state defState;
string defStr = "";
set <string> vis;
int solutions;

void init()
{
	for(int i = 0; i < 64; ++i)
		defStr += (char) 100;
	defState.str = defStr;
	defState.col = 0;
	defState.numQueens = 0;
}

void str_to_board(string str, int board[8][8])
{
	int itr = 0;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
		{
			board[i][j] = (int) (str[itr] - 100);
			itr++;
		}
	}
}

string board_to_str(int board[8][8])
{
	string res = "";
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
			res += (char) (board[i][j] + 100);
	}
	return res;
}

void marking(int board[8][8], int i, int col, int mark)
{
	for(int j = 0; j < 8; ++j){
		if(j != col) board[i][j] += mark;
		if(j != i) board[j][col] += mark;
	}
	for(int j = 1; j < 8; ++j){
		if(i - j >= 0 and col - j >= 0) board[i - j][col - j] += mark;
		if(i + j < 8 and col + j < 8) board[i + j][col + j] += mark;
		if(i - j >= 0 and col + j < 8) board[i - j][col + j] += mark;
		if(i + j < 8 and col - j >= 0) board[i + j][col - j] += mark;
	}
}

void bfs()
{
	queue <state> q;
	q.push(defState);
	
	while(!q.empty())
	{
		state curState = q.fr();
		
		int board[8][8];
		str_to_board(curState.str, board);
		
		if(!vis.count(curState.str))
			vis.insert(curState.str);
		q.pop();
		
		if(curState.numQueens >= 8)
		{
			for(int i = 0; i < 8; ++i){
				for(int j = 0; j < 8; ++j)
					cout << board[i][j] << tab;
				cout << endl;
			}
			cout << endl;
			solutions++;
			continue;
		}
		for(int i = 0; i < 8; ++i)
		{
			if(board[i][curState.col] > -1)
			{
				board[i][curState.col] = 1;
				
				marking(board, i, curState.col, -1);
				string nextStr = board_to_str(board);
				
				if(!vis.count(nextStr))
				{
					vis.insert(nextStr);
					
					state nextState = curState;
					nextState.str = nextStr;
					nextState.col++;
					nextState.numQueens++;
					
					q.push(nextState);
				}
				marking(board, i, curState.col, 1);
			}
		}
	}
}

int main()
{
	init();
	bfs();
	cout << solutions << endl;
	return 0;
}
