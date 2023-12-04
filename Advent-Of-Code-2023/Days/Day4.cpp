#include "../general.h"
#include <vector>
#include <set>
#include <map>

int Day4_Part1(stringstream& input)
{
	int sum = 0;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		stringstream ssline(line);
		ssline >> line >> line;

		string num;
		bool firstPart = true;
		set<int> winnings;
		int n = 0;

		while (!ssline.eof())
		{
			ssline >> num;
			if (firstPart)
			{
				if (num == "|")
				{
					firstPart = false;
					continue;
				}
				winnings.insert(stoi(num));
			}
			else
			{
				if (winnings.contains(stoi(num)))
					n++;
			}
		}
		if (n > 0)
			sum += pow(2, n - 1);
	}

	return sum;
}

int Day4_Part2(stringstream& input)
{
	int cards = 0;
	map<int, int> Cards;

	while (!input.eof())
	{
		int cartNumber;
		string line;
		getline(input, line);
		stringstream ssline(line);
		ssline >> line >> cartNumber >> line;

		Cards[cartNumber]++; //Original

		string num;
		bool firstPart = true;
		set<int> winnings;

		int cnum = cartNumber;
		while (!ssline.eof())
		{
			ssline >> num;
			if (firstPart)
			{
				if (num == "|")
				{
					firstPart = false;
					continue;
				}
				winnings.insert(stoi(num));
			}
			else
			{
				if (winnings.contains(stoi(num)))
				{
					Cards[++cnum] += Cards[cartNumber]; //Copies
				}
			}
		}
		cards += Cards[cartNumber];
	}

	return cards;
}


void Day4(stringstream& input)
{
	cout<<"Part 1 result is: " << Day4_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day4_Part2(input)<<endl<<endl;

	return;
}