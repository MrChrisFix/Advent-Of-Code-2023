#include "../general.h"
#include <algorithm>
#include <map>

void Print(vector<string> Grid)
{
	cout << endl;
	for (int i = 0; i < Grid.size(); i++)
		cout << Grid[i] << endl;
	cout << endl;
}

int Day14_Part1(stringstream& input)
{
	vector<string> Grid;
	while (!input.eof())
	{
		string line;
		input >> line;
		Grid.push_back(line);
	}

	for (int k = 0; k < Grid.size() - 1; k++)
		for (int i = 0; i < Grid[0].size(); i++)
			for (int j = 0; j < Grid.size() - 1; j++)
			{
				if (Grid[j][i] == '.' && Grid[j + 1][i] == 'O')
				{
					Grid[j][i] = 'O', Grid[j + 1][i] = '.';
				}
			}

	int weight = 0;
	for (int i = 0; i < Grid.size(); i++)
	{
		int score = Grid.size() - i;
		weight += score * count(Grid[i].begin(), Grid[i].end(), 'O');
	}

	return weight;
}

void North(vector<string>& Grid, vector<vector<int>> Walls)
{
	for (int i = 0; i < Grid[0].size(); i++)
	{
		string st;
		for (int j = 0; j < Grid.size(); j++)
		{
			st.push_back(Grid[j][i]);
		}
		string s = st;
		size_t start = 0;
		for (auto wall : Walls[i])
		{
			sort(s.begin() + start, s.begin() + wall, greater<char>());
			start = wall + 1;
		}

		if (s != st)
		{
			for (int j = 0; j < Grid.size(); j++)
			{
				Grid[j][i] = s[j];
			}
		}

	}
}

void West(vector<string>& Grid, vector<vector<int>> Walls)
{
	for (int i = 0; i < Grid.size(); i++)
	{
		string s = Grid[i];
		size_t start = 0;
		for (auto wall : Walls[i])
		{
			sort(s.begin() + start, s.begin() + wall, greater<char>());
			start = wall + 1;
		}
		Grid[i] = s;
	}
}

void South(vector<string>& Grid, vector<vector<int>> Walls)
{
	for (int i = 0; i < Grid[0].size(); i++)
	{
		string st;
		for (int j = 0; j < Grid.size(); j++)
		{
			st.push_back(Grid[j][i]);
		}
		string s = st;
		size_t start = 0;
		for (auto wall : Walls[i])
		{

			sort(s.begin() + start, s.begin() + wall);
			start = wall + 1;
		}

		if (s != st)
		{
			for (int j = 0; j < Grid.size(); j++)
			{
				Grid[j][i] = s[j];
			}
		}
	}
}

void East(vector<string>& Grid, vector<vector<int>> Walls)
{
	for (int i = 0; i < Grid.size(); i++)
	{
		string s = Grid[i];
		size_t start = 0;
		for (auto wall : Walls[i])
		{
			sort(s.begin() + start, s.begin() + wall);
			start = wall + 1;
		}
		Grid[i] = s;
	}
}


void RotateRight(vector<string>& vec)
{
	vector<string> transp;
	for (int j = 0; j < vec[0].size(); j++)
	{
		string s;
		for (int i = 0; i < vec.size(); i++)
		{
			s.insert(s.begin(), vec[i][j]);
		}
		transp.push_back(s);
	}
	vec = transp;
}


int Day14_Part2(stringstream& input)
{
	vector<string> Grid;
	while (!input.eof())
	{
		string line;
		input >> line;
		Grid.push_back(line);
	}
	vector<vector<int>> HorWalls;
	vector<vector<int>> VerWalls;

	for (int i = 0; i < Grid.size(); i++)
	{
		vector<int> lineWalls;
		for (int j = 0; j < Grid[i].size(); j++)
			if (Grid[i][j] == '#')
				lineWalls.push_back(j);
		lineWalls.push_back(Grid[i].size());
		HorWalls.push_back(lineWalls);
	}

	for (int i = 0; i < Grid[0].size(); i++)
	{
		vector<int> colWalls;
		for (int j = 0; j < Grid.size(); j++)
			if (Grid[j][i] == '#')
				colWalls.push_back(j);

		colWalls.push_back(Grid.size());
		VerWalls.push_back(colWalls);
	}

	vector<vector<char*>> Transposed;

	for (int j = 0; j < Grid[0].size(); j++)
	{
		vector<char*> column;
		for (int i = 0; i < Grid.size(); i++)
		{
			column.push_back(&Grid[i][j]);
		}
		Transposed.push_back(column);
	}

	map<vector<string>, int> Positions;

	for (size_t i = 0; i < 1000000000; i++)
	{
		North(Grid, VerWalls);
		West(Grid, HorWalls);
		South(Grid, VerWalls);
		East(Grid, HorWalls);

		if (Positions.contains(Grid))
		{
			long long initial = Positions[Grid];
			long long cycles = Positions.size()-initial;
			long long finalCycleElem = (1000000000 - initial) % cycles;

			long long PosElem = finalCycleElem + initial-1;
			auto it = Positions.begin();
			while (it->second != PosElem)
				it++;

			Grid = it->first;
			break;
		}
		else
		{
			Positions[Grid] = i;
		}
		//Print(Grid);
	}


	int weight = 0;
	for (int i = 0; i < Grid.size(); i++)
	{
		int score = Grid.size() - i;
		weight += score * count(Grid[i].begin(), Grid[i].end(), 'O');
	}

	return weight; //105606
}


void Day14(stringstream& input)
{
	cout << "Part 1 result is: " << Day14_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day14_Part2(input) << endl << endl;

	return;
}