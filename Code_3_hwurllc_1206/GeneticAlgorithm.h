#pragma once
//���ܣ���һ����Ԫ���������ֵ�����������Ԫ���������ֵ��f(x1,x2) = 21.5+x1*sin(4pi*x1)+x2*sin(20pi*x2)��
#pragma once//��֤�ļ�ֻ������һ��
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
const double PI = 3.141592653589793;//����һ�����ɸı�ĳ���ֵPI
const int Po_Size = 100;//��Ⱥ��ģ
const int Ev_Algebra = 500;//��������
const double Ov_Probability = 0.850; //�������,������������ж����������Ƿ���Ҫ����
const double Va_Probability = 0.050;//�������,������������ж���һ�����Ƿ���Ҫ����
const int De_Variable = 4;//�����Ա����ĸ���,���Ҫ���ж�Ԫ��������ֵ��⣬ֱ���޸��Ա�������De_Variable����
const int length1 = 216;//��ȷ��6λС������24λ�����Ʊ���
const int length2 = 216;//��ȷ��6λС������23λ�����Ʊ���
const int Row = 4;//��
const int Col = 6;//��
const int Ue_sum = 24;//�û��ܺ�
//vector<int>t1, t2, t3, t4, t_sum;
//for(int i=0;i)
class Different_cellMatric {
public:
	Eigen::MatrixXcd h;
	int cell;//
};
class X_Range //�Ա���ȡֵ��Χ�࣬�����ڶ������
{
private:
	int Upper;//�������Ͻ�ȡֵ
	int Lower;//�������½�ȡֵ
public:
	X_Range(int m_Upper, int m_Lower);//���캯��
	int GetUpper()const;//��ȡ��������
	int GetLower()const;//��ȡ��������
};
class Individual //���������
{
private:
	vector<int>Cell_Variable;//��������ĸ�С�����û� 
	double Fitness;//��Ӧֵ
	double ReFitness;//��Ӧֵ����
	double SumFitness;//�ۼӸ��ʣ�Ϊ����ת��׼��
public:
	Individual() {}//Ĭ�Ϲ��캯��
	Individual(int* m_Variable);//���캯��
	~Individual();
	vector<int> GetVariable();//��ȡ����ֵ
	void ChaFitness(const double m_fitness);//�޸���Ӧֵ
	void ChaReFitness(const double m_ReFitness);//�޸���Ӧֵ����
	void ChaSumFitness(const double m_SumFitness);//�޸��ۼӸ���
	double GetFitness()const;//��ȡ��Ӧֵ
	double GetReFitness()const;//��ȡ��Ӧֵ����
	double GetSumFitness()const;//��ȡ�ۼӸ���
};
void Initialize();//�����ʼ����Ⱥ���õ���һ������
void CaculaFitness(vector<Different_Ue_Rb>DUR,int rbId, int spId);//����������Ӧֵ
void CaculaReFitness();//����������Ӧֵ����
void CalculaSumFitness();//�����ۼӸ������
void seclect();//��Ⱥѡ��
double Scand();//�������0��49���������
void crossing();//�ӽ�
void variating();//����
void genetic_algorithm();//�Ŵ��㷨

double UeMin_sinr(vector<Different_Ue_Rb>DUR, vector<Find_num>fn);
void Last_TriRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId);
void Last_SecRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int spId);
void Last_QulRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId);