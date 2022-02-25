//Product matrix
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <time.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main()
{
	clock_t start, end;
	
	vvi arr1(1000, vi(1000)), arr2(1000, vi(1000));

	int tmp = 0;
	for (int i = 0;i < 1000;i++)
	{
		for (int j = 0;j < 1000;j++)
		{
			arr1[i][j] = arr2[j][i] = j;
		}
	}
	vvi ans(1000, vi(1000));
	printf("1000 * 1000 행렬 곱 시작!\n");
	start = clock();
	for (int i = 0;i < 1000;i++)
	{
		for (int j = 0;j < 1000;j++)
		{
			for (int k = 0;k < 1000;k++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("i j k 순서의 계산 시간: %d\n", end - start);

	start = clock();
	for (int i = 0;i < 1000;i++)
	{
		for (int k = 0;k < 1000;k++)
		{
			for (int j = 0;j < 1000;j++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("i k j 순서의 계산 시간: %d\n", end - start);

	start = clock();
	for (int j = 0;j < 1000;j++)
	{
		for (int i = 0;i < 1000;i++)
		{
			for (int k = 0;k < 1000;k++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("j i k 순서의 계산 시간: %d\n", end - start);

	start = clock();
	for (int j = 0;j < 1000;j++)
	{
		for (int k = 0;k < 1000;k++)
		{
			for (int i = 0;i < 1000;i++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("j k i 순서의 계산 시간: %d\n", end - start);

	start = clock();
	for (int k = 0;k < 1000;k++)
	{
		for (int i = 0;i < 1000;i++)
		{
			for (int j = 0;j < 1000;j++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("k i j 순서의 계산 시간: %d\n", end - start);

	start = clock();
	for (int k = 0;k < 1000;k++)
	{
		for (int j = 0;j < 1000;j++)
		{
			for (int i = 0;i < 1000;i++)
				ans[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	end = clock();
	printf("k j i 순서의 계산 시간: %d\n", end - start);

	return 0;
}