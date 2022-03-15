//Print Powerset
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

class Powerset
{
public:
	Powerset()
	{
		Welcome();
		n = Input();
	}

	void PrintPowerset()
	{
		printf("{\n 0");

		for (int i = 1; i <= n; i++)
		{
			vi subset(i);
			PrintPowerset_sub(0, 0, i,subset);
			printf("\n");
		}

		printf(" }\n");
	}

	void PrintPowerset_sub(int now, int idx, int cnt, vi& subset)
	{
		if (cnt == 0)
		{
			printf(", {%d", subset[0]);
			for (int i = 1; i < int(subset.size()); i++)
				printf(", %d", subset[i]);
			printf("}");

			return;
		}

		cnt--;
		for (int i = now + 1; i <= n - cnt; i++)
		{
			subset[idx] = i;
			PrintPowerset_sub(i, idx+1, cnt, subset);
		}
	}

	void Welcome()
	{
		printf("1부터 n까지의 집합의 멱집합을 출력하는 프로그램입니다.\n");
		printf("0은 공집합 표시입니다.\n");
	}

	int Input()
	{
		printf("자연수 n을 입력해주세요.\n");
		int n;
		while (true)
		{
			std::cin >> n;
			if (n > 0)
				break;
			else
				printf("n은 자연수여야합니다.\n n을 입력해주세요.\n");
		}
		return n;
	}

private:
	int n;
};

int main()
{
	std::ios::sync_with_stdio(false); std::cin.tie(NULL);

	Powerset set;
	set.PrintPowerset();

	return 0;
}