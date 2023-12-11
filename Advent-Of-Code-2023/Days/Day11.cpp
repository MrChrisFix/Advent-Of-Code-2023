#include "../general.h"

#define ll long long

int Day11_Part1(stringstream& input)
{
	vector<string> universe;

	//Expanding the universe
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.find('#') == line.npos)
			universe.push_back(line);
		universe.push_back(line);
	}
	for (int col = 0; col < universe[0].size(); col++)
	{
		bool hasGalaxy = false;
		for (int row = 0; row < universe.size(); row++)
		{
			if (universe[row][col] == '#')
			{
				hasGalaxy = true;
				break;
			}
		}
		if (hasGalaxy)
			continue;

		for (int row = 0; row < universe.size(); row++)
		{
			universe[row].insert(col, ".");
		}
		col++;

	}

	vector<pair<int, int>> Galaxies;
	int y = 0;
	for (string line : universe)
	{
		for (int x = 0; x < line.size(); x++)
			if (line[x] == '#')
				Galaxies.push_back(pair<int, int>(x, y));
		y++;
	}

	int sum = 0;

	for (int i = 0; i < Galaxies.size(); i++)
	{
		for (int j = i + 1; j < Galaxies.size(); j++)
		{
			int dist = abs(Galaxies[i].first - Galaxies[j].first) + abs(Galaxies[i].second - Galaxies[j].second);
			sum += dist;
		}
	}

	return sum;
}

ll Day11_Part2(stringstream& input)
{
	vector<string> universe;
	vector<ll> Ys, Xs;
	const int EXP = 1000000;

	//Expanding the universe
	ll Y = 0;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.find('#') == line.npos)
			Y += EXP;
		else
			Y++;
		Ys.push_back(Y);
		universe.push_back(line);
	}
	ll X = 0;
	for (int col = 0; col < universe[0].size(); col++)
	{
		bool hasGalaxy = false;
		for (int row = 0; row < universe.size(); row++)
		{
			if (universe[row][col] == '#')
			{
				hasGalaxy = true;
				break;
			}
		}
		if (hasGalaxy)
			X++;
		else
			X += EXP;
		Xs.push_back(X);
	}

	//Finding galaxies
	vector<pair<ll, ll>> Galaxies;
	int y = 0;
	for (string line : universe)
	{
		for (int x = 0; x < line.size(); x++)
			if (line[x] == '#')
			{
				Galaxies.push_back(pair<ll, ll>(Xs[x], Ys[y]));
			}
		y++;
	}

	//Calculating the distances
	ll sum = 0;
	for (int i = 0; i < Galaxies.size(); i++)
	{
		for (int j = i + 1; j < Galaxies.size(); j++)
		{
			int dist = abs(Galaxies[i].first - Galaxies[j].first) + abs(Galaxies[i].second - Galaxies[j].second);
			sum += dist;
		}
	}

	return sum;
}


void Day11(stringstream& input)
{
	cout<<"Part 1 result is: " << Day11_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day11_Part2(input)<<endl<<endl;

	return;
}