#include "../general.h"
#include <algorithm>
#include <numeric>

void Difference(vector<int> &nums)
{
	vector<int> Diff;
	for (int i = 1; i < nums.size(); i++)
		Diff.push_back(nums[i] - nums[i - 1]);
	if (accumulate(Diff.begin(), Diff.end(), 0) == 0)
	{
		Diff.push_back(0);
		Diff.insert(Diff.begin(), 0);
	}
	else
	{
		Difference(Diff);
		nums.push_back(Diff.back() + nums.back());
		nums.insert(nums.begin(), nums[0] - Diff[0]);
	}
}

long long Day9_Part1(stringstream& input)
{
	vector<vector<int>> Numbers;
	while (!input.eof())
	{
		vector<int> LineNum;
		int num;
		string line;
		getline(input, line); 
		stringstream sline(line);
		while(sline >> num)
			LineNum.push_back(num);
		Numbers.push_back(LineNum);
	}

	long long sum = 0;
	for (int i = 0; i < Numbers.size(); i++)
	{
		Difference(Numbers[i]);
		sum += Numbers[i].back();
	}
	return sum; //2098530125
}

long long Day9_Part2(stringstream& input)
{
	vector<vector<int>> Numbers;
	while (!input.eof())
	{
		vector<int> LineNum;
		int num;
		string line;
		getline(input, line);
		stringstream sline(line);
		while (sline >> num)
			LineNum.push_back(num);
		Numbers.push_back(LineNum);
	}

	long long sum = 0;
	for (int i = 0; i < Numbers.size(); i++)
	{
		Difference(Numbers[i]);
		sum += Numbers[i][0];
	}
	return sum; //1016
}


void Day9(stringstream& input)
{
	cout<<"Part 1 result is: " << Day9_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day9_Part2(input)<<endl<<endl;

	return;
}