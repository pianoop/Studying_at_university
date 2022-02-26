//역행렬
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
typedef double d;
typedef std::vector<d> vd;
typedef std::vector<vd> vvd;

vvd GetMatrix();
vvd ComputeInverse(vvd& Matrix);
void PrintAnswer(const vvd& Inverse);

int main()
{
	std::ios::sync_with_stdio(false), std::cin.tie(NULL), std::cout.tie(NULL);
	
	std::cout<<"행렬의 크기 n과 행렬의 원소를 입력해주세요! \nex)\n2\n2 2\n4 4\n";
	vvd Matrix = GetMatrix();
	vvd Inverse = ComputeInverse(Matrix);
	PrintAnswer(Inverse);

	return 0;
}


vvd GetMatrix()
{
	int n;
	std::cin >> n;

	vvd Matrix(n, vd(n));
	for (auto& n : Matrix)
		for (auto& m : n)
			std::cin >> m;

	return Matrix;
}

vvd ComputeInverse(vvd& Matrix)
{
	int n = int(Matrix.size());
	vvd inverse(n, vd(n));
	for (int i = 0;i < n;i++)
		inverse[i][i] = 1;

	for (int i = 0;i < n;i++)
	{
		//finding leading 1
		int lead1 = i;
		while (lead1 < n)
		{
			if (Matrix[lead1][i] == 0)
				lead1++;
			else
				break;
		}

		//열 전체가 0이면 크기 0인 행렬 반환(singular matrix)
		if (lead1 == n)
			return vvd();

		if (lead1 != i)
		{
			Matrix[i].swap(Matrix[lead1]);
			inverse[i].swap(inverse[lead1]);
		}

		d divide = Matrix[i][i];

		for (int j = 0; j < n;j++)
		{
			Matrix[i][j] /= divide;
			inverse[i][j] /= divide;
		}

		//선도 1와 같은 column 모두 0으로 만들기 (위)
		for (int upper = 0;upper < i;upper++)
		{
			divide = Matrix[upper][i];
			Matrix[upper][i] = 0;
			for (int j = 0;j < n;j++)
			{
				if (j > i)
					Matrix[upper][j] -= divide * Matrix[i][j];
				inverse[upper][j] -= divide * inverse[i][j];
			}
		}
		//(아래)
		for (int lower = i + 1;lower < n;lower++)
		{
			divide = Matrix[lower][i];
			Matrix[lower][i] = 0;
			for (int j = 0;j < n;j++)
			{
				if (j > i)
					Matrix[lower][j] -= divide * Matrix[i][j];
				inverse[lower][j] -= divide * inverse[i][j];
			}
		}
	}

	return inverse;
}

void PrintAnswer(const vvd& Inverse)
{
	if (Inverse.size() == 0)
		std::cout << "no inverse";
	else
	{
		std::cout << std::fixed;
		std::cout.precision(8);
		for (auto& n : Inverse)
		{
			for (auto& m : n)
			{
				std::cout << m << " ";
			}
			std::cout << "\n";
		}
	}
}