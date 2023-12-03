#include "../general.h"
#include <vector>
#include <set>
#include <map>

int Day3_Part1(stringstream& input)
{
	vector<vector<char>> Grid;
	while (!input.eof())
	{
		string line;
		input >> line;
		vector<char> charLine(line.begin(), line.end());
		Grid.push_back(charLine);
	}
	int sum = 0;

	int curNum = 0;
	bool validNum = false;
	for(int i=0; i< Grid.size(); i++)
	{
		for (int j = 0; j < Grid[i].size(); j++)
		{
			if (isdigit(Grid[i][j]))
			{
				curNum = curNum * 10 + Grid[i][j] - '0';

				if (i != 0)
				{
					if (!isdigit(Grid[i - 1][j]) && Grid[i - 1][j] != '.')										validNum = true;
					if (j != 0 && !isdigit(Grid[i - 1][j - 1]) && Grid[i - 1][j - 1] != '.')					validNum = true;
					if (j != Grid[i].size() - 1 && !isdigit(Grid[i - 1][j + 1]) && Grid[i - 1][j + 1] != '.')	validNum = true;
				}
				if (i != Grid.size() - 1)
				{
					if (!isdigit(Grid[i + 1][j]) && Grid[i + 1][j] != '.')										validNum = true;
					if (j != 0 && !isdigit(Grid[i + 1][j - 1]) && Grid[i + 1][j - 1] != '.')					validNum = true;
					if (j != Grid[i].size() - 1 && !isdigit(Grid[i + 1][j + 1]) && Grid[i + 1][j + 1] != '.')	validNum = true;
				}
				if (j != 0 && !isdigit(Grid[i][j - 1]) && Grid[i][j - 1] != '.')								validNum = true;
				if (j != Grid[i].size() - 1 && !isdigit(Grid[i][j + 1]) && Grid[i][j + 1] != '.')				validNum = true;

			}
			else
			{
				if (validNum)
					sum += curNum;
				validNum = false;
				curNum = 0;
			}
		}
		if (validNum)
			sum += curNum;
		validNum = false;
		curNum = 0;
	}

	return sum;
}

int Day3_Part2(stringstream& input)
{
	vector<vector<char>> Grid;
	while (!input.eof())
	{
		string line;
		input >> line;
		vector<char> charLine(line.begin(), line.end());
		Grid.push_back(charLine);
	}
	
	int sum = 0;

	map<pair<int, int>, vector<int>> Gears;
	set<pair<int, int>> numsToGears;
	int curNum = 0;
	for (int i = 0; i < Grid.size(); i++)
	{
		for (int j = 0; j < Grid[i].size(); j++)
		{
			if (isdigit(Grid[i][j]))
			{
				curNum = curNum * 10 + Grid[i][j] - '0';

				if (i != 0)
				{
					if (Grid[i - 1][j] == '*')									numsToGears.insert(pair<int, int>(i - 1, j));
					if (j != 0 && Grid[i - 1][j - 1] == '*')					numsToGears.insert(pair<int, int>(i - 1, j - 1));
					if (j != Grid[i].size() - 1 && Grid[i - 1][j + 1] == '*')	numsToGears.insert(pair<int, int>(i - 1, j + 1));
				}
				if (i != Grid.size() - 1)
				{
					if (Grid[i + 1][j] == '*')									numsToGears.insert(pair<int, int>(i + 1, j));
					if (j != 0 && Grid[i + 1][j - 1] == '*')					numsToGears.insert(pair<int, int>(i + 1, j - 1));
					if (j != Grid[i].size() - 1 && Grid[i + 1][j + 1] == '*')	numsToGears.insert(pair<int, int>(i + 1, j + 1));
				}
				if (j != 0 && Grid[i][j - 1] == '*')							numsToGears.insert(pair<int, int>(i, j - 1));
				if (j != Grid[i].size() - 1 && Grid[i][j + 1] == '*')			numsToGears.insert(pair<int, int>(i, j + 1));

			}
			else
			{
				for (auto it = numsToGears.begin(); it != numsToGears.end(); it++)
				{
					pair<int, int> pos(it->first, it->second);
					Gears[pos].push_back(curNum);
				}
				numsToGears.clear();
				curNum = 0;
			}
		}
		for (auto it = numsToGears.begin(); it != numsToGears.end(); it++)
		{
			pair<int, int> pos(it->first, it->second);
			Gears[pos].push_back(curNum);
		}
		numsToGears.clear();
		curNum = 0;
	}


	for (auto it = Gears.begin(); it != Gears.end(); it++)
	{
		if (it->second.size() == 2)
		{
			sum += it->second[0] * it->second[1];
		}
	}


	return sum;
}


void Day3(stringstream& input)
{
	cout<<"Part 1 result is: " << Day3_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day3_Part2(input)<<endl<<endl;

	return;
}