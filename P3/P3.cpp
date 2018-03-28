#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
	
struct vertices
{
	int x, y;
	vertices *linked[8];
	int index;
};

vertices graph[8][8];
string start, goal;

int startx, starty, goalx, goaly;


void setLink()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i > 0)
			{
				if (j > 1)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i - 1][j - 2];
					graph[i][j].index++;
				}
				if (j < 6)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i - 1][j + 2];
					graph[i][j].index++;
				}
			}
			if (i > 1)
			{
				if (j > 0)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i - 2][j - 1];
					graph[i][j].index++;
				}
				if (j < 7)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i - 2][j + 1];
					graph[i][j].index++;
				}
			}
			if (i < 6)
			{
				if (j > 0)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i + 2][j - 1];
					graph[i][j].index++;
				}
				if (j < 7)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i + 2][j + 1];
					graph[i][j].index++;
				}
			}
			if (i < 7)
			{
				if (j > 1)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i + 1][j - 2];
					graph[i][j].index++;
				}
				if (j < 6)
				{
					graph[i][j].linked[graph[i][j].index] = &graph[i + 1][j + 2];
					graph[i][j].index++;
				}
			}
		}
	}
}

void setGraph()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			graph[i][j].x = i;
			graph[i][j].y = j;
			graph[i][j].index = 0;
			for (int k = 0; k < 8; k++)
			{
				graph[i][j].linked[k] = new vertices;
			}
		}
	}
	setLink();
}

bool ids(vertices & v, int move)
{
	bool found = false;
	if (move == 0)
	{
		if (v.x == goalx && v.y == goaly)
		{
			return true;
		}
	}
	else
	{
		for (int i = 0; i < v.index; i++)
		{
			bool found = ids(*v.linked[i], move - 1);
			if (found)
			{
				return true;
			}
		}
	}
	return false;
}


void IDS()
{
	bool found = false;

	for (int move = 0; move < 100; move++)
	{
		found = ids(graph[startx][starty], move);
		if (found)
		{
			cout << "To get from " << start << " to "
				<< goal << " takes " << move
				<< " knight moves." << endl;
			break;
		}
	}
}

int main() 
{
	setGraph();

	ifstream inf("input.txt");

	if (!inf)
	{
		cout << "Cannot find the file" << endl;
		return 0;
	}

	while (getline(inf, start))
	{
		goal = start.substr(3, 4);
		start = start.substr(0, 2);

		starty = (int)start[0] - 97;
		startx = (int)start[1] - 49;

		goaly = (int)goal[0] - 97;
		goalx = (int)goal[1] - 49;

		IDS();
	}

	return 0;
}

/*
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
请按任意键继续. . .
*/