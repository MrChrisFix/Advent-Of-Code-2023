#include "../general.h"
#include <map>
#include <set>
#include <vector>

#define ll long long

struct Mapping
{
	ll dest, source, range;
	bool exists(ll src)
	{
		return src >= source && src < source + range;
	}
	ll getNum(ll src)
	{
		ll offset = src - source;
		return dest + offset;
	}
};

struct Seed
{
	ll start, range;
	bool isValid(ll seed)
	{
		return seed >= start && seed < start + range;
	}
};

bool isValidSeed(ll seed, vector<Seed> seeds)
{
	for (int i = 0; i < seeds.size(); i++)
	{
		if (seeds[i].isValid(seed))
			return true;
	}
	return false;
}

ll FindNum(vector<Mapping> map, ll num)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].exists(num))
			return map[i].getNum(num);
	}
	return num;
}

ll Day5_Part1(stringstream& input)
{
	vector<Mapping> seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemp, tempToHum, humToLocation;
	vector<vector<Mapping>*> maps = { &seedToSoil, &soilToFertilizer, &fertilizerToWater, &waterToLight, &lightToTemp, &tempToHum, &humToLocation };
	set<ll> seeds;
	int m = -1;
	while (!input.eof())
	{
		string tr, line;
		ll seed;
		getline(input, line);
		if (line.empty())
		{
			m++;
			getline(input, line); //trash
			continue;
		}
		stringstream sline(line);
		if (m == -1)
		{
			sline >> tr;
			while (!sline.eof())
			{
				sline >> seed;
				seeds.insert(seed);
			}
		}
		else
		{
			ll dest, source, range;
			sline >> dest >> source >> range;
			Mapping mapping{ dest, source, range };
			maps[m]->push_back(mapping);
		}

	}
	
	ll num = LLONG_MAX;
	for (auto it = seeds.begin(); it != seeds.end(); it++)
	{
		ll cur = *it;

		for (int i = 0; i < maps.size(); i++)
		{
			cur = FindNum(*maps[i], cur);
		}

		if (cur < num)
			num = cur;
	}

	return num; //199602917
}

ll Day5_Part2(stringstream& input)
{
	vector<Mapping> seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemp, tempToHum, humToLocation;
	vector<vector<Mapping>*> maps = { &seedToSoil, &soilToFertilizer, &fertilizerToWater, &waterToLight, &lightToTemp, &tempToHum, &humToLocation };
	vector<Seed> seeds;
	int m = -1;
	while (!input.eof())
	{
		string tr, line;
		ll seed;
		getline(input, line);
		if (line.empty())
		{
			m++;
			getline(input, line); //trash
			continue;
		}
		stringstream sline(line);
		if (m == -1)
		{
			sline >> tr;
			while (!sline.eof())
			{
				ll range;
				sline >> seed >> range;
				seeds.push_back(Seed{ seed, range });
			}
		}
		else
		{
			ll dest, source, range;
			sline >> dest >> source >> range;
			Mapping mapping{ source, dest, range }; //Inverted
			maps[m]->push_back(mapping);
		}
	}

	ll num = 0;
	
	while (true)
	{
		ll cur = num;
		for (int i = maps.size()-1; i >= 0; i--)
		{
			cur = FindNum(*maps[i], cur);
		}

		if (isValidSeed(cur, seeds))
		{
			break;
		}
		num++;
	}

	return num; //2254686
}


void Day5(stringstream& input)
{
	cout<<"Part 1 result is: " << Day5_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day5_Part2(input)<<endl<<endl;

	return;
}