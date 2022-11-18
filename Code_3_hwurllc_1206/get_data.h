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
	int cell;//小区
	vector<int>U;//存储过查询过的用户
	Find_num();
	Find_num(int sample, int rb, vector<int>U);
	~Find_num();
};
class Different_Ue_Rb {
private:
	int SampleIdx;//用户所在的小区
	int RbIdx;//用户所匹配的频带
	int UeIdx;//用户的序号
	int CellIdx;//用户所在的小区
	int TxIdx;//天线号数
	double Colldx_real;//天线的实部
	double Colldx_imag;//天线的虚部
	double W[4];//用户所在小区的权值
	Eigen::MatrixXd Tx_data;//总的天线数据
	vector<TX_> TX;//分立的天线数据
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
	Different_Ue_Rb(int SampleIdx, int Rblex, int UeIdx, int CellIdx);//构造函数
	~Different_Ue_Rb();//析构函数
};
//void Get_ChannelData(vector<Different_Ue_Rb>&DUR,int SpId);//获取信道矩阵数据
void Get_ChannelData(vector<Different_Ue_Rb>&DUR, vector<string>s_all);
void Select_Csv(int spId,vector<Different_Ue_Rb>&DUR);
std::vector<std::string> split(std::string str, std::string pattern);
std::vector<TX_> test_Eigen(Eigen::MatrixXd Shapes, int row, int col, int CellIdx, double& tar_cell_w);
double test_w(Eigen::MatrixXd Shapes, int row, int col, int CellIdx, double& tar_cell_w);
//获取基础数据
//#end if