#include"BaseConversion.h"
//#include"GeneticAlgorithm.h"
#include<bitset>
string toBinary(vector<int>m)
{
	string r;
	for (int i = 0; i < m.size(); i++)
	{
		bitset<9> bs1(m[i]);
		int count = bs1.size();
		while (count--)
		{
			r += (bs1[count] == 0 ? "0" : "1");
		}
	}
	return r;
}
int * toNum(string s,vector<int>T_sum)//将string变成vector<int>数据
{
	 int *m=new int[24];
	int count = 0;
	bool p = false;
	for (int i = 0; i < s.length(); i+=9)
	{
		int temp=0;//用来纪录数据
		for (int j = i; j < i + 9; j++)
		{
			//bitset<1> bs4(s[j]);
			int cun=(s[j] == '0' ? 0 :2);
			temp += pow(cun, 9-j % 9);
		}
		if (find(T_sum.begin(), T_sum.end(), temp / 2) != T_sum.end())
			p = true;
		m[count++] = temp / 2;
		//m.push_back(temp/2);
	}
	if (p)
		return NULL;
	else
		return m;
}