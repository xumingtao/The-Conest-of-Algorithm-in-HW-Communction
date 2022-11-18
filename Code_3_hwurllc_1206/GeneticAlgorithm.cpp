#include"GeneticAlgorithm.h"//����ͷ�ļ�
#include"BaseConversion.h"
#include<time.h>
//�Ա���ȡֵ��Χ��������Ⱥ��������
const X_Range Range[De_Variable] = { X_Range(1,90) ,X_Range(91,180),X_Range(181,270) ,X_Range(271,360) };//�Ա��������߻���x1,x2��ȡֵ��Χ
vector<Individual> nowpopulation;//P(t)��Ⱥ
vector<Individual> midpopulation;//�м���Ⱥ���������ѡ�����������
vector<Individual> nextpopulation;//P(t+1)��Ⱥ
vector<Different_Ue_Rb>DUR;//���е����ݾ������ڴ�
vector<int>t1, t2, t3, t4, t_sum;
int RB;//�������
int SamPle;//������
//X_Range��ʵ��
X_Range::X_Range(int m_Lower, int m_Upper) :Lower(m_Lower), Upper(m_Upper) {}//X_Range�๹�캯��ʵ��
int X_Range::GetUpper()const//��ȡ��������
{
	return Upper;
}
int X_Range::GetLower()const//��ȡ��������
{
	return Lower;
}
//Individual��ʵ��
Individual::Individual(int* m_Variable)//���캯��
{
	for (int i = 0; i < Row; i++)//��forѭ���Ա��������ֵ
	{
		for (int j = 0; j < Col; j++)
		{
			if (m_Variable[i*Col + j] >= Range[i].GetLower() && m_Variable[i*Col + j] <= Range[i].GetUpper())//����Ҫ�����Ա���ȡֵ��Χ�ж�
			{
				//cout << m_Variable[i*Col + j] << " ";
				Cell_Variable.push_back( m_Variable[i*Col+j]);//�Ա�����ֵ
			}
			else//������Ҫ���򷢳������沢����
			{
				//cout << m_Variable[i*Col + j] << " " << Range[i].GetLower() << " "<<Range[i].GetUpper() << endl;
				cerr << "�Ա���ȡֵ������Ҫ��" << endl;
				exit(1);//ֹͣ�����һ�����������ķ�ʽ�����Ա�����ֵ(����ֵ)������˵������ֵ���ڹ涨��Χ��
			}
		}
	}
	//��ʼ��ʱĬ����Ӧֵ��ֵΪ0
	this->Fitness = 0;
	this->ReFitness = 0;
	this->SumFitness = 0;
	//delete[] m_Variable;
}
Individual::~Individual()
{

}
vector<int> Individual::GetVariable()//��ȡ����ֵ
{
	return Cell_Variable;
}
double Individual::GetFitness()const//��ȡ��Ӧֵ
{
	return Fitness;
}
double Individual::GetReFitness()const //��ȡ��Ӧֵ����
{
	return ReFitness;
}
double Individual::GetSumFitness()const//��ȡ�ۼӸ���
{
	return SumFitness;
}
void Individual::ChaFitness(const double m_fitness)//�޸���Ӧֵ
{
	this->Fitness = m_fitness;
}
void Individual::ChaReFitness(const double m_ReFitness)//�޸���Ӧֵ����
{
	this->ReFitness = m_ReFitness;
}
void Individual::ChaSumFitness(const double m_SumFitness)//�޸��ۼӸ���
{
	this->SumFitness = m_SumFitness;
}
//�Ŵ��㷨��׼������
void Initialize()//�����ʼ����Ⱥ���õ���һ����Ⱥ
{
	//����ָ����Χ���������������
	//double X[Po_Size][De_Variable];//Ϊ��ʹ������������Ԫ������ֵ�ļ��㣬�þ��󱣴���������������ֵ
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
		default_random_engine e(time(0));//���棬�����������
		uniform_int_distribution<int> u(0, t1.size());//�ֲ�
		int temp = t1.size();
		int count = 1;
		vector<int>Temp;//������֤��������ݲ��ظ�
		while (count != (Ue_sum+1))
		{
			int flag =(count-1) / Col;
			if (flag == 0)
			{
				int temp1 = t1[(u(e) + count * i + rand()) % temp];
				//cout << temp1 << endl;
				if (find(Temp.begin(), Temp.end(), temp1) == Temp.end())
				{
					X[i][count-1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
					X[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
					X[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
					X[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
					Temp.push_back(temp1);
					count++;
				}
			}
		}
		//Temp.clear();
	}
	//���ɶ���Ⱦɫ�壩�����뵽��ʼ��Ⱥ��
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
		Individual Indivi(variable);//����һ������Ⱦɫ�壩
		nowpopulation.push_back(Indivi);//���뵽��Ⱥpopulation��
	}
	//cout << nowpopulation.size() << endl;
}
void CaculaFitness(vector<Different_Ue_Rb>DUR,int rbId,int spId)//����������Ӧֵ ������������sinrֵ
{
	//f(x1,x2) = 21.5+x1*sin(4pi*x1)+x2*sin(20pi*x2)��Ϊ��Ӧ�ȼ��㺯��
	double fitness = 0;//��ʱ��Ӧֵ
	//double x[De_Variable];//��ʱ�洢�Ա��������� �ڴ˴������û���С����ת��
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
				x[j*Col+t] = nowpopulation.at(i).GetVariable()[j*Col + t];//��Χ�ڱ�
				//cout << x[j*Col + t] << " ";
				U.push_back(x[j*Col + t]);
			}
			//cout << endl;
			Find_num temp1(spId,rbId,U);
			fn.push_back(temp1);
			U.clear();
			//x[j] = nowpopulation.at(i).GetVariable()[j];//������ֱ��
		}
		fitness = UeMin_sinr(DUR,fn);//��Ӧ�ȼ���
		nowpopulation.at(i).ChaFitness(fitness);//�޸ĵ�ǰȾɫ�����Ӧֵ
		//cout << nowpopulation.at(i).GetFitness()<<" ";
		fn.clear();
	}
	//cout << endl;
}
void CaculaReFitness()//������Ӧֵ����
{
	//if (RB == 2)cout << "hello world!" << endl;
	double sum = 0;//��Ӧֵ�ۼ���
	double temp = 0;
	for (int i = 0; i < Po_Size; i++)//�������Ӧֵ֮��
	{
		sum += nowpopulation.at(i).GetFitness();
	}
	for (int j = 0; j < Po_Size; j++)
	{
		temp = nowpopulation.at(j).GetFitness() / sum;//�������
		nowpopulation.at(j).ChaReFitness(temp);//�޸ĸ������Ӧ�ȸ���
	}
}
void CalculaSumFitness()//�����ۼӸ������
{
	double summation = 0;//�ۼ���
	for (int k = 0; k < Po_Size; k++)
	{
		summation += nowpopulation.at(k).GetReFitness();
		nowpopulation.at(k).ChaSumFitness(summation);//��ǰ�ۼӽ����ֵ
	}
}
void seclect() //��Ⱥѡ��
{
	//���������0��1��С��
	double array[Po_Size];//������������
	default_random_engine e(time(0));//���棬�����������
	uniform_real_distribution<double> u(0.0, 1.0); //�ֲ�
	for (int i = 0; i < Po_Size; i++)
		array[i] = u(e);
	//���̽���ѡ��  ��ϸ�о���
	for (int j = 0; j < Po_Size; j++)
	{
		for (int i = 1; i < Po_Size; i++)
		{
			if (array[j] < nowpopulation[i - 1].GetSumFitness())
			{
				midpopulation.push_back(nowpopulation.at(i - 1));//���뵽�м���Ⱥ
			}
			if (array[j] >= nowpopulation.at(i - 1).GetSumFitness() && array[j] <= nowpopulation.at(i).GetSumFitness())
			{
				midpopulation.push_back(nowpopulation.at(i));//���뵽�м���Ⱥ
			}
		}
	}
	//nowpopulation.clear();//���nowpopulation
}
double Scand() //�������0��1��С��
{
	int N = rand() % 999;
	return double(N) / 1000.0;;//�������0��1��С��
}
void crossing()//�ӽ�
{
	int num = 0;//��¼����
	double corss = 0.0;//������������ĸ���ֵ
	srand((unsigned)time(NULL));//����ϵͳʱ���������������,����һ��������Ӿ���
	//double array1[De_Variable], array2[De_Variable];//��ʱ�洢���׺�ĸ�׵ı���ֵ
	while (num < Po_Size - 1)//����1�����2�ӽ�������3�����4�ӽ�......����i�͸���i+1�ӽ�
	{
		//�ж�˫���Ƿ���Ҫ�ӽ����������һ��0��1��С�����������������ӽ����ʣ�������ӽ���ֱ���Ŵ�����һ�������򣬶Ը�ĸ������ӽ�
		vector<int> Array1, Array2;//��ʱ�洢���׺�ĸ�׵ı���ֵ
		corss = Scand();
		if (corss <= Ov_Probability)//���corssС�ڵ����ӽ�����Ov_Probability�ͽ��е����ӽ�
		{
			//����Ѱ�Ҷ�Ӧ�±�ĸ��岢�ұ���
			for (int i = 0; i <Ue_sum; i++)
			{
				//cout << midpopulation.at(num).GetVariable()[i] << " " << midpopulation.at(num + 1).GetVariable()[i] << endl;
				Array1.push_back(midpopulation.at(num).GetVariable()[i]);////���׵��Ա���
				Array2.push_back(midpopulation.at(num+1).GetVariable()[i]);////ĸ���Ա���
			}
			int localx1, localx2;//��¼���򽻲���λ��
			string corssx1;//��Ϊ�������������
			//int newx1[Ue_sum], newx2[Ue_sum];//�ֱ�����������򽻻�������Ӧ�Ա���ֵ
			//int newx1, *newx2;
			int *newx1 = new int[24];
			int *newx2 = new int[24];
			bool p1 = true, p2 = true;
			//Ȼ���˫�ױ������б��벢�ҽ��е����ӽ�
			string array1b1 = toBinary(Array1);
			string array2b1 = toBinary(Array2);	
			//�����������0��length1-1������ȷ��������λ��
			localx1 = rand() % length1;
			//cout <<"localx1:"<< localx1 << endl;
			//���ڽ��е��㽻�棬����˫��localx1����Ļ���
			corssx1 = array1b1.substr(0, localx1-1);
			/*for (int i = 0; i < localx1; i++)
					corssx1[i] = array1b1[i];*/
			for (int k = 0; k < localx1; k++)
					array1b1[k] = array2b1[k];
			for (int s = 0; s < localx1; s++)
					array2b1[s] = corssx1[s];
			//��ֵ������newx1�����У�x1������ɵ����ӽ�����
			newx1 = toNum(array1b1,t_sum);
			newx2 = toNum(array2b1,t_sum);
			//���²�����ֵ�����жϣ��ж��Ƿ񳬳���Χ�����������Χ���ӽ�
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
				else//��ԭ���ĸ����Ŵ�����һ��
				{
					nextpopulation.push_back(midpopulation.at(num));
					nextpopulation.push_back(midpopulation.at(num + 1));
				}
				delete[] newx1;
				delete[] newx2;
			}
			else//��ԭ���ĸ����Ŵ�����һ��
			{
				nextpopulation.push_back(midpopulation.at(num));
				nextpopulation.push_back(midpopulation.at(num + 1));
				delete[] newx1;
				delete[] newx2;
			}
		}
		else//����ֱ���Ŵ�����һ��nextpopulation
		{
			nextpopulation.push_back(midpopulation.at(num));//����һ���µĸ��岢�Ҽ��뵽nextpopulation��
			nextpopulation.push_back(midpopulation.at(num + 1));
		}
		num += 2;
	}
	//cout << "midpo:" << midpopulation.size() << endl;
	//midpopulation.clear();//���midpopulation
}
void variating()//����
{
	int num = 0;
	while (num < Po_Size)
	{
		double variation = Scand();//�������һ��0��1��С���������ж��Ƿ���б���
		if (variation <= Va_Probability)//���variationС�ڱ���ϵ��������Ҫ���б���
		{
			bool p = true;
			vector<int> Array1;
			int x1local;
			for (int i = 0; i < Ue_sum; i++)
				Array1.push_back(nextpopulation.at(num).GetVariable()[i]);
			string array1 = toBinary(Array1);
			x1local = rand() % length1;//array1��λȡ��
			if (array1[x1local] == '0')
				array1[x1local] = '1';
			else
				array1[x1local] = '0';
			int *newx1=new int[24];
			newx1 = toNum(array1,t_sum);
			if (newx1 == NULL)
				break;
			//�ж��Ƿ��������
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
	//nextpopulation.clear();//���nextpopulation
}
void genetic_algorithm()
{
	ofstream outFile;
	outFile.open("result.csv", ios::out); // ��ģʽ��ʡ��
	for ( SamPle = 1; SamPle <= 10; SamPle++)
	{
		cout << "Sample:" << SamPle << endl;
		Select_Csv(SamPle, DUR);
		t_sum.clear();
		for (RB = 1; RB <= 12; RB++)
		{
			//clock_t start, end;
			//start = clock();
			Initialize();//��ʼ����Ⱥ,������ɵ�һ������
			//����500��
			for (int i = 0; i < 1; i++)
			{
				CaculaFitness(DUR, RB,1);//��Ӧ�ȼ���
				CaculaReFitness();//��Ӧ�ȸ��ʼ���
				CalculaSumFitness();//�����ۼӸ������
				seclect();//ѡ��
				crossing();//�ӽ�
				variating();//����
			}
			CaculaFitness(DUR, RB,1);//��Ӧ�ȼ���
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
			cout << "��" << RB << "�ϵķ��鷽��:";
			for (int t = 0; t < Ue_sum; t++)
			{
				//t_sum.push_back(t);
				t_sum.push_back(nowpopulation.at(maxid).GetVariable()[t]);
				cout << nowpopulation.at(maxid).GetVariable()[t] << " ";
			}
			//cout << endl;
			cout << endl << "��Сsinr��" << nowpopulation.at(maxid).GetFitness() << endl;
			t1.clear(); t2.clear(); t3.clear(); t4.clear();
			nowpopulation.clear();
			midpopulation.clear();
			nextpopulation.clear();
			//end = clock();
			//cout << "����ʱ��:" << (end - start) / 1000 << endl;
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

//ȷ���������rb�ϵ�����
void Last_SecRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR,int spId)
{
	vector<int>T_sumTemp;
	T_sumTemp = T_sum;//����ԭ������
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72λ����
	int rb_last[2][24];//����ĸ�С��ʣ����û�
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
	int num = 0;//������ʱ
	while (sinr < 4.0&&num < 100)
	{
		default_random_engine e(time(0));//���棬�����������
		uniform_int_distribution<int> u(0, cell1.size());//�ֲ�
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
			//std::cout << "��"<<i+12<<"RB��"<<tt << endl;
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
		cout << "��" << 14 + i << "�ϵķ��鷽��:";
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
	T_sumTemp = T_sum;//����ԭ������
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72λ����
	int rb_last[3][24];//����ĸ�С��ʣ����û�
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
	int num = 0;//������ʱ
	while (sinr < 4.0&&num<100)
	{
		default_random_engine e(time(0));//���棬�����������
		uniform_int_distribution<int> u(0, cell1.size());//�ֲ�
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
			//std::cout << "��"<<i+12<<"RB��"<<tt << endl;
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
		cout << "��" << 13+i << "�ϵķ��鷽��:";
		for (int j = 0; j < Ue_sum; j++)
			cout << TT_sum[i*Ue_sum + j]<<" ";
		cout << endl;
	}
	cout << "��С��sinr" << sinr << endl;
	for (int i = 0; i < TT_sum.size(); i++)
		T_sum.push_back(TT_sum[i]);
	//std::cout << "ok" << endl;
}

double UeMin_sinr(vector<Different_Ue_Rb>DUR, vector<Find_num>fn)//���Լ��ٲ��ٵ�������
{
	//�Ȼ�ȡÿ��С�������û���H����H1,H2,H3,H4
	vector<Eigen::MatrixXcd> H_sum;
	vector<Eigen::MatrixXcd> W_sum;
	vector<Different_cellMatric>H_Diffcell;
	//std::ofstream outFile, out_H;
	//outFile.open("test_w.txt"); // ��ģʽ��ʡ��
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
			//�û�fn[i].U[j]
			//std::cout << (sample - 1) * 5400 + (rb - 1) * 360 + fn[i].U[j] - 1 << endl;
			vector<TX_> tx = DUR[(sample - 1) * 5400 + (rb - 1) * 360 + fn[i].U[j] - 1].get_TX_();
			//���ԣ�
			for (int t = 0; t < tx.size(); t++)
			{
				if (tx[t].flag == true)
				{
					H.row(j) = tx[t].tt.col(0);
					//cout << "Ŀ��С��:" << t + 1 << endl;
					/*for (int tm = 0; tm < 64; tm++)
					{
						H(j, tm) = tx[t].tt(tm, 0);
					}*/
				}
				else {//���ž���
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
	//����ÿ���û���sinr
	//double s1 = 0, s2 = 0, s3 = 0;
	int count = 0;
	double min_sinr = 0XFFFF;
	for (int i = 0; i < fn.size(); i++)
	{

		double s1 = 0, s2 = 0, sinr = 0.0;
		s1 = pow(abs((H_sum[i].row(0)*(W_sum[i].col(0)))(0, 0))*sqrt(0.1667), 2);//����õ����ù��� ����pkδ��
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
			//std::cout << " �û�" << fn[i].U[j] << "��sinr" << sinr << endl;
			if (min_sinr > sinr)
			{
				min_sinr = sinr;//��ȡ��С��SINR
				//min_temp = fn[i];
			}
			//std::cout << "s1=" << s1 << " s2=" << s2 << " s3=" << s3 << " �û�" << fn[i].U[j] << "��sinr:" << s1 / (s2 + s3 + 1) << std::endl;
		}
	}
	return min_sinr;
}


void Last_QulRb(vector<int>&T_sum, vector<Different_Ue_Rb>DUR, int SpId)
{
	vector<int>T_sumTemp;
	T_sumTemp = T_sum;//����ԭ������
	vector<int>TriRb;
	for (int i = 1; i <= 360; i++)
	{
		if (find(T_sum.begin(), T_sum.end(), i) == T_sum.end())
			TriRb.push_back(i);
	}
	//TriRb.sort();
	sort(TriRb.begin(), TriRb.end());//72λ����
	int rb_last[4][24];//����ĸ�С��ʣ����û�
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
	int num = 0;//������ʱ
	while (sinr < 6.0&&num < 50)
	{
		default_random_engine e(time(0));//���棬�����������
		uniform_int_distribution<int> u(0, cell1.size());//�ֲ�
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
						rb_last[i][count - 1] = temp1;//ѭ������ʱ���������ֵ�ͱ�����X������
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
			//std::cout << "��"<<i+12<<"RB��"<<tt << endl;
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
		cout << "��" << 12 + i << "�ϵķ��鷽��:";
		for (int j = 0; j < Ue_sum; j++)
			cout << TT_sum[i*Ue_sum + j] << " ";
		cout << endl;

	}
	for (int i = 0; i < TT_sum.size(); i++)
		T_sum.push_back(TT_sum[i]);
	//std::cout << "ok" << endl;
}