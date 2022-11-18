#include"GeneticAlgorithm.h"//包含头文件
#include"BaseConversion.h"
#include<time.h>
//自变量取值范围向量和种群向量定义
const X_Range Range[De_Variable] = { X_Range(1,90) ,X_Range(91,180),X_Range(181,270) ,X_Range(271,360) };//自变量（或者基因）x1,x2的取值范围
vector<Individual> nowpopulation;//P(t)种群
vector<Individual> midpopulation;//中间种群，存放轮盘选择后的优秀个体
vector<Individual> nextpopulation;//P(t+1)种群
vector<Different_Ue_Rb>DUR;//所有的数据均存在于此
vector<int>t1, t2, t3, t4, t_sum;
int RB;//带宽代号
int SamPle;//样例号
//X_Range类实现
X_Range::X_Range(int m_Lower, int m_Upper) :Lower(m_Lower), Upper(m_Upper) {}//X_Range类构造函数实现
int X_Range::GetUpper()const//获取变量上限
{
	return Upper;
}
int X_Range::GetLower()const//获取变量下限
{
	return Lower;
}
//Individual类实现
Individual::Individual(int* m_Variable)//构造函数
{
	for (int i = 0; i < Row; i++)//用for循环自变量逐个赋值
	{
		for (int j = 0; j < Col; j++)
		{
			if (m_Variable[i*Col + j] >= Range[i].GetLower() && m_Variable[i*Col + j] <= Range[i].GetUpper())//这里要进行自变量取值范围判断
			{
				//cout << m_Variable[i*Col + j] << " ";
				Cell_Variable.push_back( m_Variable[i*Col+j]);//自变量赋值
			}
			else//不满足要求则发出出错警告并返回
			{
				//cout << m_Variable[i*Col + j] << " " << Range[i].GetLower() << " "<<Range[i].GetUpper() << endl;
				cerr << "自变量取值不满足要求" << endl;
				exit(1);//停止程序，我会以随机函数的方式生成自变量的值(基因值)，这里说明基因值不在规定范围内
			}
		}
	}
	//初始化时默认适应值等值为0
	this->Fitness = 0;
	this->ReFitness = 0;
	this->SumFitness = 0;
	//delete[] m_Variable;
}
Individual::~Individual()
{

}
vector<int> Individual::GetVariable()//获取基因值
{
	return Cell_Variable;
}
double Individual::GetFitness()const//获取适应值
{
	return Fitness;
}
double Individual::GetReFitness()const //获取适应值概率
{
	return ReFitness;
}
double Individual::GetSumFitness()const//获取累加概率
{
	return SumFitness;
}
void Individual::ChaFitness(const double m_fitness)//修改适应值
{
	this->Fitness = m_fitness;
}
void Individual::ChaReFitness(const double m_ReFitness)//修改适应值概率
{
	this->ReFitness = m_ReFitness;
}
void Individual::ChaSumFitness(const double m_SumFitness)//修改累加概率
{
	this->SumFitness = m_SumFitness;
}
//遗传算法的准备工作
void Initialize()//随机初始化种群，得到第一代种群
{
	//产生指定范围的随机变量（基因）
	//double X[Po_Size][De_Variable];//为了使程序可以满足多元函数最值的计算，用矩阵保存产生的随机数变量值
	//cout << t_sum.size() << endl;
	for (int i = 1; i <= 90; i++)
	{
		if (find(t_sum.begin(), t_sum.end(), i) == t_sum.end())
			t1.push_back(i);
		if (find(t_sum.begin(), t_sum.end(), i+90) == t_sum.end())
			t2.push_back(i+90);
		if (find(t_sum.begin(), t_sum.end(), i+180) == t_sum.end())
			t3.push_back(i+180);
		if (find(t_sum.begin(), t_sum.end(), i+270) == t_sum.end())
			t4.push_back(i+270);
	}
	//cout << t1.size() << " " << t2.size() << " " << t3.size() << " " << t4.size() << " " << endl;
	int X[Po_Size][Row*Col];
	for (int i = 0; i < Po_Size; i++)
	{
		default_random_engine e(time(0));//引擎，生成随机序列
		uniform_int_distribution<int> u(0, t1.size());//分布
		int temp = t1.size();
		int count = 1;
		vector<int>Temp;//用来保证插入的数据不重复
		while (count != (Ue_sum+1))
		{
			int flag =(count-1) / Col;
			if (flag == 0)
			{
				int temp1 = t1[(u(e) + count * i + rand()) % temp];
				//cout << temp1 << endl;
				if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
				{
					X[i][count-1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
					Temp.push_back(temp1);
					count++;
				}
			}
			if (flag == 1)
			{
				int temp1 = t2[(u(e) + count * i + rand()) % temp];
				//int *p1;
				if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
				{
					X[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
					Temp.push_back(temp1);
					count++;
				}
			}
			if (flag == 2)
			{
				int temp1 = t3[(u(e) + count * i + rand()) % temp];
				//int *p1;
				if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
				{
					X[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
					Temp.push_back(temp1);
					count++;
				}
			}
			if (flag == 3)
			{
				int temp1 = t4[(u(e) + count * i + rand()) % temp];
				//int *p1;
				if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
				{
					X[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
					Temp.push_back(temp1);
					count++;
				}
			}
		}
		//Temp.clear();
	}
	//生成对象（染色体）并加入到初始种群中
	for (int i = 0; i < Po_Size; i++)
	{
		//double variable[De_Variable];
		int variable[Row*Col];
		for (int j = 0; j < Row*Col; j++)
		{
			variable[j]=X[i][j];
			//cout << X[i][j] << " ";
		}
		//cout << endl;
		Individual Indivi(variable);//生成一个对象（染色体）
		nowpopulation.push_back(Indivi);//加入到种群population中
	}
	//cout << nowpopulation.size() << endl;
}
void CaculaFitness(vector<Different_Ue_Rb>DUR,int rbId,int spId)//计算个体的适应值 后面用来计算sinr值
{
	//f(x1,x2) = 21.5+x1*sin(4pi*x1)+x2*sin(20pi*x2)）为适应度计算函数
	double fitness = 0;//临时适应值
	//double x[De_Variable];//临时存储自变量（基因） 在此处进行用户到小区的转化
	int x[Row*Col];
	for (int i = 0; i < Po_Size; i++)
	{
		vector<Find_num>fn;
		//cout << "i:" << i << endl;
		for (int j = 0; j < Row; j++)
		{
			vector<int>U;
			for (int t = 0; t < Col; t++)
			{
				x[j*Col+t] = nowpopulation.at(i).GetVariable()[j*Col + t];//范围在变
				//cout << x[j*Col + t] << " ";
				U.push_back(x[j*Col + t]);
			}
			//cout << endl;
			Find_num temp1(spId,rbId,U);
			fn.push_back(temp1);
			U.clear();
			//x[j] = nowpopulation.at(i).GetVariable()[j];//这样更直观
		}
		fitness = UeMin_sinr(DUR,fn);//适应度计算
		nowpopulation.at(i).ChaFitness(fitness);//修改当前染色体的适应值
		//cout << nowpopulation.at(i).GetFitness()<<" ";
		fn.clear();
	}
	//cout << endl;
}
void CaculaReFitness()//计算适应值概率
{
	//if (RB == 2)cout << "hello world!" << endl;
	double sum = 0;//适应值累加器
	double temp = 0;
	for (int i = 0; i < Po_Size; i++)//计算出适应值之和
	{
		sum += nowpopulation.at(i).GetFitness();
	}
	for (int j = 0; j < Po_Size; j++)
	{
		temp = nowpopulation.at(j).GetFitness() / sum;//计算概率
		nowpopulation.at(j).ChaReFitness(temp);//修改个体的适应度概率
	}
}
void CalculaSumFitness()//计算累加个体概率
{
	double summation = 0;//累加器
	for (int k = 0; k < Po_Size; k++)
	{
		summation += nowpopulation.at(k).GetReFitness();
		nowpopulation.at(k).ChaSumFitness(summation);//当前累加结果赋值
	}
}
void seclect() //种群选择
{
	//随机生生成0到1的小数
	double array[Po_Size];//随机数保存变量
	default_random_engine e(time(0));//引擎，生成随机序列
	uniform_real_distribution<double> u(0.0, 1.0); //分布
	for (int i = 0; i < Po_Size; i++)
		array[i] = u(e);
	//轮盘进行选择  仔细研究下
	for (int j = 0; j < Po_Size; j++)
	{
		for (int i = 1; i < Po_Size; i++)
		{
			if (array[j] < nowpopulation[i - 1].GetSumFitness())
			{
				midpopulation.push_back(nowpopulation.at(i - 1));//加入到中间种群
			}
			if (array[j] >= nowpopulation.at(i - 1).GetSumFitness() && array[j] <= nowpopulation.at(i).GetSumFitness())
			{
				midpopulation.push_back(nowpopulation.at(i));//加入到中间种群
			}
		}
	}
	//nowpopulation.clear();//清空nowpopulation
}
double Scand() //随机产生0到1的小数
{
	int N = rand() % 999;
	return double(N) / 1000.0;;//随机产生0到1的小数
}
void crossing()//杂交
{
	int num = 0;//记录次数
	double corss = 0.0;//保存随机产生的概率值
	srand((unsigned)time(NULL));//根据系统时间设置随机数种子,设置一次随机种子就行
	//double array1[De_Variable], array2[De_Variable];//临时存储父亲和母亲的变量值
	while (num < Po_Size - 1)//个体1与个体2杂交，个体3与个体4杂交......个体i和个体i+1杂交
	{
		//判断双亲是否需要杂交，随机生成一个0到1的小数，如果这个数大于杂交概率，则放弃杂交，直接遗传给下一代，否则，对父母体进行杂交
		vector<int> Array1, Array2;//临时存储父亲和母亲的变量值
		corss = Scand();
		if (corss <= Ov_Probability)//如果corss小于等于杂交概率Ov_Probability就进行单点杂交
		{
			//首先寻找对应下标的个体并且保存
			for (int i = 0; i <Ue_sum; i++)
			{
				//cout << midpopulation.at(num).GetVariable()[i] << " " << midpopulation.at(num + 1).GetVariable()[i] << endl;
				Array1.push_back(midpopulation.at(num).GetVariable()[i]);////父亲的自变量
				Array2.push_back(midpopulation.at(num+1).GetVariable()[i]);////母亲自变量
			}
			int localx1, localx2;//记录基因交叉点的位置
			string corssx1;//作为交换基因的数组
			//int newx1[Ue_sum], newx2[Ue_sum];//分别用来保存基因交换后所对应自变量值
			//int newx1, *newx2;
			int *newx1 = new int[24];
			int *newx2 = new int[24];
			bool p1 = true, p2 = true;
			//然后对双亲变量进行编码并且进行单点杂交
			string array1b1 = toBinary(Array1);
			string array2b1 = toBinary(Array2);	
			//现在随机生成0到length1-1的数，确定交叉点的位置
			localx1 = rand() % length1;
			//cout <<"localx1:"<< localx1 << endl;
			//现在进行单点交叉，交换双亲localx1后面的基因
			corssx1 = array1b1.substr(0, localx1-1);
			/*for (int i = 0; i < localx1; i++)
					corssx1[i] = array1b1[i];*/
			for (int k = 0; k < localx1; k++)
					array1b1[k] = array2b1[k];
			for (int s = 0; s < localx1; s++)
					array2b1[s] = corssx1[s];
			//新值保存在newx1数组中，x1基因完成单点杂交操作
			newx1 = toNum(array1b1,t_sum);
			newx2 = toNum(array2b1,t_sum);
			//对新产生的值进行判断，判断是否超出范围，如果超出范围则不杂交
			if (newx1 != NULL && newx2 != NULL)
			{
				for (int f = 0; f < 4; f++)
				{
					for (int ft = f * Col; ft < f*Col + 6; ft++)
					{
						if (newx1[ft]< Range[f].GetLower() || newx1[ft]>Range[f].GetUpper() || newx2[ft]<Range[f].GetLower() || newx2[ft]>Range[f].GetUpper())
						{
							p1 = false;
							break;
						}
					}
					if (p1 == false)
						break;
				}
				/*for (int ft = 0; ft < 24; ft++)
					cout << newx1[ft] << " " << newx2[ft] << endl;*/
				if (p1 == true)
				{
					Individual newchiled1(newx1);
					//cout << "hello" << endl;
					Individual newchiled2(newx2);
					nextpopulation.push_back(newchiled1);
					nextpopulation.push_back(newchiled2);
				}
				else//将原来的个体遗传给下一代
				{
					nextpopulation.push_back(midpopulation.at(num));
					nextpopulation.push_back(midpopulation.at(num + 1));
				}
				delete[] newx1;
				delete[] newx2;
			}
			else//将原来的个体遗传给下一代
			{
				nextpopulation.push_back(midpopulation.at(num));
				nextpopulation.push_back(midpopulation.at(num + 1));
				delete[] newx1;
				delete[] newx2;
			}
		}
		else//否则直接遗传给下一代nextpopulation
		{
			nextpopulation.push_back(midpopulation.at(num));//生成一个新的个体并且加入到nextpopulation中
			nextpopulation.push_back(midpopulation.at(num + 1));
		}
		num += 2;
	}
	//cout << "midpo:" << midpopulation.size() << endl;
	//midpopulation.clear();//清空midpopulation
}
void variating()//变异
{
	int num = 0;
	while (num < Po_Size)
	{
		double variation = Scand();//随机产生一个0到1的小数，用于判断是否进行变异
		if (variation <= Va_Probability)//如果variation小于变异系数，则需要进行变异
		{
			bool p = true;
			vector<int> Array1;
			int x1local;
			for (int i = 0; i < Ue_sum; i++)
				Array1.push_back(nextpopulation.at(num).GetVariable()[i]);
			string array1 = toBinary(Array1);
			x1local = rand() % length1;//array1该位取反
			if (array1[x1local] == '0')
				array1[x1local] = '1';
			else
				array1[x1local] = '0';
			int *newx1=new int[24];
			newx1 = toNum(array1,t_sum);
			if (newx1 == NULL)
				break;
			//判断是否符合条件
			for (int f = 0; f < 4; f++)
			{
				for (int ft = f * Col; ft < f*Col + 6; ft++)
				{
					if (newx1[ft]< Range[f].GetLower() || newx1[ft]>Range[f].GetUpper())
					{
						p = false;
						break;
					}
				}
				if (p == false)
					break;
			}
			if (!p)
				nowpopulation.push_back(nextpopulation.at(num));
			if (p)
			{
				Individual newchiled(newx1);
				nowpopulation.push_back(newchiled);
			}
			delete[] newx1;
		}
		else
			nowpopulation.push_back(nextpopulation.at(num));
	num++;
	}
	//nextpopulation.clear();//清空nextpopulation
}
void genetic_algorithm()
{
	ofstream outFile;
	outFile.open("result.csv", ios::out); // 打开模式可省略
	for ( SamPle = 1; SamPle <= 10; SamPle++)
	{
		cout << "Sample:" << SamPle << endl;
		Select_Csv(SamPle, DUR);
		t_sum.clear();
		for (RB = 1; RB <= 12; RB++)
		{
			//clock_t start, end;
			//start = clock();
			Initialize();//初始化种群,随机生成第一代个体
			//进化500代
			for (int i = 0; i < 1; i++)
			{
				CaculaFitness(DUR, RB,1);//适应度计算
				CaculaReFitness();//适应度概率计算
				CalculaSumFitness();//计算累加个体概率
				seclect();//选择
				crossing();//杂交
				variating();//变异
			}
			CaculaFitness(DUR, RB,1);//适应度计算
			double maxfitness = nowpopulation.at(0).GetFitness();
			int maxid = 0;
			int k;
			bool flag = true;
			for (k = 0; k < Po_Size; k++)
			{
				//cout << nowpopulation.at(k).GetFitness() << endl;
				if (maxfitness < nowpopulation.at(k).GetFitness())
				{
					maxfitness = nowpopulation.at(k).GetFitness();
					maxid = k;
				}
			}
			cout << "第" << RB << "上的分组方案:";
			for (int t = 0; t < Ue_sum; t++)
			{
				//t_sum.push_back(t);
				t_sum.push_back(nowpopulation.at(maxid).GetVariable()[t]);
				cout << nowpopulation.at(maxid).GetVariable()[t] << " ";
			}
			//cout << endl;
			cout << endl << "最小sinr：" << nowpopulation.at(maxid).GetFitness() << endl;
			t1.clear(); t2.clear(); t3.clear(); t4.clear();
			nowpopulation.clear();
			midpopulation.clear();
			nextpopulation.clear();
			//end = clock();
			//cout << "运行时间:" << (end - start) / 1000 << endl;
		}
		//Last_SecRb(t_sum, DUR,1);
		Last_TriRb(t_sum,DUR, 1);
		//Last_QulRb(t_sum, DUR, 1);
		for (int i = 0; i < 4; i++)
			for (int j = 6 * i; j < t_sum.size(); j += 24)
				outFile << t_sum[j] << " " << t_sum[j + 1] << " " << t_sum[j + 2] << " " << t_sum[j + 3] << " " << t_sum[j + 4] << " " << t_sum[j + 5] << endl;
		DUR.clear();
	}
}

//确定最后两个rb上的数据
void Last_SecRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR,int spId)
{
	vector<int>T_sumTemp;
	T_sumTemp = T_sum;//保存原先数据
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72位数据
	int rb_last[2][24];//存放四个小区剩余的用户
	vector<int>cell1, cell2, cell3, cell4;//
	for (int i = 0; i < 12; i++)
	{
		cell1.push_back(TriRb[i]);
		cell2.push_back(TriRb[i + 12]);
		cell3.push_back(TriRb[i + 24]);
		cell4.push_back(TriRb[i + 36]);
	}
	double sinr = 0.0;
	vector<int>TT_sum;
	int num = 0;//迭代此时
	while (sinr < 4.0&&num < 100)
	{
		default_random_engine e(time(0));//引擎，生成随机序列
		uniform_int_distribution<int> u(0, cell1.size());//分布
		int LEN = cell1.size();
		//TT_sum.clear();
		vector<int>Temp;
		vector<int>Con_T;
		for (int i = 0; i < 2; i++)
		{
			int count = 1;
			while (count != 25)
			{
				if ((count - 1) / Col == 0)
				{
					int temp1 = cell1[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 1)
				{
					int temp1 = cell2[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 2)
				{
					int temp1 = cell3[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 3)
				{
					int temp1 = cell4[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
			}
		}
		vector<double> min_sinr;
		for (int i = 0; i < 2; i++)
		{
			vector<Find_num>fn;
			for (int j = 0; j < Row; j++)
			{
				vector<int>U;
				for (int t = 0; t < Col; t++)
				{
					U.push_back(rb_last[i][j*Col + t]);
					Con_T.push_back(rb_last[i][j*Col + t]);
				}
				Find_num temp1(spId, 14 + i, U);
				fn.push_back(temp1);
				//U.clear();
			}
			double tt = UeMin_sinr(DUR, fn);
			//std::cout << "第"<<i+12<<"RB："<<tt << endl;
			min_sinr.push_back(tt);
			//fn.clear();
		}
		//sinr = 10;
		sort(min_sinr.begin(), min_sinr.end());
		if (min_sinr[0] > sinr)
		{
			TT_sum = Con_T;
			sinr = min_sinr[0];
		}
		std::cout << min_sinr[0] << " " << min_sinr[1] << " " <<  endl;
		//sinr = min_sinr[0];
		num++;
	}
	for (int i = 0; i < 2; i++)
	{
		cout << "第" << 14 + i << "上的分组方案:";
		for (int j = 0; j < Ue_sum; j++)
			cout << TT_sum[i*Ue_sum + j] << " ";
		cout << endl;

	}
	for (int i = 0; i < TT_sum.size(); i++)
		T_sum.push_back(TT_sum[i]);
}
void Last_TriRb(vector<int>&T_sum,vector<Different_Ue_Rb>DUR,int SpId)
{
	vector<int>T_sumTemp;
	T_sumTemp = T_sum;//保存原先数据
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72位数据
	int rb_last[3][24];//存放四个小区剩余的用户
	vector<int>cell1, cell2, cell3, cell4;//
	for (int i = 0; i < 18; i++)
	{
		cell1.push_back(TriRb[i]);
		cell2.push_back(TriRb[i+18]);
		cell3.push_back(TriRb[i+36]);
		cell4.push_back(TriRb[i+54]);
	}
	double sinr = 0.0;
	vector<int>TT_sum;
	int num = 0;//迭代此时
	while (sinr < 4.0&&num<100)
	{
		default_random_engine e(time(0));//引擎，生成随机序列
		uniform_int_distribution<int> u(0, cell1.size());//分布
		int LEN = cell1.size();
		//TT_sum.clear();
		vector<int>Temp;
		vector<int>Con_T;
		for (int i = 0; i < 3; i++)
		{
			int count = 1;
			while (count != 25)
			{
				if ((count - 1) / Col == 0)
				{
					int temp1 = cell1[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 1)
				{
					int temp1 = cell2[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 2)
				{
					int temp1 = cell3[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 3)
				{
					int temp1 = cell4[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
			}
		}
		vector<double> min_sinr ;
		for (int i = 0; i < 3; i++)	
		{
			vector<Find_num>fn;
			for (int j = 0; j < Row; j++)
			{
				vector<int>U;
				for (int t = 0; t < Col; t++)
				{
					U.push_back(rb_last[i][j*Col + t]);
					Con_T.push_back(rb_last[i][j*Col + t]);
				}
				Find_num temp1(1, 13 + i, U);
				fn.push_back(temp1);
				//U.clear();
			}
			double tt = UeMin_sinr(DUR, fn);
			//std::cout << "第"<<i+12<<"RB："<<tt << endl;
			min_sinr.push_back(tt);
			//fn.clear();
		}
		//sinr = 10;
		sort(min_sinr.begin(), min_sinr.end());
		if (min_sinr[0] > sinr)
		{
			TT_sum = Con_T;
			sinr = min_sinr[0];
		}
		//std::cout << min_sinr[0] << " " << min_sinr[1] << " " << min_sinr[2] << endl;
		//sinr = min_sinr[0];
		num++;
	}
	for (int i = 0; i < 3; i++)
	{
		cout << "第" << 13+i << "上的分组方案:";
		for (int j = 0; j < Ue_sum; j++)
			cout << TT_sum[i*Ue_sum + j]<<" ";
		cout << endl;
	}
	cout << "最小的sinr" << sinr << endl;
	for (int i = 0; i < TT_sum.size(); i++)
		T_sum.push_back(TT_sum[i]);
	//std::cout << "ok" << endl;
}

double UeMin_sinr(vector<Different_Ue_Rb>DUR, vector<Find_num>fn)//可以减少不少的运算量
{
	//先获取每个小区所有用户的H矩阵，H1,H2,H3,H4
	vector<Eigen::MatrixXcd> H_sum;
	vector<Eigen::MatrixXcd> W_sum;
	vector<Different_cellMatric>H_Diffcell;
	//std::ofstream outFile, out_H;
	//outFile.open("test_w.txt"); // 打开模式可省略
	//out_H.open("test_H.txt");
	for (int i = 0; i < fn.size(); i++)//
	{
		Eigen::MatrixXcd H(6, 64);
		Eigen::MatrixXcd Wt(64, 6);
		int sample = fn[i].sample;//DUR[fn[i].U[j]]
		int rb = fn[i].rb;
		//cout <<"rb="<< rb << endl;
		for (int j = 0; j < fn[i].U.size(); j++)
		{
			//用户fn[i].U[j]
			//std::cout << (sample - 1) * 5400 + (rb - 1) * 360 + fn[i].U[j] - 1 << endl;
			vector<TX_> tx = DUR[(sample - 1) * 5400 + (rb - 1) * 360 + fn[i].U[j] - 1].get_TX_();
			//测试！
			for (int t = 0; t < tx.size(); t++)
			{
				if (tx[t].flag == true)
				{
					H.row(j) = tx[t].tt.col(0);
					//cout << "目标小区:" << t + 1 << endl;
					/*for (int tm = 0; tm < 64; tm++)
					{
						H(j, tm) = tx[t].tt(tm, 0);
					}*/
				}
				else {//干扰矩阵
					Different_cellMatric temp;
					temp.h = (tx[t].tt);
					temp.cell = t;
					H_Diffcell.push_back(temp);
				}
			}
		}
		//cout << "hello world" << endl;
		H_sum.push_back(H);//
		//out_H << H << endl << endl;
		Wt = (H.adjoint()*(H*H.adjoint()).inverse()) / sqrt((((H.adjoint()*(H*H.adjoint()).inverse())).adjoint()*(H.adjoint()*(H*H.adjoint()).inverse())).trace());
		//outFile << Wt << endl << endl;
		W_sum.push_back(Wt);
		//cout << Wt << endl;
	}
	//计算每个用户的sinr
	//double s1 = 0, s2 = 0, s3 = 0;
	int count = 0;
	double min_sinr = 0XFFFF;
	for (int i = 0; i < fn.size(); i++)
	{

		double s1 = 0, s2 = 0, sinr = 0.0;
		s1 = pow(abs((H_sum[i].row(0)*(W_sum[i].col(0)))(0, 0))*sqrt(0.1667), 2);//计算得到有用功率 功率pk未加
		for (int j = 0; j < fn[i].U.size(); j++)
		{
			int flag = 0;
			double s3 = 0.0;
			for (int f = 0; f < fn.size(); f++)
			{
				if (f != i)
				{
					Eigen::MatrixXcd xmt = H_Diffcell[count * 3 + flag].h;
					xmt = xmt.transpose();
					for (int ft = 0; ft < fn[f].U.size(); ft++)
					{
						/*Eigen::MatrixXcd xmt = H_Diffcell[count * 3 + flag].h;
						xmt = xmt.transpose();*/
						s3 += pow(abs((xmt*(W_sum[f].col(ft)))(0, 0))*sqrt(0.1667), 2);
					}
					flag++;
				}
			}
			count++;
			sinr = s1 / (s2 + s3 + 1);
			//std::cout << " 用户" << fn[i].U[j] << "的sinr" << sinr << endl;
			if (min_sinr > sinr)
			{
				min_sinr = sinr;//获取最小的SINR
				//min_temp = fn[i];
			}
			//std::cout << "s1=" << s1 << " s2=" << s2 << " s3=" << s3 << " 用户" << fn[i].U[j] << "的sinr:" << s1 / (s2 + s3 + 1) << std::endl;
		}
	}
	return min_sinr;
}


void Last_QulRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId)
{
	vector<int>T_sumTemp;
	T_sumTemp = T_sum;//保存原先数据
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72位数据
	int rb_last[4][24];//存放四个小区剩余的用户
	vector<int>cell1, cell2, cell3, cell4;//
	for (int i = 0; i < 24; i++)
	{
		cell1.push_back(TriRb[i]);
		cell2.push_back(TriRb[i + 24]);
		cell3.push_back(TriRb[i + 48]);
		cell4.push_back(TriRb[i + 72]);
	}
	double sinr = 0.0;
	vector<int>TT_sum;
	int num = 0;//迭代此时
	while (sinr < 6.0&&num < 50)
	{
		default_random_engine e(time(0));//引擎，生成随机序列
		uniform_int_distribution<int> u(0, cell1.size());//分布
		int LEN = cell1.size();
		//TT_sum.clear();
		vector<int>Temp;
		vector<int>Con_T;
		for (int i = 0; i < 4; i++)
		{
			int count = 1;
			while (count != 25)
			{
				if ((count - 1) / Col == 0)
				{
					int temp1 = cell1[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 1)
				{
					int temp1 = cell2[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 2)
				{
					int temp1 = cell3[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
				if ((count - 1) / Col == 3)
				{
					int temp1 = cell4[(u(e) + count * rand()) % LEN];
					//cout << temp1 << endl;
					if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
					{
						rb_last[i][count - 1] = temp1;//循环结束时，所有随机值就保存在X矩阵中
						Temp.push_back(temp1);
						count++;
					}
				}
			}
		}
		vector<double> min_sinr;
		for (int i = 0; i < 4; i++)
		{
			vector<Find_num>fn;
			for (int j = 0; j < Row; j++)
			{
				vector<int>U;
				for (int t = 0; t < Col; t++)
				{
					U.push_back(rb_last[i][j*Col + t]);
					Con_T.push_back(rb_last[i][j*Col + t]);
				}
				Find_num temp1(1, 12 + i, U);
				fn.push_back(temp1);
				//U.clear();
			}
			double tt = UeMin_sinr(DUR, fn);
			//std::cout << "第"<<i+12<<"RB："<<tt << endl;
			min_sinr.push_back(tt);
			//fn.clear();
		}
		//sinr = 10;
		sort(min_sinr.begin(), min_sinr.end());
		if (min_sinr[0] > sinr)
		{
			TT_sum = Con_T;
			sinr = min_sinr[0];
		}
		std::cout << min_sinr[0] << " " << min_sinr[1] << " " << min_sinr[2]<<" "<< min_sinr[3] << endl;
		//sinr = min_sinr[0];
		num++;
	}
	for (int i = 0; i < 4; i++)
	{
		cout << "第" << 12 + i << "上的分组方案:";
		for (int j = 0; j < Ue_sum; j++)
			cout << TT_sum[i*Ue_sum + j] << " ";
		cout << endl;

	}
	for (int i = 0; i < TT_sum.size(); i++)
		T_sum.push_back(TT_sum[i]);
	//std::cout << "ok" << endl;
}