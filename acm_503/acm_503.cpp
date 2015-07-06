#include <string>   
#include <iostream>
#include <vector>

int prim(int index, int countryCount);
int kruskal(int index, int countryCount);

int data[30][26][26];

int main()
{
	int inputNum = 0;
	int countryCount[30];
	memset(data, 0, sizeof(data));
	memset(countryCount, 0, sizeof(countryCount));
	int index = 0;
	while (std::cin >> inputNum && inputNum != 0)
	{
		countryCount[index] = inputNum;
		for (int i = 0; i < inputNum - 1; ++i)
		{
			char a = 'A'; 
			int b = 0;
			char c = 'A';
			std::cin >> a;
			std::cin >> b;
			for (int j = 0; j < b*2; ++j)
			{
				if (j%2)
				{
					std::cin >> data[index][a - 'A'][c - 'A'];
					data[index][c - 'A'][a - 'A'] = data[index][a - 'A'][c - 'A'];
				}
				else
				{
					std::cin >> c;
				}
			}
		}
		++index;
	}
	//开始计算
	for (int i = 0; i < index; ++i)
	{
		std::cout << prim(i, countryCount[i]) << std::endl;
		//kruskal(i, countryCount[i]);
	}
	return 0;
}

int prim(int index, int countryCount)
{
	int totalPath = 0; 

	int lowcost[26];							//记录data[index][j][closest]的最小权值
	int closest[26];							//V-S中点j在S中的最邻接顶点
	bool s[26];
	memset(lowcost, 0, sizeof(lowcost));
	memset(closest, 0, sizeof(closest));
	memset(s, 0, sizeof(s));
	s[0] = true;

	//初始化s[i],lowcost[i],closest[i]
	for (int i = 1; i < countryCount; i++)
	{
		lowcost[i] = data[index][0][i];
		closest[i] = 1;
		s[i] = false;
	}

	for (int i = 0; i < countryCount - 1; i++)
	{
		int min = 10000000;
		int j = 0;
		for (int k = 1; k < countryCount; k++)//找出V-S中使lowcost最小的顶点j
		{
			if ((lowcost[k] != 0 && lowcost[k] < min) && (!s[k]))
			{
				min = lowcost[k];
				j = k;
			}
		}
		totalPath += lowcost[j];
		s[j] = true;//将j添加到S中

		for (int k = 1; k < countryCount; k++)//将j添加到S中后，修改closest和lowcost的值
		{	
			if (((data[index][j][k] != 0 && data[index][j][k] < lowcost[k])
				|| (lowcost[k] == 0 && data[index][j][k] > 0)) 
				&& (!s[k]))
			{
				lowcost[k] = data[index][j][k];
				closest[k] = j;
			}
		}
	}
	return totalPath;
}

int kruskal(int index, int countryCount)
{
	return 0;
}