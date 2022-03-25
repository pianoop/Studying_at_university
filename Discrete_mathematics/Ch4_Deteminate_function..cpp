//Deteminate that relation given is function.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

//주어진 집합 A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} 내에서 관계가 입력돼야함.
//파일로 관계를 받아옴.
class DetFunc
{
public:
	DetFunc(const char* fileName, int n = 10) :mN(n)
	{
		mIdx = ++cnt;
		bool* bChecks = new bool[mN + 1];
		memset(bChecks, false, sizeof(bool) * (mN + 1));

		if (input(fileName))
			calc();
	}

	void IsFunc()
	{
		if (mbFunc)
			std::cout << mIdx << "번째 관계는 함수가 맞습니다.\n";
		else
			std::cout << mIdx << "번째 관계는 함수가 아닙니다.\n";

	}

	void PrintRelations()
	{
		std::cout << "----------------\n{ ";
		for (auto& a : mRelations)
			std::cout << "\n(" << a.first << ", " << a.second << "),";
		std::cout << "\b \n}\n----------------";
	}

private:
	bool input(const char* fileName)
	{
		std::ifstream readFile(fileName);

		if (readFile.fail())
		{
			std::cout << "파일 이름을 잘못 되었습니다.\n";
			return false;
		}

		int a, b;
		mRelations.reserve(mN * mN);
		while (!readFile.eof())
		{
			readFile >> a >> b;
			mRelations.push_back({ a,b });
		}

		readFile.close();
		return true;
	}

	void calc()
	{
		bool* bChecks = new bool[mN + 1];
		memset(bChecks, false, sizeof(bool) * (mN + 1));

		for (auto& [a, b] : mRelations)
		{
			if (bChecks[a])
			{
				mbFunc = false;
				break;
			}
			else
				bChecks[a] = true;
		}

		delete[] bChecks;
	}

private:
	std::vector<std::pair<int, int> > mRelations;
	bool mbFunc = true;
	int mN, mIdx;
	static int cnt;
};
int ::DetFunc::cnt = 0;

void Solve()
{
	DetFunc func1("pp3-1.dat", 10);
	DetFunc func2("pp3-2.dat", 10);

	func1.IsFunc();
	func2.IsFunc();
}

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Solve();

	return 0;
}