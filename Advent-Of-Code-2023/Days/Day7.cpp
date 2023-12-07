#include "../general.h"
#include <map>
#include <set>

enum class HAND
{
	FIVE_A_KIND, FOUR_A_KIND, FULL_HOUSE, THREE_A_KIND, TWO_PAIR, ONE_PAIR, HIGH
};

HAND evaluateHand(string hand, bool wildcard = false)
{
	map<char, int> eval;
	for (int i = 0; i < hand.size(); i++)
	{
		eval[hand[i]]++;
	}

	switch (eval.size())
	{
	case 1:
	{
		return HAND::FIVE_A_KIND;
		break;
	}
	case 2:
	{
		// 4 1 or 3 2
		if (eval.contains('J') && wildcard)
			return HAND::FIVE_A_KIND;
		int size = eval.begin()->second;
		if (size == 4 || size == 1)
			return HAND::FOUR_A_KIND;
		else
			return HAND::FULL_HOUSE;
		break;
	}
	case 3:
	{
		// 3 1 1 or 2 2 1
		int jockerSize = eval.contains('J') ? eval['J'] : 0;
		auto it = eval.begin();
		int size1 = it->second;
		int size2 = (++it)->second;
		if (size1 == 2 || size2 == 2)
		{
			if (jockerSize == 2 && wildcard)
				return HAND::FOUR_A_KIND;
			else if (jockerSize == 1 && wildcard)
				return HAND::FULL_HOUSE;
			return HAND::TWO_PAIR;
		}
		else
		{
			if (jockerSize != 0 && wildcard || !wildcard)
				return HAND::THREE_A_KIND;
			else
				return HAND::FOUR_A_KIND;
		}
		break;
	}
	case 4:
	{
		// 2 1 1 1 
		if (eval.contains('J') && wildcard)
			return HAND::THREE_A_KIND;
		return HAND::ONE_PAIR;
		break;
	}
	case 5:
	{
		if (eval.contains('J') && wildcard)
			return HAND::ONE_PAIR;
		return HAND::HIGH;
		break;
	}
	default:
		break;
	}
}

struct Hand
{
	Hand(string h, int b, bool part2 = false)
	{
		hand = h, bid = b;
		eval = evaluateHand(hand, part2);
		insertValues(part2);
	}
	string hand;
	int bid;
	HAND eval;
	vector<int> values;
private:
	void insertValues(bool part2)
	{
		for (char c : hand)
		{
			if (isdigit(c))
				values.push_back(c - '0');
			else
			{
				if (!part2)
				{
					if (c == 'J') values.push_back(11);
				}
				else
				{
					if (c == 'J') values.push_back(1);
				}
				if (c == 'T') values.push_back(10);
				else if (c == 'Q') values.push_back(12);
				else if (c == 'K') values.push_back(13);
				else if (c == 'A') values.push_back(14);
			}
		}
	}
};

auto cmp = [](Hand a, Hand b) {
	if (a.eval == b.eval)
	{
		for (int i = 0; i < a.values.size(); i++)
		{
			if (a.values[i] == b.values[i])
				continue;

			return a.values[i] < b.values[i];
		}
	}
	else
	{
		return a.eval > b.eval;
	}
};

int Day7_Part1(stringstream& input)
{
	set<Hand, decltype(cmp)> ordered;
	while (!input.eof())
	{
		string hand;
		int bid;
		input >> hand >> bid;
		ordered.insert(Hand(hand, bid));
	}
	int sum=0;
	int i = 1;

	for (auto hand : ordered)
	{
		sum += hand.bid * i++;
	}

	return sum;
}

int Day7_Part2(stringstream& input)
{
	set<Hand, decltype(cmp)> ordered;
	while (!input.eof())
	{
		string hand;
		int bid;
		input >> hand >> bid;
		ordered.insert(Hand(hand, bid, true));
	}
	int sum = 0;
	int i = 1;

	for (auto hand : ordered)
	{
		sum += hand.bid * i++;
	}

	return sum; //253362743
}


void Day7(stringstream& input)
{
	cout<<"Part 1 result is: " << Day7_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day7_Part2(input)<<endl<<endl;

	return;
}