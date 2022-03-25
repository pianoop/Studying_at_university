//Washall algorithm
//-------------------------------------------------------------------
#include <iostream>
#include <cstring>

class Graph
{
public:
	Graph()
	{
		input();
	}

	~Graph()
	{
		for (int i = 0; i <= mN; i++)
		{
			delete[] mGraph[i];
			delete[] mWarshall[i];
		}
		delete[] mGraph;
		delete[] mWarshall;
	}

	void PrintAns()
	{
		if (mAnsflag)
		{
			calc();
			mAnsflag = false;
		}

		printf("{ ");
		for (int i = 1; i <= mN; i++)
		{
			for (int j = 1; j <= mN; j++)
			{
				if (mWarshall[i][j])
					printf("\n(%d, %d),",i,j);
			}
		}
		printf("\b \n}");
	}

	/*void PrintGraph()
	{
		printf("{ ");
		for (int i = 1; i <= mN; i++)
		{
			for (int j = 1; j <= mN; j++)
			{
				if (mGraph[i][j])
					printf("\n(%d, %d),", i, j);
			}
		}
		printf("\b \n}");
	}*/

private:
	void input()
	{
		printf("정점의 개수를 입력해주세요: ");
		std::cin >> mN;
		mGraph = new bool* [mN + 1];
		mWarshall = new bool* [mN + 1];
		for (int i = 0; i <= mN; i++)
		{
			mGraph[i] = new bool[mN + 1];
			mWarshall[i] = new bool[mN + 1];
			memset(mGraph[i], false, sizeof(bool) * (mN + 1));
			memset(mWarshall[i], false, sizeof(bool) * (mN + 1));
		}

		printf("\n-------\n간선을 입력해주세요. 입력이 끝나셨으면 0번을 입력해주세요. \nex) \n1 2\n3 4\n-------\n");
		int a, b;
		while (std::cin >> a)
		{
			if (a == 0)
				break;
			std::cin >> b;
			mGraph[a][b] = true;
			mWarshall[a][b] = true;
		}
	}

	void calc()
	{
		for (int k = 1; k <= mN; k++)
		{
			for (int i = 1; i <= mN; i++)
			{
				for (int j = 1; j <= mN; j++)
				{
					if (mWarshall[i][k] && mWarshall[k][j])
						mWarshall[i][j] = true;
				}
			}
		}
	}


private:
	int mN;
	bool **mGraph, **mWarshall;
	bool mAnsflag = true;
};

void Solve()
{
	Graph graph;
	graph.PrintAns();
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}