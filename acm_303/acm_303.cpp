#include <string>   
#include <iostream>
#include <stack>
#include <vector>

bool isNum(char a);
bool compareOper(char a, char b);		//a优先或等于b返回true 否则false 

int main()
{
	char treedata[21];
	std::cin >> treedata;
	std::cout << treedata << std::endl;

	std::stack<char> symbolStack;	//运算符栈
	std::vector<char> DesVector;	//目标
	for (int i = 0; i < strlen(treedata); ++i)
	{
		if (isNum(treedata[i]))
		{
			DesVector.push_back(treedata[i]);
		}
		else
		{
			if ('(' == treedata[i])
			{
				symbolStack.push(treedata[i]);
			}
			else if (')' == treedata[i])
			{
				while (symbolStack.top() != '(')
				{
					DesVector.push_back(symbolStack.top());
					symbolStack.pop();
				}
				symbolStack.pop();
			}
			else
			{
				if (symbolStack.empty() || symbolStack.top() == '(')
				{
					symbolStack.push(treedata[i]);
				}
				else if(compareOper(treedata[i], symbolStack.top()))
				{
					symbolStack.push(treedata[i]);
				}		
				else 
				{
					DesVector.push_back(symbolStack.top());
					symbolStack.pop();
					--i;
				}
			}
		}
	}

	while (symbolStack.size() != 1)
	{
		DesVector.push_back(symbolStack.top());
		symbolStack.pop();
	}
	for (std::vector<char>::const_iterator it = DesVector.begin();
		it != DesVector.end(); ++it)
	{
		std::cout << *it << " ";
	}
	system("pause");
	return 0;
}

bool isNum(char a)
{
	return a >= '0' && a <= '9';
}

bool compareOper(char a, char b)
{
	if (a == '*' || a == '/')
	{
		return true;
	}
	else if (b == '+' || b == '-')
	{
		return true;
	}
	return false;
}