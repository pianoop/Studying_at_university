//Welsh Powell algorithm
// 추천 예시) 1 2 1 3 1 4 2 3 3 5 4 5 0
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
typedef std::vector<int> vi;

class WelshPowell
{
public:
	WelshPowell()
	{
		input();
		solve();
	}

	~WelshPowell()
	{
		for (int i = 0; i <= mN; i++)
			delete[] mArr[i];
		delete[] mArr;
	}


private:
	void input()
	{
		mN = 6;  //이 함수 끝에서 5로 변경
		std::cout << "정점의 개수는 5개입니다.\n";
		mAns.resize(mN);
		mArr = new bool* [mN];
		for (int i = 0; i < mN; i++)
		{
			mArr[i] = new bool[mN];
			memset(mArr[i], false, sizeof(bool) * (mN));
		}

		int a, b;
		std::cout << "평면 그래프의 간선들을 입력해주세요:			예시) 1 2   (1 ~ 5 이내로, 종료시 0입력)\n";

		while (std::cin >> a)
		{
			if (a == 0)
				break;
			std::cin >> b;
			mArr[a][b] = true;
			mArr[b][a] = true;
		}

		mSortD.resize(mN);
		for (int i = 1; i < mN; i++)
		{
			auto& [a,b] =mSortD[i];
			b = i;
			for (int j = 1; j < mN; j++)
			{
				if (mArr[i][j])
					a++;
			}
			if (mArr[i][i])
				a++;
		}

		std::sort(mSortD.begin() + 1, mSortD.end(), [](auto& a, auto& b)->bool
			{
				return a.first > b.first;
			});

		mN--;  //5로 변경
	}

	void solve()
	{
		for (int i = 1; i <= mN; i++)
		{
			int now = mSortD[i].second;
			if (mAns[now] == 0)
			{
				mAns[now] = ++mColor;
				memset(mCheck, false, sizeof(bool) * 6);
				mCheck[now] = true;
				recur(now, true);
			}
		}

		for (int i = 1; i <= mN; i++)
			std::cout << i << "번 정점 색상 번호 : " << mAns[i] << "\n";
		std::cout << "사용한 색의 개수 : " << mColor << "\n";
	}

	void recur(int now, bool bPainted)
	{
		if (bPainted)
		{
			for (int i = 1; i <= mN; i++)
			{
				if (!mCheck[i] && mArr[now][i])
				{
					mCheck[i] = true;
					recur(i, false);
				}
			}
		}
		else
		{
			for (int i = 1; i <= mN; i++)
			{
				if (!mCheck[i] && mArr[now][i])
				{
					mCheck[i] = true;

					if (mAns[i] == 0)
					{
						bool bNext = true;

						for (int j = 1; j <= mN; j++)
						{
							if (mArr[i][j] && mAns[j] == mColor)
							{
								bNext = false;
								break;
							}
						}

						if (bNext)
						{
							mAns[i] = mColor;
							recur(i, true);
						}
						else
						{
							recur(i, false);
						}
					}
					else
						recur(i, false);
				}
			}
		}
	}

private:
	bool **mArr;
	bool mCheck[6] = { false, };
	std::vector<std::pair<int, int> >  mSortD;
	vi mAns;
	int mN, mColor = 0;

};

void Solve()
{
	WelshPowell painting;
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}