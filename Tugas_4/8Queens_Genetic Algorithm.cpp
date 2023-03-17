#include <bits/stdc++.h>
using namespace std;
#define psi pair<string, int>
#define mp make_pair
#define fi first
#define sc second
#define vi vector<int>
#define vvi vector<vi>
#define vs vector<string>
#define vpsi vector<psi>
#define pb push_back

int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

void printBoard(vvi board)
{
	cout << endl;
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
			cout << board[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

vvi translate(string chromosome)
{
	vvi board(8, vi(8));
	for(int i = 0; i < 8; ++i)
		board[chromosome[i] - '0'][i] = 1;
	return board;
}

bool validPos(int r, int c)
{
	return (r >= 0 and r < 8 and c >= 0 and c < 8);
}

bool finished(vpsi population)
{
	for(int i = 0; i < 100; ++i){
		if(population[i].sc == 28)
		{
			cout << "Answer :";
			printBoard(translate(population[i].fi));
			return 1;	
		}
	}
	return 0;
}

char randomGene()
{
	return '0' + (rand() % 8);
}

string randomChromosome()
{
	string res = string(8, '0');
	for(int i = 0; i < 8; ++i)
		res[i] = randomGene();
	return res;
}

vs randomPopulation()
{
	vs population(100);
	set <string> appeared;
	
	for(int i = 0; i < 100; ++i)
	{
		do population[i] = randomChromosome();
		while(appeared.count(population[i]));
		
		appeared.insert(population[i]);
	}
	return population;
}

int fitness(string chromosome)
{
	vvi board = translate(chromosome);
	int attacked = 0;
	
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j)
		{
			int r = (chromosome[i] - '0') + dr[j];
			int c = i + dc[j];
			
			while(validPos(r, c) and board[r][c] != 1){
				r += dr[j];
				c += dc[j];
			}
			if(validPos(r, c) and board[r][c] == 1)
				attacked++;
		}
	}
	return 28 - (attacked / 2);
}

vs selection(vpsi population)
{
	vs parents;
	for(int p = 0; p < 10; ++p)
	{
		int maxFitness = 0;
		string bestParent = population[0].fi;
		
		for(int k = 0; k < 10; ++k)
		{
			int candidate = rand() % 100;
			
			if(population[candidate].sc > maxFitness)
			{
				maxFitness = population[candidate].sc;
				bestParent = population[candidate].fi;
			}
		}
		parents.pb(bestParent);
	}
	return parents;	
}

void mutation(vs &parents)
{
	for(int i = 0; i < 100; ++i)
	{
		int index = rand() % 8;
		parents[i][index] = randomGene();
	}
}

void crossover(vs &parents)
{
	for(int i = 0; i < 9; ++i){
		for(int j = i + 1; j < 10; ++j)
		{
			string parent1 = parents[i];
			string parent2 = parents[j];
			string child1, child2;
			int part = rand() % 7;
			
			for(int itr = 0; itr <= part; ++itr){
				child1 += parent1[itr];
				child2 += parent2[itr];
			}
			for(int itr = part + 1; itr < 8; ++itr){
				child1 += parent2[itr];
				child2 += parent1[itr];
			}
			parents.pb(child1);
			parents.pb(child2);
		}
	}
}

vpsi objective(vs parents)
{
	vpsi population(100);
	for(int i = 0; i < 100; ++i)
	{
		int fitnessValue = fitness(parents[i]);
		population[i] = mp(parents[i], fitnessValue);
	}
	return population;
}

void geneticAlgorithm()
{
	int generation = 1;
	vs parents = randomPopulation();
	vpsi population = objective(parents);
	
	while(true){
		if(finished(population)){
			cout << "Generation : " << generation << endl;
			return;
		}
		parents = selection(population);
		crossover(parents);
		mutation(parents);
		population = objective(parents);
		generation++;
	}
}

int main()
{
	srand(time(NULL));
	geneticAlgorithm();
	return 0;
}