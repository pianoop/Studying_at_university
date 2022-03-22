//Logical operation
//-------------------------------------------------------------------
//Description
//
//괄호를 사용하지 않고, 연산자 우선순위는 ¬ 가장 높고 나머지 연산자들의 우선순위가 모두 같다고 가정한다.
//
//또한, 결합법칙은 왼쪽 결합법칙을 가지고 명제 변수들의 개수와 논리연산자들의 개수를 받아서 합성 명제에 대한 진리표를 작성하는 프로그램을 작성하라
//
//본 실습에서는 명제 변수의 개수를 최대3개, 논리 연산자의 개수를 최대4개로 가정한다.
//
//
//Input
//입력은 총 4가지이다.
//
//첫번째는 명제 변수의 개수이다.명제 변수는 무조건 대문자로 주어진다.
//
//두번째는 논리 연산자들의 개수이다.
//
//세번째는 입력받을 논리 연산식에 있는 명제 변수와 논리 연산자의 개수의 합이다.
//
//네번째는 논리 연산식이다.논리 연산식에서 연산 ¬은 'n'으로, ∧ 는 'a'로, ∨는 'o'로, →는 'i'로 표기한다.
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
		mData = new T[size + 1];
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
		mVars.reserve(mVarnum);
		mTruth = new bool[mVarnum];
		memset(mTruth, true, sizeof(bool) * mVarnum);
		Input();

		mOperator = new Stack<pci>(mVarnum);
		mOperand = new Stack<bool>(opernum);
	}

	~Proposition()
	{
		delete[] mTruth;
		delete mOperator;
		delete mOperand;
	}

	void Input()
	{

		int length;
		std::cin >> length;
		mProp.reserve(length);
		for (int i = 0; i < length; i++)
		{
			char tmp;
			std::cin >> tmp;
			if (tmp < 91 && mTransOperand[tmp - 65] == 0)
			{
				mVars.push_back(tmp);
				mTransOperand[tmp - 65] = -1;
			}
			mProp.push_back(tmp);
		}

		std::sort(mVars.begin(), mVars.end());
		int order = 0;
		for (int i = 0; i < mVarnum; i++)
			mTransOperand[mVars[i] - 65] = order++;
	}

	void Compute()
	{
		for (int i = 0; i < mVarnum; i++)
			printf("%c ", mVars[i]);
		printf("RESULT\n");

		PrevPermutation(0);
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
		while (i<int(mProp.size()))
		{
			//Operand
			if (mProp[i] < 91)
			{
				mOperand->Push(mTruth[mTransOperand[mProp[i] - 65]]);
			}
			else //Operator
			{
				if (mOperator->Empty())
				{
					if (mProp[i] == 'n')
						mOperator->Push({ mProp[i],1 });
					else
						mOperator->Push({ mProp[i],2 });
				}
				else  //compare
				{
					int nowpriority;
					if (mProp[i] == 'n')
						nowpriority = 1;
					else
						nowpriority = 2;

					while (mOperator->Top().second <= nowpriority)
					{
						Operate();
						if (mOperator->Empty())
							break;
					}

					if (mProp[i] == 'n')
						mOperator->Push({ mProp[i],1 });
					else
						mOperator->Push({ mProp[i],2 });
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
	std::vector<char> mProp, mVars;
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