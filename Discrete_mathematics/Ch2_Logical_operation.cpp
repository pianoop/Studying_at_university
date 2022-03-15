//Logical operation
//-------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

typedef std::pair<char, int> pci;

template <typename T>
class Stack
{
public:
	Stack(int size = 100)
	{
		mData = new T[size+1];
	}
	~Stack()
	{
		delete[] mData;
	}

	void Push(T num)
	{
		mData[mStackSize] = num;
		mStackSize++;
	}

	void Pop()
	{
		mStackSize--;
	}

	T Top()
	{
		return mData[mStackSize - 1];
	}

	int Size()
	{
		return mStackSize;
	}

	bool Empty()
	{
		if (Size() == 0)
			return true;
		else
			return false;
	}

private:
	T* mData;
	int mStackSize = 0;
};

class Proposition
{
public:
	Proposition()
	{
		memset(&mTransOperand, 0, 27 * sizeof(int));

		int opernum;
		std::cin >> mVarnum >> opernum;
		mTruth = new bool[mVarnum];
		memset(mTruth, true, sizeof(bool) * mVarnum);
		Input();

		mOperator = new Stack<pci>(mVarnum);
		mOperand = new Stack<bool>(opernum);
	}

	~Proposition()
	{
		free(mTruth);
		delete mOperator;
		delete mOperand;
	}

	void Compute()
	{
		PrevPermutation(0);
	}

	void Input()
	{

		int length;
		std::cin >> length;
		str.reserve(length);
		std::vector<char> sorting;
		sorting.reserve(mVarnum);
		for (int i = 0; i < length; i++)
		{
			char tmp;
			std::cin >> tmp;
			if (tmp < 91 && mTransOperand[tmp - 65] == 0)
			{
				sorting.push_back(tmp);
				mTransOperand[tmp - 65] = -1;
			}
			str.push_back(tmp);
		}

		std::sort(sorting.begin(), sorting.end());
		int order = 0;
		for (int i = 0; i < mVarnum; i++)
		{
			printf("%c ", sorting[i]);
			mTransOperand[sorting[i] - 65] = order++;
		}

		printf("RESULT\n");
	}

private:

	void PrevPermutation(int n)
	{
		if (n == mVarnum)
		{
			ComputeSub();
			PrintTruthtable();
			return;
		}

		mTruth[n] = true;
		PrevPermutation(n + 1);
		mTruth[n] = false;
		PrevPermutation(n + 1);
	}

	void ComputeSub()
	{
		int i = 0;
		while (i<int(str.size()))
		{
			//Operand
			if (str[i] < 91)
			{
				mOperand->Push(mTruth[mTransOperand[str[i] - 65]]);
			}
			else //Operator
			{
				if (mOperator->Empty())
				{
					if (str[i] == 'n')
						mOperator->Push({ str[i],1 });
					else
						mOperator->Push({ str[i],2 });
				}
				else  //compare
				{
					int nowpriority;
					if (str[i] == 'n')
						nowpriority = 1;
					else
						nowpriority = 2;

					while (mOperator->Top().second <= nowpriority)
					{
						Operate();
						if (mOperator->Empty())
							break;
					}

					if (str[i] == 'n')
						mOperator->Push({ str[i],1 });
					else
						mOperator->Push({ str[i],2 });
				}
			}
			i++;
		}
		while (!mOperator->Empty())
		{
			Operate();
		}
	}

	void Operate()
	{
		char oper = mOperator->Top().first;
		mOperator->Pop();
		bool right = mOperand->Top();
		mOperand->Pop();

		if (oper == 'n')      //¬
		{
			mOperand->Push(!right);
		}
		else
		{
			bool left = mOperand->Top();
			mOperand->Pop();
			if (oper == 'a')  //∧
			{
				mOperand->Push(left && right);
			}
			else if (oper == 'o') //∨
			{
				mOperand->Push(left || right);
			}
			else				  //→
			{
				mOperand->Push(!left || right);
			}
		}
	}

	void PrintTruthtable()
	{
		printf("\n");
		for (int i = 0; i < mVarnum; i++)
		{
			if (mTruth[i])
				printf("T ");
			else
				printf("F ");
		}

		if (mOperand->Top())
			printf("T\n");
		else
			printf("F\n");

		mOperand->Pop();
	}

private:
	Stack<pci>* mOperator;
	Stack<bool>* mOperand;
	std::vector<char> str;
	int mTransOperand[27];
	int mVarnum;
	bool* mTruth;
};

void Solve()
{
	Proposition prop;
	prop.Compute();
}

int main()
{
	/*std::ios::sync_with_stdio(false); std::cin.tie(NULL);*/

	Solve();

	return 0;
}