#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#define CLEAR "clear"							//Раскомментировать для Linux, закомментировать для Windows
//#define CLEAR "cls"							//Раскомментировать для Windows, закомментировать для Linux
#define N 7								//Количество блоков

using namespace std;


void Draw_Towers(int A[N+1][3]);					//Графика))
void move_block(int A[N+1][3],int i,int Source,int Target);		//Рекурсивная функция
//unsigned long long Iter=0;						//Сколько раз функция move_block вызвала сама себя (если 2 в степени N не превышает 4млрд.)
FILE * f;								//Запишем результаты в файл



int main(int argc, char * argv[])
{

	time_t start,end;
	double dif;							//Заодно подсчитаем время работы программы
	time (&start);

	int A[N+1][3];							//Работать будем с массивом
	int Target=N%2+1;						//Целевой стержень - третий, а N может быть и четным, и нечетным (на всякий случай)
	for(int i=0;i<N;i++){A[i][0]=N-i;A[i][1]=0;A[i][2]=0;}		//Инициализация отображаемых элементов массива
	A[N][0]=-1;							//Последняя строка массива сообщает
	A[N][1]=N-1;							//нам сколько блоков еще можно надеть на стержень
	A[N][2]=N-1;							//Значение -1 соответствует заполненому стержню
	Draw_Towers(A);							//Полюбуемся стержнями пока ничего не напортачили
	f=fopen("Result.txt","w");					//Путь к файлу с результатами.
	for(int i=0;i<N;i++)
		{
		move_block(A,N-1,i%2,2);				//А вот, собственно и веселье
		time (&end);						//Пишем в файл
		dif = difftime (end,start);				//время работы программы в минутах до вставшего на место блока
		fprintf (f,"Block %d:\tWork lasts %.2f minutes.\n", i+1, dif/60 );//и число перемещенных блоков
		}
	cout<<"*******************************************"<<endl;	//Финальная "заставка"
	cout<<"*******************************************"<<endl;
	cout<<endl<<"Final:"<<endl;
	Draw_Towers(A);

	time (&end);							//Пишем в файл
	dif = difftime (end,start);					//время работы программы в минутах и число перемещений блоков
	fprintf (f,"\n-------------------------------------------------------------------------------------\nFinal:\t\tWork lasts %.2f minutes.", dif/60 );
	fclose(f);
}


void Draw_Towers(int A[N][3])
{
//	cout<<endl<<"Iter: "<<Iter<<endl;	
	system(CLEAR);							//Помогает отслеживать прогресс
	cout<<"____________________________________"<<endl;
	for(int i=0;i<N;i++)
	{//cout<<i<<":\t";						//Номера строк (для отладки) 
		for(int j=0;j<3;j++)
		{
		cout<<"\t";
		A[i][j]?cout<<A[i][j]:cout<<"|";			//Выводим номер блока или стержень
		}
	cout<<endl;	
	}
	cout<<"*************************************"<<endl;
//	for(int i=0;i<3;i++)cout<<"\t "<<A[N][i]<<" "; 			//метаданные(для отладки)
	cout<<endl;	
}



void move_block(int A[N+1][3],int i,int Source,int Target)
{
	
//	cout<<"Moving "<<i<<" from "<<Source<<" to "<<Target<<endl;	//Чего куда хотим двигать (для отладки)
	for(int jm=0;jm<N/2;jm++)
	{
	int foo;							//Пояснения ниже.
	if(A[i-1][Source]&&i)move_block(A,i-1,Source,3-Source-Target);	 //Если блок не верхний - двигаем тот, что выше
//	Если верхний блок целевого стержня "меньше" передвигаемого его необходимо подвинуть
	if((A[A[N][Target]+1][Target]>A[i][Source])&&(A[N][Target]!=N-1))
//	Морока, связанная с тем, что передвигать с целевого стержня может быть нужно и не один блок. foo - сколько именно
	{	
		foo=0;
		while((A[A[N][Target]+foo+1][Target]>A[i][Source])&&(A[N][Target]!=N-1)&&(A[N][Target]+foo+1)<N)
		foo++;
		move_block(A,A[N][Target]+foo,Target,3-Source-Target);}	//Ну и двигаем их наконец.
	}
		A[A[N][Target]][Target]=A[i][Source];			//Рутина по передвижению
		A[i][Source]=0;						//блока когда все
		A[N][Target]--;						//в порядке
		A[N][Source]++;
//		Iter++;
	Draw_Towers(A);							//Смотрим результат.
	getchar();							//Раскоментировать чтобы видеть каждый шаг. С N=64 не рекомендуется)).
	return;

}
