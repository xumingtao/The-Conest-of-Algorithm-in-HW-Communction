#include"get_data.h"
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include<map>
#include<time.h>
using namespace std;
const int sam_num = 5400;
const int Rb_num = 360;//小区内的总人数
const int Ue_num = 90;
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
//将其分装到函数中
void Select_Csv(int spId,vector<Different_Ue_Rb>&DUR)
{
	if (spId == 1)
	{
		ifstream in("Sample1.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 2)
	{
		ifstream in("Sample2.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if(spId==3)
	{
		ifstream in("Sample3.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 4)
	{
		ifstream in("Sample4.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 5)
	{
		ifstream in("Sample5.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 6)
	{
		ifstream in("Sample6.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 7)
	{
		ifstream in("Sample7.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 8)
		{
		ifstream in("Sample8.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 9)
		{
		ifstream in("Sample9.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
	else if (spId == 10)
		{
		ifstream in("Sample10.csv");
		in.seekg(0, in.end);
		int length = in.tellg();
		in.seekg(0, in.beg);
		char* temp = new char[length];
		if (in.is_open()) {
			in.read(temp, length);
		}
		string s = temp;
		vector<string>s_all = split(s, "\n");
		Get_ChannelData(DUR, s_all);
		in.close();
	}
}
void Get_ChannelData(vector<Different_Ue_Rb>&DUR, vector<string>s_all)
{
	int count = 0;
	while (count != 5400) 
	{ //循环读取每行数据
		string number;
		int  Rblex, UeIdx, CellIdx;
		string readstr = s_all[count];
		//SampleIdx = count / sam_num + 1;
		Rblex = (count % sam_num) / Rb_num + 1;
		UeIdx = (count%sam_num) % Rb_num;
		CellIdx = UeIdx / Ue_num + 1;
		//cout <<"用户信息：" <<SampleIdx<<" "<<Rblex<<" "<<UeIdx+1<<" "<<CellIdx << endl;
		Different_Ue_Rb temp(1, Rblex, UeIdx + 1, CellIdx);
		//将一行数据按'，'分割
		int count_arr = 0;
		Eigen::MatrixXd testMat(256, 2);
		vector<string> TX_zuobiao;
		TX_zuobiao = split(readstr, " ");
		while (count_arr != 512)
		{
			testMat(count_arr / 2, count_arr % 2) = atof(TX_zuobiao[count_arr].c_str());
			count_arr++;
		}
		temp.give_Mat_data(testMat);
		temp.give_TX_(test_Eigen(temp.get_Mat(), 256, 2, CellIdx, temp.weight));//目的是，将用户所在的小区标记为发射区，其他先去标记为干扰
		count++;
		//std::cout << count << endl;
		//printf("%d\n", count);
		DUR.push_back(temp);
	}
}
Different_Ue_Rb::Different_Ue_Rb()
{
	this->SampleIdx = 0;
	this->RbIdx = 0;
	this->UeIdx = 0;
	this->CellIdx = 0;
}
Different_Ue_Rb::Different_Ue_Rb(int SampleIdx, int Rblex, int UeIdx, int CellIdx)
{
	this->SampleIdx = SampleIdx;
	this->RbIdx = Rblex;
	this->UeIdx = UeIdx;
	this->CellIdx = CellIdx;
}
Different_Ue_Rb::~Different_Ue_Rb()
{	
	//delete[] Tx;
}
std::vector<TX_> test_Eigen(Eigen::MatrixXd Shapes, int row, int col, int CellIdx, double& tar_cell_w)
{
	int cols = col / 2;//列
	int rows = row;//行
	//TX_ X;
	Eigen::MatrixXcd Tt(rows, cols);
	//Eigen::MatrixXcd t1(64, cols), t2(64, cols), t3(64, cols), t4(64, cols);
	TX_ t1, t2, t3, t4;
	std::vector<TX_>store;
	Tt.real() = Shapes.leftCols(cols);
	Tt.imag() = Shapes.rightCols(cols);

	t1.tt = Tt.block<64, 1>(0, 0);
	//Eigen::MatrixXcd ff1=(t1.tt.adjoint())*t1.tt;
	//t1.W = abs(ff1(0,0));
	//t1.W = ff1.norm();
	store.push_back(t1);

	t2.tt = Tt.block<64, 1>(64, 0);
	/*Eigen::MatrixXcd ff2 = (t2.tt.adjoint())*t2.tt;
	t2.W = ff2.norm();*/
	store.push_back(t2);

	t3.tt = Tt.block<64, 1>(128, 0);
	/*Eigen::MatrixXcd ff3 = (t3.tt.adjoint())*t3.tt;
	t3.W = ff3.norm();*/
	store.push_back(t3);

	t4.tt = Tt.block<64, 1>(192, 0);
	/*Eigen::MatrixXcd ff4 = (t4.tt.adjoint())*t4.tt;
	t4.W = ff4.norm();*/
	store.push_back(t4);

	for (int i = 0; i < store.size(); i++)
	{
		if (i == (CellIdx - 1))//
		{
			//std::cout << CellIdx - 1 << std::endl;
			Eigen::MatrixXcd ff1 = (store[i].tt.adjoint())*store[i].tt;
			tar_cell_w = ff1.norm();
			store[i].flag = true;
		}
		else
			store[i].flag = false;
	}
	return store;
}
Find_num::Find_num()
{

}
Find_num::Find_num(int sample, int rb, vector<int>U)
{
	this->sample = sample;
	this->rb = rb;
	this->U = U;
	this->cell = U[0] / 90 + 1;
}
Find_num::~Find_num()
{

}