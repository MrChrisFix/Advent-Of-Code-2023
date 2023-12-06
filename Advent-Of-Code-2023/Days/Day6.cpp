#include "../general.h"
#include <algorithm>

int Day6_Part1(stringstream& input)
{
	vector<int> times, distances;
	string t, d;

	getline(input, t);
	getline(input, d);
	stringstream st(t), sd(d);
	st >> t;
	sd >> d;
	while (!st.eof())
	{
		int num;
		st >> num;
		times.push_back(num);
		sd >> num;
		distances.push_back(num);
	}

	int product = 1;
	for (int i = 0; i < times.size(); i++)
	{
		int delta = times[i] * times[i] - 4 * distances[i];
		float sqrtDelta = sqrt(delta);
		int x1 = floor((-times[i] - sqrtDelta) / (-2));
		int x2 = floor((-times[i] + sqrtDelta) / (-2));
		int range = x1 - x2;
		if ((int)sqrtDelta * (int)sqrtDelta == delta) //Perfect square
			range--;
		product *= range;
	}

	return product; //1710720
}

int Day6_Part2(stringstream& input)
{
	string s;
	long long time, distance;
	input >> s;
	getline(input, s);
	s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
	time = stoll(s);

	input >> s;
	getline(input, s);
	s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
	distance = stoll(s);

	long long delta = time * time - 4 * distance;
	long double sqrtDelta = sqrtl(delta);
	int x1 = floor((-time - sqrtDelta) / (-2));
	int x2 = floor((-time + sqrtDelta) / (-2));
	int range = x1 - x2;
	if ((long long)sqrtDelta * (long long)sqrtDelta == delta) //Perfect square
		range--;

	return range; // 35349468
}


void Day6(stringstream& input)
{
	cout<<"Part 1 result is: " << Day6_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day6_Part2(input)<<endl<<endl;

	return;
}