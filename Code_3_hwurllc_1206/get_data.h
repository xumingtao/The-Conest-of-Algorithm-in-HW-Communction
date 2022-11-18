#pragma once
#include<vector>
#include<Eigen/Dense>
//#include"test.h"
using namespace std;
//vector<Different_Ue_Rb> DUR;
class TX_ {
public:
	Eigen::MatrixXcd tt;
	double W;
	bool flag;
};
class Find_num {
public:
	int sample;
	int rb;
	int cell;//С��
	vector<int>U;//�洢����ѯ�����û�
	Find_num();
	Find_num(int sample, int rb, vector<int>U);
	~Find_num();
};
class Different_Ue_Rb {
private:
	int SampleIdx;//�û����ڵ�С��
	int RbIdx;//�û���ƥ���Ƶ��
	int UeIdx;//�û������
	int CellIdx;//�û����ڵ�С��
	int TxIdx;//���ߺ���
	double Colldx_real;//���ߵ�ʵ��
	double Colldx_imag;//���ߵ��鲿
	double W[4];//�û�����С����Ȩֵ
	Eigen::MatrixXd Tx_data;//�ܵ���������
	vector<TX_> TX;//��������������
public:
	double weight;
	int get_SamleIdx() { return this->SampleIdx;}
	int get_RbIdx() { return this->RbIdx; }
	int get_UeIdx() { return this->UeIdx; }
	int get_CellIdx() { return this->CellIdx; }
	void give_W(int num, double w) {this->W[num] = w;}
	double get_W(int num) { return this->W[num]; }
	void give_Mat_data(Eigen::MatrixXd testMat) { this->Tx_data = testMat;}
	Eigen::MatrixXd get_Mat() { return this->Tx_data;}
	vector<TX_> get_TX_() { return this->TX; }
	void give_TX_(vector<TX_> tx) { this->TX = tx; }
	void give_Weight(double w) { this->weight = w; }
	Different_Ue_Rb();
	Different_Ue_Rb(int SampleIdx, int Rblex, int UeIdx, int CellIdx);//���캯��
	~Different_Ue_Rb();//��������
};
//void Get_ChannelData(vector<Different_Ue_Rb>&DUR,int SpId);//��ȡ�ŵ���������
void Get_ChannelData(vector<Different_Ue_Rb>&DUR, vector<string>s_all);
void Select_Csv(int spId,vector<Different_Ue_Rb>&DUR);
std::vector<std::string> split(std::string str, std::string pattern);
std::vector<TX_> test_Eigen(Eigen::MatrixXd Shapes, int row, int col, int CellIdx, double& tar_cell_w);
double test_w(Eigen::MatrixXd Shapes, int row, int col, int CellIdx, double& tar_cell_w);
//��ȡ��������
//#end if