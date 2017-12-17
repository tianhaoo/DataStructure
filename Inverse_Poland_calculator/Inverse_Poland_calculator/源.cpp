#include <stack>
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//判断是否是加减乘除运算符
bool IsOperator(char ch)
{
	char ops[] = "+-*/";
	for (int i = 0; i < sizeof(ops) / sizeof(char); i++)
	{
		if (ch == ops[i])
			return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 比较两个操作符的优先级，左括号优先级最小，其次是加减，再其次是乘除。
int Precedence(char op1, char op2)
{
	if (op1 == '(')
	{
		return -1;
	}

	if (op1 == '+' || op1 == '-')
	{
		if (op2 == '*' || op2 == '/')
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	if (op1 == '*' || op1 == '/')
	{
		if (op2 == '+' || op2 == '-')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 中缀表达式转换成后缀表达式
void inFix2PostFix(char* inFix, char* postFix)
{
	int j = 0, len;
	char c;
	stack<char> st;

	len = strlen(inFix);

	for (int i = 0; i < len; i++)
	{
		c = inFix[i];

		if (c == '(')                 //如果是左括号，将其入栈
			st.push(c);
		else if (c == ')')            //如果是右括号，将直到左括号之前的运算符全部出栈
		{
			while (st.top() != '(')
			{
				postFix[j++] = st.top();
				st.pop();
			}
			st.pop();
		}
		else                           //不是括号的情况
		{
			if (!IsOperator(c))        //如果是操作数，直接入栈
				st.push(c);
			else                       //如果是运算符，弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈
			{
				while (st.empty() == false
					&& Precedence(st.top(), c) >= 0)     //循环终止的条件是栈不为空并且栈顶元素的优先级小于当前运算符
				{
					postFix[j++] = st.top();
					st.pop();
				}
				st.push(c);
			}
		}
	}

	while (st.empty() == false)      //弹出所有剩下的运算符
	{
		postFix[j++] = st.top();
		st.pop();
	}
	postFix[j] = 0;
}

//////////////////////////////////////////////////////////////////////////
// 后缀表达式求值程序
double postFixEval(char* postFix)
{
	stack<char> st;
	int len = strlen(postFix);
	char c;

	for (int i = 0; i < len; i++)
	{
		c = postFix[i];
		if (IsOperator(c) == false)
		{
			st.push(c - '0');
		}
		else
		{
			char op1, op2;
			int val;

			op1 = st.top();
			st.pop();
			op2 = st.top();
			st.pop();

			switch (c)
			{
			case '+':
				val = op1 + op2;
				break;
			case '-':
				val = op2 - op1;
				break;
			case '*':
				val = op1 * op2;
				break;
			case '/':
				val = op2 / op1;
				break;
			}
			st.push(val);
		}
	}

	return st.top();
}

int main()
{
	char inFix[100];
	char postFix[100];
	double val;

	while (1)
	{
		printf("enter an expression:");
		gets_s(inFix);
		if (strlen(inFix) == 0)
			continue;

		printf("\n%s = ", inFix);
		inFix2PostFix(inFix, postFix);
		printf("%s = ", postFix);
		val = postFixEval(postFix);
		printf("%.3f\n", val);
	}

	return 0;
}