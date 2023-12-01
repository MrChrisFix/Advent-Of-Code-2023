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

	for (int i = 0; i < s.size() - 1; i++)
	{
		s[i] = s[i + 1];
	}
	s.pop_back();
}

bool isRelevant(string test)
{
	string numbers[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	for (int i = 0; i < 9; i++)
	{
		if (numbers[i].starts_with(test))
			return true;
	}
	return false;
}

int checkIfNumber(string test)
{
	if (test == "one") return 1;
	if (test == "two") return 2;
	if (test == "three") return 3;
	if (test == "four") return 4;
	if (test == "five") return 5;
	if (test == "six") return 6;
	if (test == "seven") return 7;
	if (test == "eight") return 8;
	if (test == "nine") return 9;
	return 0;
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
					if (isRelevant(word))
					{
						int num = checkIfNumber(word);
						if (num != 0)
						{
							numbersInLine.push_back(num);
							pop_front(word);
						}
						break;
					}
					else
					{
						pop_front(word);
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