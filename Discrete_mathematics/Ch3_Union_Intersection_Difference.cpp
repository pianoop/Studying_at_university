//Process- Union, Intersection, Difference
//-------------------------------------------------------------------
#include <iostream>

class ProcessSet
{
public:
	ProcessSet() 
	{
		Welcome();
		Input();
	}

	void SelectProcess()
	{
		int select;
		while (true)
		{
			printf("출력할 계산을 선택해주세요. (1: 합집합, 2: 교집합, 3: 차집합(A-B), 4: 차집합(B-A), 그 외의 값: 종료)\n");
			std::cin >> select;
			if (select == 1)
				PrintUnion();
			else if (select == 2)
				PrintIntersection();
			else if (select == 3)
				PrintDifference(true);
			else if(select==4)
				PrintDifference(false);
			else
				break;
		}
	}

	void PrintUnion()
	{
		printf("\n{  ");

		for (int i = 1; i < 101; i++)
		{
			if (mbA[i] || mbB[i])
				printf("%d, ",i);
			}

		printf("\b\b  }\n A와 B의 합집합을 출력했습니다.\n");
	}

	void PrintIntersection()
	{
		printf("\n{  ");

		for (int i = 1; i < 101; i++)
		{
			if (mbA[i] && mbB[i])
				printf("%d, ", i);
		}

		printf("\b\b  }\n A와 B의 교집합을 출력했습니다.\n");
	}

	void PrintDifference(bool flag)
	{
		bool(*A)[101], (*B)[101];
		if (flag)
		{
			A = &mbA;
			B = &mbB;
		}
		else
		{
			A = &mbB;
			B = &mbA;
		}

		printf("\n{  ");

		for (int i = 1; i < 101; i++)
		{
			if((*A)[i] && !(*B)[i])
				printf("%d, ", i);
		}

		if(flag)
			printf("\b\b  }\n A와 B의 차집합(A-B)을 출력했습니다.\n");
		else
			printf("\b\b  }\n A와 B의 차집합(B-A)을 출력했습니다.\n");
	}

	void Welcome()
	{
		printf("두 집합의 합집합, 교집합, 차집합을 구하는 프로그램입니다.\n");
		printf("원소의 범위는 100이하의 자연수입니다.\n");
	}

	void Input()
	{
		int n, temp;
		printf("A집합에 들어갈 원소의 크기를 입력해주세요\n");
		std::cin >> n;
		printf("A에 들어갈 원소 입력해주세요.\n");
		while (n != 0)
		{
			std::cin >> temp;
			if (temp < 1 || temp > 100)
			{
				printf("1부터 100사이의 자연수를 입력해주세요.\n");
				continue;
			}
			mbA[temp] = true;
			n--;
		}

		printf("\nB집합에 들어갈 원소의 크기를 입력해주세요\n");
		std::cin >> n;
		printf("B에 들어갈 원소 입력해주세요.\n");
		while (n != 0)
		{
			std::cin >> temp;
			if (temp < 1 || temp > 100)
			{
				printf("1부터 100사이의 자연수를 입력해주세요.\n");
				continue;
			}
			mbB[temp] = true;
			n--;
		}
	}

private:
	bool mbA[101] = { false, }, mbB[101] = { false, };
};

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	ProcessSet sets;
	sets.SelectProcess();

	return 0;
}