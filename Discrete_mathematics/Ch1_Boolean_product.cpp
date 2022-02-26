//boolean product
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

vvi GetMatrix(int n);
void Welcome();
vvi Productbool(const vvi& Matrix1, const vvi& Matrix2);
void PrintAnswer(const vvi& answer);

int main()
{
	std::ios::sync_with_stdio(false), std::cin.tie(NULL);

	Welcome();
	vvi Matrix1 = GetMatrix(3);
	Welcome();
	vvi Matrix2 = GetMatrix(3);

	vvi answer = Productbool(Matrix1, Matrix2);
	PrintAnswer(answer);

	return 0;
}

void Welcome()
{
	printf("부울 행렬(3*3)을 입력하세요.\n(0과 1만 사용하세요)\n");
	printf("ex)\n0 1 0\n0 0 0\n1 0 1\n\n");
}

vvi GetMatrix(int n)
{
	vvi Matrix(n,vi(n));

	for (auto& n : Matrix)
		for (auto& m : n)
			std::cin >> m;

	return Matrix;
}

vvi Productbool(const vvi& Matrix1, const vvi& Matrix2)
{
	int n = int(Matrix1.size());
	vvi answer(n, vi(n));
	for (int i = 0;i < n;i++)
	{
		for (int k = 0;k < n;k++)
		{
			for (int j = 0;j < n;j++)
			{
				if (!answer[i][j])
					answer[i][j] = Matrix1[i][k] * Matrix2[k][j];
			}
		}
	}

	return answer;
}

void PrintAnswer(const vvi& answer)
{
	printf("결과)\n");
	for (auto& n : answer)
	{
		for (auto& m : n)
		{
			printf("%d ", m);
		}
		printf("\n");
	}
}