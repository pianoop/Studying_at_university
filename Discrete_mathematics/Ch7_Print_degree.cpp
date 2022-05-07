//Print out degree for vertexes in undirected graph.
//
#include <iostream>
#include <fstream>
#include <cstring>

class UndirectedGraph
{
public:
	UndirectedGraph()
	{
		input();
		solve();
	}

	~UndirectedGraph()
	{
		for (int i = 0; i < mN; i++)
			delete[] mArr[i];
		delete[] mArr;
	}

private:
	void input()
	{
		std::cout << "0 입력 -> 기존 파일 예제 실행\n그 외의 입력 -> 직접 입력\n";
		char C;
		std::cout << "입력값: ";
		std::cin >> C;

		int a, b;
		if (C == '0')
		{
			std::ifstream readFile("input.dat");
			mN = 6;			//기본 값

			if (readFile.fail())
			{
				std::cout << "파일 이름을 잘못 되었습니다.\n";
				return;
			}

			mArr = new bool* [mN];
			for (int i = 0; i < mN; i++)
			{
				mArr[i] = new bool[mN];
				memset(mArr[i], false, sizeof(bool) * (mN));
			}

			while (!readFile.eof())
			{
				readFile >> a >> b;
				mArr[a][b] = true;
				mArr[b][a] = true;
			}
		}
		else
		{
			std::cout << "정점의 개수를 입력해주세요: ";
			std::cin >> mN;
			mN++;
			mArr = new bool* [mN];
			for (int i = 0; i < mN; i++)
			{
				mArr[i] = new bool[mN];
				memset(mArr[i], false, sizeof(bool) * (mN));
			}

			std::cout << "\n간선들을 입력해주세요:			예시) 1 2   (종료시 0입력)\n";

			while (std::cin >> a)
			{
				if (a == 0)
					break;
				std::cin >> b;
				mArr[a][b] = true;
				mArr[b][a] = true;
			}
		}
	}

	void solve()
	{
		std::cout << "1번 정점부터의 차수 출력\n--------\n\n";
		int cnt;
		for(int i=1;i<mN;i++)
		{ 
			cnt = 0;
			for (int j = 1; j < mN; j++)
			{
				if (mArr[i][j])
					cnt++;
			}
			if (mArr[i][i])
				cnt++;

			std::cout << cnt << " ";
		}
		std::cout << "\n\n--------";
	}

private:
	bool** mArr;
	int mN;

};

void Solve()
{
	UndirectedGraph Vert;
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}