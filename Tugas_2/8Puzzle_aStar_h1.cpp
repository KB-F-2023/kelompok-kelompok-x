#include <bits/stdc++.h>
using namespace std;
#define pqueue priority_queue
#define endl '\n'

typedef struct
{
	string str;
	int dist, Tdist;
}
state;

class cmp
{
	public:
		bool operator()(state a, state b)
		{
			if(b.Tdist == a.Tdist)
				return b.dist < a.dist;
			return b.Tdist < a.Tdist;
		}	
};

map <string, int> Sdist, heur;
map <string, string> prev;
set <string> vis;
int loop;

int getPos(int idx, int dest)
{
	int row = idx / 3;
	int col = idx % 3;
	
	if(dest == 0)
		return (col == 0 ? -1 : 3 * row + col - 1);		// Left
	else if(dest == 1)
		return (col == 2 ? -1 : 3 * row + col + 1);		// Right
	else if(dest == 2)
		return (row == 0 ? -1 : 3 * (row - 1) + col);	// Top
	else
		return (row == 2 ? -1 : 3 * (row + 1) + col);	// Bottom
}

int getHeur(string cur, string finish)
{
	if(heur.count(cur))
		return heur[cur];
	int res = 0;
	
	for(int i = 0; i < 9; ++i){
		if(finish[i] != '0')
			res += (finish[i] != cur[i]);
	}
	return heur[cur] = res;
}

void printPuzzle(string str)
{
	for(int i = 0; i <= 2; ++i){
		for(int j = 0; j <= 2; ++j)
			cout << str[3*i+j] << " ";
		cout << endl;
	}
	cout << endl;
}

void aStar(string start, string finish)
{
	pqueue <state, vector<state>, cmp> pq;
	Sdist[start] = 0;
	
	state init = {start, 0, getHeur(start, finish)};
	pq.push(init);
	
	while(!pq.empty())
	{
		state curState = pq.top();
		pq.pop();
		
		if(vis.count(curState.str))
			continue;
		vis.insert(curState.str);
		
		printPuzzle(curState.str);
		cout << "g(n) : " << curState.dist << endl;
		cout << "h(n) : " << getHeur(curState.str, finish) << endl << endl;
		cout << string(25, '-') << endl << endl;
		
		if(curState.str == finish)
			break;
		int kosong = -1;
		
		for(int i = 0; i < 9; ++i){
			if(curState.str[i] == '0'){
				kosong = i;
				break;
			}
		}
		for(int i = 0; i < 4; ++i)
		{
			string nextStr = curState.str;
			int nextPos = getPos(kosong, i);
			int nextHeur = 0;
			
			if(nextPos != -1)
			{
				swap(nextStr[kosong], nextStr[nextPos]);
				nextHeur = getHeur(nextStr, finish);
				
				if(!Sdist.count(nextStr) or curState.dist + 1 < Sdist[nextStr])
				{
					Sdist[nextStr] = curState.dist + 1;
					prev[nextStr] = curState.str;
					
					state nextState = curState;
					nextState.str = nextStr;
					nextState.dist++;
					nextState.Tdist = nextState.dist + heur[nextStr];
					
					pq.push(nextState);
				}
			}
		}
		loop++;
	}
}

void backtrack(string cur, int depth)
{
	if(depth > 0)
		backtrack(prev[cur], depth - 1);
	cout << "Step " << depth << endl;
	printPuzzle(cur);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string start = "724506831";
	string finish = "012345678";
	aStar(start, finish);
	
	cout << "Total Distance : " << Sdist[finish] << endl;
	cout << "Total Loop : " << loop << endl << endl;
	backtrack(finish, 26);
	return 0;
}
