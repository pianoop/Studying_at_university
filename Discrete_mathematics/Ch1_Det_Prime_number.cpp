//Det_Prime number
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
typedef std::vector<int> vi;
typedef std::vector<char> vc;

int main()
{
	std::ios::sync_with_stdio(false), std::cin.tie(NULL), std::cout.tie(NULL);

	std::cout << "입력(Input)에 대한 소수 판별을 해드립니다.\n";
	std::cout << "소수 판별을 위한 N값을 입력해주세요 : ";
	int N;
	std::cin >> N;

	bool flag = 0;
	for (int i = 2;i <= int(sqrt(N));i++)
	{
		if (N % i == 0)
		{
			flag = 1;
			break;
		}
	}

	if (!flag)
		std::cout << "input number -->" << N << " is Prime number!!\n";
	else
		std::cout << "input number -->" << N << " is not Prime number!!\n";

	return 0;
}