#include "../general.h"

struct Point
{
	int x, y;
	bool set{ false };
};

void FindNext(vector<vector<char>>& Maze, Point& P, Point& Prev)
{
	char now = Maze[P.y][P.x];

	if (now == '|')
	{
		if (P.y + 1 != Prev.y)
		{
			Prev = P;
			P.y++;
		}
		else
		{
			Prev = P;
			P.y--;
		}
	}
	else if (now == '-')
	{
		if (P.x + 1 != Prev.x)
		{
			Prev = P;
			P.x++;
		}
		else
		{
			Prev = P;
			P.x--;
		}
	}
	else if (now == 'L')
	{
		if (P.y - 1 != Prev.y)
		{
			Prev = P;
			P.y--;
		}
		else
		{
			Prev = P;
			P.x++;
		}
	}
	else if (now == 'J')
	{
		if (P.y - 1 != Prev.y)
		{
			Prev = P;
			P.y--;
		}
		else
		{
			Prev = P;
			P.x--;
		}
	}
	else if (now == 'F')
	{
		if (P.y + 1 != Prev.y)
		{
			Prev = P;
			P.y++;
		}
		else
		{
			Prev = P;
			P.x++;
		}
	}
	else if (now == '7')
	{
		if (P.y + 1 != Prev.y)
		{
			Prev = P;
			P.y++;
		}
		else
		{
			Prev = P;
			P.x--;
		}
	}
}


int Day10_Part1(stringstream& input)
{
	vector<vector<char>> Maze;
	int Sx = 0, Sy = 0;
	int i = 0;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		auto pos = line.find('S');
		if (pos != line.npos)
		{
			Sx = pos, Sy = i;
		}
		vector<char> vline(line.begin(), line.end());
		Maze.push_back(vline);
		i++;
	}
	Point P1{}, P2{};

	if (Sy < Maze.size()-1 && (Maze[Sy + 1][Sx] == '|' || Maze[Sy + 1][Sx] == 'J' || Maze[Sy + 1][Sx] == 'L'))
	{ //DOWN
		P1 = { Sx, Sy + 1 };
		P1.set = true;
	}
	if (Sy > 0 && (Maze[Sy - 1][Sx] == '|' || Maze[Sy - 1][Sx] == '7' || Maze[Sy - 1][Sx] == 'F'))
	{ //UP
		if (!P1.set)
		{
			P1 = { Sx, Sy - 1 };
			P1.set = true;
		}
		else
			P2 = { Sx, Sy - 1 };
	}
	if (Sx < Maze[0].size()-1 && (Maze[Sy][Sx + 1] == '-' || Maze[Sy][Sx + 1] == 'J' || Maze[Sy][Sx + 1] == '7'))
	{ //RIGHT
		if (!P1.set)
		{
			P1 = { Sx + 1, Sy };
			P1.set = true;
		}
		else
			P2 = { Sx + 1, Sy };
	}
	if (Sx > 0 && (Maze[Sy][Sx - 1] == '-' || Maze[Sy][Sx - 1] == 'L' || Maze[Sy][Sx - 1] == 'F'))
	{ //LEFT	
		P2 = { Sx - 1, Sy };
	}

	Point P1Prev{Sx, Sy}, P2Prev{Sx, Sy};
	int steps = 1;
	while (!(P1.x == P2.x && P1.y == P2.y))
	{
		FindNext(Maze, P1, P1Prev);
		FindNext(Maze, P2, P2Prev);
		steps++;
	}

	return steps;
}

string Day10_Part2(stringstream& input)
{
	vector<vector<char>> Maze;
	int i = 0;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		vector<char> vline(line.begin(), line.end());
		Maze.push_back(vline);
		i++;
	}

	return "Not implemented yet";
}


/* Idea for part 2: compression of maze
 
FJ		.|
L-  => 	.L


7|		-J
LJ  =>	..


||		LJ
LJ =>	..


7F		--
LJ => 	..


L7		|.
-J =>	J.


etc

*/


void Day10(stringstream& input)
{
	cout << "Part 1 result is: " << Day10_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day10_Part2(input) << endl << endl;

	return;
}