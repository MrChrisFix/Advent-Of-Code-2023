#include "../general.h"
#include <map>
#include <numeric>

struct Node
{
	Node* left;
	Node* right;
	string name;
};

int StartPart1(string instr, Node* start)
{
	Node* current = start;
	int steps = 0;

	int j = 0;
	while (true)
	{
		if (j == instr.size())
		{
			if (current->name == "ZZZ")
				break;
			else
				j = 0;
		}
		if (instr[j] == 'R')
			current = current->right;
		else
			current = current->left;
		j++;
		steps++;
	}

	return steps;
}

long long StartPart2(string instr, vector<Node*> start)
{
	vector<int> stepsPerStart;
	stepsPerStart.resize(start.size());

	for (int i = 0; i < start.size(); i++)
	{
		int steps = 0;
		Node* node = start[i];
		int j = 0;
		while(true)
		{
			if (j == instr.size())
			{
				bool all = true;
				if (node->name.back() == 'Z')
					break;
				else
					j = 0;
			}
			if (instr[j] == 'R')
				node = node->right;
			else
				node = node->left;
			j++;
			steps++;
		}
		stepsPerStart[i] = steps;
	}

	long long steps = stepsPerStart[0];
	for (int i = 1; i < stepsPerStart.size(); i++)
	{
		steps = lcm(steps, stepsPerStart[i]);
	}
	return steps;
}

int Day8_Part1(stringstream& input)
{
	string instruction, name1, name2, name3;
	input >> instruction;
	map<string, Node> nodes;
	while(!input.eof())
	{
		input >> name1 >> name2 >> name2 >> name3;
		name3.pop_back();
		name2.pop_back();
		name2.erase(0, 1);
		nodes[name1].left = &nodes[name2];
		nodes[name1].right = &nodes[name3];
		nodes[name1].name = name1;
	}

	return StartPart1(instruction, &nodes["AAA"]); //14257
}

long long Day8_Part2(stringstream& input)
{
	string instruction, name1, name2, name3;
	input >> instruction;
	map<string, Node> nodes;
	vector<Node*> starting;
	while (!input.eof())
	{
		input >> name1 >> name2 >> name2 >> name3;
		name3.pop_back();
		name2.pop_back();
		name2.erase(0, 1);
		nodes[name1].left = &nodes[name2];
		nodes[name1].right = &nodes[name3];
		nodes[name1].name = name1;
		if (name1.back() == 'A')
			starting.push_back(&nodes[name1]);
	}

	return StartPart2(instruction, starting); //16187743689077
}


void Day8(stringstream& input)
{
	cout<<"Part 1 result is: " << Day8_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day8_Part2(input)<<endl<<endl;

	return;
}