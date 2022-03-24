//Determinate that given graph is reflaxive, symmetric and transitive relation.
//-------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
typedef std::vector<int> vi;

//파일로 간선 입력
class Matrix
{
public:
	Matrix(int n = 20): mN(n)
	{
		input();
	}

	~Matrix()
	{
		for (int i = 0; i <= mN; i++)
			delete[] mEdges[i];
		delete[] mEdges;
	}

	bool IsReflaxiveR()
	{
		for (int i = 1; i <= mN; i++)
		{
			if (!mEdges[i][i])
				return false;
		}

		return true;
	}

	bool IsSymmetricR()
	{
		for (int i = 1; i <= mN; i++)
		{
			for (int j = i; j <= mN; j++)
			{
				if (mEdges[i][j] != mEdges[j][i])
					return false;
			}
		}

		return true;
	}
	
	bool IsTransitiveR() //To do
	{
		for (int i = 1; i <= mN; i++)
		{
			bool* check = new bool[mN + 1];
			memset(check, false, sizeof(bool) * (mN + 1));
			check[i] = true;

			for (int j = 1; j <= mN; j++)
			{
				if (!check[j] && mEdges[i][j])
				{
					check[j] = true;
					if (!isTransitiveR_Sub(i, j, check))
						return false;
				}
			}
		}

		return true;
	}

private:
	void input()
	{
		mEdges = new bool* [mN + 1];
		for (int i = 0; i <= mN; i++)
		{
			mEdges[i] = new bool[mN + 1];
			memset(mEdges[i], false, sizeof(bool) * (mN + 1));
		}

		/*    ####   파일 입력은 여기서!####    */
		std::ifstream readFile("pp2-1.dat");
		if (readFile.fail())
		{
			printf("파일을 찾을 수 없습니다.\n");
			return;
		}

		int a, b;
		while (!readFile.eof())
		{
			readFile >> a >> b;
			mEdges[a][b] = true;
		}
		readFile.close();
	}

	bool isTransitiveR_Sub(const int& i, int j, bool* check)
	{
		for (int k = 1; k <= mN; k++)
		{
			if (!check[k] && mEdges[j][k])
			{
				if (!mEdges[i][k])
					return false;

				check[k] = true;
				isTransitiveR_Sub(i, k, check);
			}
		}

		return true;
	}


private:
	bool** mEdges;
	int mN;
};

void Solve()
{
	printf("--- 간선을 파일에서 불러옵니다 ---\n");

	//정점 개수 수정시 n개 -> matrix(n)
	Matrix matrix; 

	printf("반사 관계: ");
	if (matrix.IsReflaxiveR())
		printf("T\n");
	else
		printf("F\n");
	printf("대칭 관계: ");
	if (matrix.IsSymmetricR())
		printf("T\n");
	else
		printf("F\n");
	printf("추이 관계: ");
	if (matrix.IsTransitiveR())
		printf("T\n");
	else
		printf("F\n");
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}