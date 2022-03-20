//Find a path of length n
//-------------------------------------------------------------------
#include <iostream>
#include <cstring>

class FindPathN
{
public:
	FindPathN(int n) :mN(n + 1)
	{
		printf("1과 0으로 데이터를 입력해주세요.\n");

		mArr = new bool* [mN];
		mArr[0] = new bool[mN];
		for (int i = 1; i < mN; i++)
		{
			mArr[i] = new bool[mN];
			mArr[i][0] = false;
			for (int j = 1; j < mN; j++)
				std::cin >> mArr[i][j];
		}
	}
	~FindPathN()
	{
		for (int i = 0; i < mN; i++)
			delete[] mArr[i];
		delete[] mArr;
	}

	void PrintAns(int n)
	{
		bool** ans = calc(n);

		printf("길이가 %d인 경로 출력\n\n", n);
		for (int i = 1; i < mN; i++)
		{
			for (int j = 1; j < mN; j++)
			{
				if (ans[i][j])
					printf("(%d -> %d)\n", i, j);
			}
		}


		for (int i = 0; i < mN; i++)
			delete[] ans[i];
		delete[] ans;
	}


private:
	bool** matrixProduct(bool** A, bool** B)
	{
		bool** ret = new bool* [mN];
		ret[0] = new bool[mN];
		for (int i = 1; i < mN; i++)
		{
			ret[i] = new bool[mN];
			memset(ret[i], false, sizeof(bool) * mN);
		}
		
		for (int i = 1; i < mN; i++)
		{
			for (int j = 1; j < mN; j++)
			{
				for (int k = 1; k < mN; k++)
				{
					if (A[i][k] && B[k][j])
					{
						ret[i][j] = true;
						break;
					}
				}
			}
		}

		return ret;
	}

	bool** calc(int b)
	{
		bool** ret = new bool* [mN];
		for (int i = 0; i < mN; i++)
		{
			ret[i] = new bool[mN];
			memset(ret[i], false, sizeof(bool) * mN);
		}
		for (int i = 1; i < mN; i++)
			ret[i][i] = true;

		bool** A = new bool* [mN];
		A[0] = new bool[mN];
		for (int i = 1; i < mN; i++)
		{
			A[i] = new bool[mN];
			A[i][0] = false;
			for (int j = 1; j < mN; j++)
				A[i][j] = mArr[i][j];
		}

		while (b != 0)
		{
			if (b & 1)
			{
				bool** temp = ret;

				ret = matrixProduct(ret, A);

				for (int i = 0; i < mN; i++)
					delete[] temp[i];
				delete[] temp;
			}

			bool** temp = A;

			A = matrixProduct(A, A);

			for (int i = 0; i < mN; i++)
				delete[] temp[i];
			delete[] temp;

			b >>= 1;
		}
		for (int i = 0; i < mN; i++)
			delete[] A[i];
		delete[] A;

		return ret;
	}

private:
	int mN;
	bool** mArr;
};

void Solve()
{
	int n;
	printf("행렬의 크기 N을 입력해주세요: ");
	std::cin >> n;
	FindPathN path(n);

	while (n != 0)
	{
		printf("경로의 길이 n을 입력해주세요: ");
		std::cin >> n;

		path.PrintAns(n);

		printf("종료하시려면 0을, 계속하시려면 1을 입력해주세요: ");
		std::cin >> n;
	}
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}