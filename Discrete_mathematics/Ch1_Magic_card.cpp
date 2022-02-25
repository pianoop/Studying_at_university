#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
typedef std::vector<int> vi;

void Welcome()
{
	std::cout << "# 지금부터 여러분을 신비한 마술의 세계로 초대합니다.\n\n\n";
	std::cout << "1 - 31의 숫자중 마음에 드는 숫자를 생각해 보세요.\n\n\n";
}

int main()
{
	std::ios::sync_with_stdio(false), std::cin.tie(NULL), std::cout.tie(NULL);

	while (true)
	{
		vi card[5];
		for (int i = 1;i < (1 << 5);i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (i & (1 << j))
				{
					card[j].push_back(i);
				}
			}
		}

		Welcome();

		int ans = 0;
		std::string input;
		std::cout << "생각하셨다면 엔터를 눌러주세요.";
		std::getline(std::cin, input);

		std::cout << "\n\n";

		for (int i = 0;i < 5;i++)
		{
			std::cout << "------ " << i + 1 << "번째 카드 ------\n";
			int enter = 0;
			for (auto& a : card[i])
			{
				if (enter % 4 == 0)
					std::cout << "      ";
				enter++;
				std::cout << a << " ";
				if (a < 10)
					std::cout << " ";
				if (enter % 4 == 0)
					std::cout << "\n";
			}
			std::cout << "------------------------\n";
			std::cout << "이 중에 생각한 숫자가 있다면 YES를, 없으면 NO를 입력해주세요\n";

			while (std::cin >> input)
			{
				if (input == "YES")
				{
					ans += (1 << i);
				}
				else if (input != "NO")
				{
					std::cout << "잘못 입력하셨습니다. 다시 입력해주세요.\n";
					continue;
				}
				break;
			}
			std::cout << "\n\n";
		}
		if (ans == 0)
			std::cout << "##1 - 31 이외의 수를 생각하셨습니다! 이러시면 곤란합니다!##\n";
		else
			std::cout << "##당신이 생각한 숫자는 " << ans << "입니다.##\n\n\n";

		std::cout << "다시 해보시려면 YES를 입력해주세요.\n";
		std::cin >> input;
		if (input == "YES")
		{
			system("cls");
			continue;
		}
		else
		{
			std::cout << "지금까지 마술의 세계였습니다!\n\n";
			break;
		}
	}

	return 0;
}