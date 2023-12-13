#include "../general.h"

vector<string> Transpose(vector<string> vec)
{
	vector<string> transp;
	for (int j = 0; j < vec[0].size(); j++)
	{
		string s;
		for (int i = 0; i < vec.size(); i++)
		{
			s.push_back(vec[i][j]);
		}
		transp.push_back(s);
	}
	return transp;
}

int FindLine(vector<string> vec, bool correction = false)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		int changedLines = 0;
		bool good = true;
		for (int k = 0; k < vec.size() / 2 && good; k++)
		{
			if (i - k >= 0 && i + k + 1 <= vec.size() - 1)
			{
				if (vec[i - k] != vec[i + k + 1] && correction)
				{
					string s1 = vec[i - k];
					string s2 = vec[i + k + 1];
					int nonmaching = 0;
					for (int S = 0; S < s1.size(); S++)
						if (s1[S] != s2[S])
							nonmaching++;
					if (nonmaching != 1)
					{
						good = false;
					}
					else
					{
						changedLines++;
					}
				}
				else if (vec[i - k] != vec[i + k + 1])
				{
					good = false;
				}
			}
		}
		if (good && (changedLines == 1 || !correction))
		{
			return i;
		}
	}
	return -1;
}


int Day13_Part1(stringstream& input)
{
	vector<vector<string>> Maps;
	string line;
	vector<string> current;
	while (getline(input, line))
	{
		if (line.empty())
		{
			if (!current.empty())
				Maps.push_back(current);
			current.clear();
		}
		else
		{
			current.push_back(line);
		}
	}
	Maps.push_back(current);

	int sum = 0;
	for (auto vec : Maps)
	{
		bool found = false;
		//Horizontal
		int res = FindLine(vec, false);
		if (res != -1)
		{
			sum += (res + 1) * 100;
		}
		else
		{
			//Vertical
			vec = Transpose(vec);
			res = FindLine(vec, false);
			sum += res + 1;
		}
	}

	return sum; //33735
}

int Day13_Part2(stringstream& input)
{
	vector<vector<string>> Maps;
	string line;
	vector<string> current;
	while (getline(input, line))
	{
		if (line.empty())
		{
			if (!current.empty())
				Maps.push_back(current);
			current.clear();
		}
		else
		{
			current.push_back(line);
		}
	}
	Maps.push_back(current);

	int sum = 0;
	for (auto vec : Maps)
	{
		bool found = false;
		//Horizontal
		int res = FindLine(vec, true);
		if (res != -1)
		{
			sum += (res + 1) * 100;
		}
		else
		{
			//Vertical
			vec = Transpose(vec);
			res = FindLine(vec, true);
			sum += res + 1;
		}
	}

	return sum; //38063
}


void Day13(stringstream& input)
{
	cout << "Part 1 result is: " << Day13_Part1(input) << endl;
	input.clear();
	input.seekg(0);
	cout << "Part 2 result is: " << Day13_Part2(input) << endl << endl;

	return;
}