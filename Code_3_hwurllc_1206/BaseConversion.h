#pragma once
//验证进制转换
//1，十进制转为二进制
//2.二进制转为十进制
#include<iostream>
#include<vector>
#include<string>
using namespace std;
string toBinary(vector<int>m);
int * toNum(string s, vector<int>T_sum);//将string变成vector<int>数据