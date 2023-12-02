#include "../general.h"
#include <vector>

vector<pair<string, int>> DecomposeBatch(string batch)
{
	vector<pair<string, int>> vec;

	if (batch[0] == ' ')
		batch.erase(0, 1);

	for (int i = 0; i < batch.size(); i++)
		if (batch[i] == ',')
			batch.erase(i, 1);

	stringstream token(batch);
	while (!token.eof())
	{
		string col;
		int amount;
		token >> amount >> col;
		pair<string, int> p{col, amount};
		vec.push_back(p);
	}

	return vec;
}

int Day2_Part1(stringstream& input)
{
	int sum = 0;
	string line, trash;
	int maxRed = 12, maxGreen = 13, maxBlue = 14;
	while (!input.eof())
	{
		int gameId;

		input >> trash >> gameId;
		input.get(); //colon

		getline(input, line);
		stringstream ssline(line);
		string batch;
		bool badLine = false;
		while (getline(ssline, batch, ';') && !badLine)
		{
			auto pairs = DecomposeBatch(batch);

			for (int i = 0; i < pairs.size() && !badLine; i++)
			{
				if (pairs[i].first == "red")
				{
					if (pairs[i].second > maxRed)
						badLine = true;
				}
				else if (pairs[i].first == "green")
				{
					if (pairs[i].second > maxGreen)
						badLine = true;
				}
				else if (pairs[i].first == "blue")
					if (pairs[i].second > maxBlue)
						badLine = true;				
			}
		}

		if (!badLine)
			sum += gameId;
	}

	return sum;
}

int Day2_Part2(stringstream& input)
{
	
	string line, trash;
	int sum = 0;
	while (!input.eof())
	{
		int gameId;
		int minRed = 0, minGreen = 0, minBlue = 0;

		input >> trash >> gameId;
		input.get(); //colon

		getline(input, line);
		stringstream ssline(line);
		string batch;
		while (getline(ssline, batch, ';'))
		{
			auto pairs = DecomposeBatch(batch);

			for (int i = 0; i < pairs.size(); i++)
			{
				string col = pairs[i].first;
				int val = pairs[i].second;

				if (col == "red")
				{
					if (val > minRed)
						minRed = val;
				}
				else if (col == "green")
				{
					if (val > minGreen)
						minGreen = val;
				}
				else if (col == "blue")
					if (val > minBlue)
						minBlue = val;
			}
		}

		sum += minRed * minGreen * minBlue;

	}
	return sum;
}



void Day2(stringstream& input)
{
	cout << "Part 1 result is: " << Day2_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day2_Part2(input) << endl << endl;

	return;
}