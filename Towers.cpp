#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#define CLEAR "clear"							//����������������� ��� Linux, ���������������� ��� Windows
//#define CLEAR "cls"							//����������������� ��� Windows, ���������������� ��� Linux
#define N 7								//���������� ������

using namespace std;


void Draw_Towers(int A[N+1][3]);					//�������))
void move_block(int A[N+1][3],int i,int Source,int Target);		//����������� �������
//unsigned long long Iter=0;						//������� ��� ������� move_block ������� ���� ���� (���� 2 � ������� N �� ��������� 4����.)
FILE * f;								//������� ���������� � ����



int main(int argc, char * argv[])
{

	time_t start,end;
	double dif;							//������ ���������� ����� ������ ���������
	time (&start);

	int A[N+1][3];							//�������� ����� � ��������
	int Target=N%2+1;						//������� �������� - ������, � N ����� ���� � ������, � �������� (�� ������ ������)
	for(int i=0;i<N;i++){A[i][0]=N-i;A[i][1]=0;A[i][2]=0;}		//������������� ������������ ��������� �������
	A[N][0]=-1;							//��������� ������ ������� ��������
	A[N][1]=N-1;							//��� ������� ������ ��� ����� ������ �� ��������
	A[N][2]=N-1;							//�������� -1 ������������� ����������� �������
	Draw_Towers(A);							//���������� ��������� ���� ������ �� �����������
	f=fopen("Result.txt","w");					//���� � ����� � ������������.
	for(int i=0;i<N;i++)
		{
		move_block(A,N-1,i%2,2);				//� ���, ���������� � �������
		time (&end);						//����� � ����
		dif = difftime (end,start);				//����� ������ ��������� � ������� �� ��������� �� ����� �����
		fprintf (f,"Block %d:\tWork lasts %.2f minutes.\n", i+1, dif/60 );//� ����� ������������ ������
		}
	cout<<"*******************************************"<<endl;	//��������� "��������"
	cout<<"*******************************************"<<endl;
	cout<<endl<<"Final:"<<endl;
	Draw_Towers(A);

	time (&end);							//����� � ����
	dif = difftime (end,start);					//����� ������ ��������� � ������� � ����� ����������� ������
	fprintf (f,"\n-------------------------------------------------------------------------------------\nFinal:\t\tWork lasts %.2f minutes.", dif/60 );
	fclose(f);
}


void Draw_Towers(int A[N][3])
{
//	cout<<endl<<"Iter: "<<Iter<<endl;	
	system(CLEAR);							//�������� ����������� ��������
	cout<<"____________________________________"<<endl;
	for(int i=0;i<N;i++)
	{//cout<<i<<":\t";						//������ ����� (��� �������) 
		for(int j=0;j<3;j++)
		{
		cout<<"\t";
		A[i][j]?cout<<A[i][j]:cout<<"|";			//������� ����� ����� ��� ��������
		}
	cout<<endl;	
	}
	cout<<"*************************************"<<endl;
//	for(int i=0;i<3;i++)cout<<"\t "<<A[N][i]<<" "; 			//����������(��� �������)
	cout<<endl;	
}



void move_block(int A[N+1][3],int i,int Source,int Target)
{
	
//	cout<<"Moving "<<i<<" from "<<Source<<" to "<<Target<<endl;	//���� ���� ����� ������� (��� �������)
	for(int jm=0;jm<N/2;jm++)
	{
	int foo;							//��������� ����.
	if(A[i-1][Source]&&i)move_block(A,i-1,Source,3-Source-Target);	 //���� ���� �� ������� - ������� ���, ��� ����
//	���� ������� ���� �������� ������� "������" �������������� ��� ���������� ���������
	if((A[A[N][Target]+1][Target]>A[i][Source])&&(A[N][Target]!=N-1))
//	������, ��������� � ���, ��� ����������� � �������� ������� ����� ���� ����� � �� ���� ����. foo - ������� ������
	{	
		foo=0;
		while((A[A[N][Target]+foo+1][Target]>A[i][Source])&&(A[N][Target]!=N-1)&&(A[N][Target]+foo+1)<N)
		foo++;
		move_block(A,A[N][Target]+foo,Target,3-Source-Target);}	//�� � ������� �� �������.
	}
		A[A[N][Target]][Target]=A[i][Source];			//������ �� ������������
		A[i][Source]=0;						//����� ����� ���
		A[N][Target]--;						//� �������
		A[N][Source]++;
//		Iter++;
	Draw_Towers(A);							//������� ���������.
	getchar();							//���������������� ����� ������ ������ ���. � N=64 �� �������������)).
	return;

}
