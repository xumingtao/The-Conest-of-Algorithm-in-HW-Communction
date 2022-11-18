#pragma once
//功能：求一个多元函数的最大值（这里是求二元函数的最大值：f(x1,x2) = 21.5+x1*sin(4pi*x1)+x2*sin(20pi*x2)）
#pragma once//保证文件只被编译一次
#include"get_data.h"
#include<random>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include <cstdlib>
#include <bitset>
#include<iomanip>
#include <fstream>
#include <sstream>
#include<Eigen/Dense>
using namespace std;
const double PI = 3.141592653589793;//定义一个不可改变的常量值PI
const int Po_Size = 100;//种群规模
const int Ev_Algebra = 500;//进化代数
const double Ov_Probability = 0.850; //交叉概率,交叉概率用于判断两两个体是否需要交叉
const double Va_Probability = 0.050;//变异概率,变异概率用于判断任一个体是否需要变异
const int De_Variable = 4;//函数自变量的个数,如果要进行多元函数的最值求解，直接修改自变量数个De_Variable即可
const int length1 = 216;//精确到6位小数，用24位二进制编码
const int length2 = 216;//精确到6位小数，用23位二进制编码
const int Row = 4;//行
const int Col = 6;//列
const int Ue_sum = 24;//用户总和
//vector<int>t1, t2, t3, t4, t_sum;
//for(int i=0;i)
class Different_cellMatric {
public:
	Eigen::MatrixXcd h;
	int cell;//
};
class X_Range //自变量取值范围类，适用于多个变量
{
private:
	int Upper;//变量的上界取值
	int Lower;//变量的下界取值
public:
	X_Range(int m_Upper, int m_Lower);//构造函数
	int GetUpper()const;//获取变量上限
	int GetLower()const;//获取变量下限
};
class Individual //定义个体类
{
private:
	vector<int>Cell_Variable;//用来存放四个小区的用户 
	double Fitness;//适应值
	double ReFitness;//适应值概率
	double SumFitness;//累加概率，为轮盘转做准备
public:
	Individual() {}//默认构造函数
	Individual(int* m_Variable);//构造函数
	~Individual();
	vector<int> GetVariable();//获取变量值
	void ChaFitness(const double m_fitness);//修改适应值
	void ChaReFitness(const double m_ReFitness);//修改适应值概率
	void ChaSumFitness(const double m_SumFitness);//修改累加概率
	double GetFitness()const;//获取适应值
	double GetReFitness()const;//获取适应值概率
	double GetSumFitness()const;//获取累加概率
};
void Initialize();//随机初始化种群，得到第一代个体
void CaculaFitness(vector<Different_Ue_Rb>DUR,int rbId, int spId);//计算个体的适应值
void CaculaReFitness();//计算个体的适应值概率
void CalculaSumFitness();//计算累加个体概率
void seclect();//种群选择
double Scand();//随机产生0到49的随机整数
void crossing();//杂交
void variating();//变异
void genetic_algorithm();//遗传算法

double UeMin_sinr(vector<Different_Ue_Rb>DUR, vector<Find_num>fn);
void Last_TriRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId);
void Last_SecRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int spId);
void Last_QulRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId);