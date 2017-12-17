#include <stack>
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//�ж��Ƿ��ǼӼ��˳������
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
// �Ƚ����������������ȼ������������ȼ���С������ǼӼ���������ǳ˳���
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
// ��׺���ʽת���ɺ�׺���ʽ
void inFix2PostFix(char* inFix, char* postFix)
{
	int j = 0, len;
	char c;
	stack<char> st;

	len = strlen(inFix);

	for (int i = 0; i < len; i++)
	{
		c = inFix[i];

		if (c == '(')                 //����������ţ�������ջ
			st.push(c);
		else if (c == ')')            //����������ţ���ֱ��������֮ǰ�������ȫ����ջ
		{
			while (st.top() != '(')
			{
				postFix[j++] = st.top();
				st.pop();
			}
			st.pop();
		}
		else                           //�������ŵ����
		{
			if (!IsOperator(c))        //����ǲ�������ֱ����ջ
				st.push(c);
			else                       //�����������������������ȼ����ڻ��ߵ��ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ
			{
				while (st.empty() == false
					&& Precedence(st.top(), c) >= 0)     //ѭ����ֹ��������ջ��Ϊ�ղ���ջ��Ԫ�ص����ȼ�С�ڵ�ǰ�����
				{
					postFix[j++] = st.top();
					st.pop();
				}
				st.push(c);
			}
		}
	}

	while (st.empty() == false)      //��������ʣ�µ������
	{
		postFix[j++] = st.top();
		st.pop();
	}
	postFix[j] = 0;
}

//////////////////////////////////////////////////////////////////////////
// ��׺���ʽ��ֵ����
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