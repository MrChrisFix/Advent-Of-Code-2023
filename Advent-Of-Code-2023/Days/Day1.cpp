#include "../general.h"
#include <vector>

static void pop_front(string &s)
{
	if (s.empty()) return;
	if (s.size() == 1)
	{
		s = "";
		return;
	}

	for (int i = 1; i < s.size(); i++)
	{
		s[i-1] = s[i];
	}
	s.pop_back();
}

//Returns -1 if irrelevant text, 0 if uncomplete number, 1-9 if number
int checkForNumber(string text)
{
	string numbers[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	for (int i = 0; i < 9; i++)
	{
		if (numbers[i].starts_with(text))
		{
			if (numbers[i] == text)
				return i + 1;
			else
				return 0;
		}
	}
	return -1;
}

string Day1_Part1(stringstream& input)
{
	int sum = 0;
	string line;
	while (!input.eof())
	{
		input >> line;
		vector<int> numbersInLine;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] > '0' && line[i] <= '9')
				numbersInLine.push_back(line[i] - '0');
		}
		if (numbersInLine.size() > 0)
			sum += numbersInLine.front() * 10 + numbersInLine.back();
	}

	return to_string(sum);
}

string Day1_Part2(stringstream& input)
{
	int sum = 0;
	bool first = true;
	char sign;
	string word;
	string line;
	int linenum = 0;
	while (!input.eof())
	{
		input >> line;
		vector<int> numbersInLine;
		linenum++;

		for (int i = 0; i < line.size(); i++)
		{
			sign = line[i];
			if(sign > '0' && sign <= '9')
			{
				word = "";
				numbersInLine.push_back(sign - '0');
			}
			else
			{
				word.push_back(sign);
				do
				{
					int num = checkForNumber(word);

					if(num == 0)
						break;
					else if (num < 0)
					{
						pop_front(word);
					}
					else
					{
						numbersInLine.push_back(num);
						pop_front(word);
						break;
					}
				} while (word.size() > 0);				
			}
		}

		if(numbersInLine.size() > 0)
			sum += numbersInLine.front() * 10 + numbersInLine.back();
	}

	return to_string(sum);
}



void Day1(stringstream& input)
{
	cout<<"Part 1 result is: " << Day1_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day1_Part2(input)<<endl<<endl;

	return;
}