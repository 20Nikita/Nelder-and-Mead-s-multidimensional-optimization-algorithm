#include <iostream>
#include <iomanip>

using namespace std;

const int i = 2;		//колличество переменных
const int j = i + 1;	//колличество вершин

//-----------------------------------ФУЕКЦИИ
//
//нет мин, но есть мах(0,1)
//double F(double x[2]) { return -(-x[0] * x[0] - x[1] * x[1] + x[0] * x[1] - x[0] + 2 * x[1]); }
//
//для самопроверки мин(0.0)
//double F(double x[2]) { return (x[0]) * (x[0]) + x[1] * x[1]; }
//
//нет мах и минимуа, но есль локальные минимумы в (.) = (0.0) и (1.1)
double F(double x[2]) { return ((x[0] - x[1]) * (x[0] - x[1]) + 7 * (x[1] * x[1] - x[0]) * (x[1] * x[1] - x[0])); }
//----------------------------------------------------------------------------------//

//-------------УСЛОВИЕ ОСТАНОВКИ (ДИСПЕРСИЯ)
double D(double xh[2], double xg[2], double xl[2], double xc[2])
{ return sqrt(1 / (j + 1) * ((F(xh)) - F(xc)) * ((F(xh)) - F(xc)) + ((F(xg)) - F(xc)) * ((F(xg)) - F(xc)) + ((F(xl)) - F(xc)) * ((F(xl)) - F(xc))); }


void сорт(double x[j][i]);
void Таблица(double x[j][i], double	х_наим[2], double	х_2_по_велечене[2], double	х_наиб[2], double	центр_тяж[2], double	отр[2], double	отр_рас[2], double	отр_сжат[2], int k);

int main() {
	system("color F0");				//фон белый буквы черные
	int n;							//индексная переменная
	int k = 0;						//количество итераций
	bool f = 0;						//вспомогательный флаг
	double Temp[i];					//обменная переменная

	double Eps = 0.01;				//точность
	double	a = 1;					//коэфицент отражения
	double	b = 0.5;				//коэфицент сжатия
	double	y = 2;					//коэфицент рястяжения
	//начальный набор точек

	double	х_наиб[2];			//точка с наибольшем значением функции
	double	х_2_по_велечене[2];	//точка с 2 по велечине значением функции
	double	х_наим[2];			//точка с самым маленьким значением функции

	double	центр_тяж[2];		//центр тяжести
	double	отр[2];				//отраженный х
	double	отр_рас[2];			//отраженный х c растяжением
	double	отр_сжат[2];		//отраженный х с жатеем

	double	x[j][i] = { { -2,-2 },{ -1,-1 },{ 0,-1 } };
	setlocale(LC_ALL, "Russian");
	cout << "Введите Eps : ";
	cin >> Eps;
	cout << "Введите коэфицент отражения : ";
	cin >> a;
	cout << "Введите коэфицент сжатия : ";
	cin >> b;
	cout << "Введите коэфицент рястяжения : ";
	cin >> y;
	setlocale(LC_ALL, "C");

	cout << "\n\n" << char(218) << setfill(char(196)) << setw(154) << char(191) << endl;
	do {
		k++;
		сорт(x);	//сортировка точек
		for (n = 0; n < i; n++)
		{
			центр_тяж[n] = 0;
			отр[n] = 0;
			отр_рас[n] = 0;
			отр_сжат[n] = 0;
			х_наиб[n] = x[i][n];
			х_2_по_велечене[n] = x[i - 1][n];
			х_наим[n] = x[0][n];
		}
		f = 0;

		//поиск центра тяжести
		for (n = 0; n < i; n++)
			for (int m = 0; m < i; m++)
				центр_тяж[n] = центр_тяж[n] + (x[m][n]);
		центр_тяж[0] = центр_тяж[0] / i; центр_тяж[1] = центр_тяж[1] / i;

		for (n = 0; n < i; n++)
			отр[n] = центр_тяж[n] + a * (центр_тяж[n] - х_наиб[n]);

		if (F(отр) <= F(х_наим))
		{
			for (n = 0; n < i; n++)
				отр_рас[n] = центр_тяж[n] + y * (отр[n] - центр_тяж[n]);
			double x7 = F(отр_рас);

			if (F(отр_рас) < F(отр))
				for (n = 0; n < i; n++)
					х_наиб[n] = отр_рас[n];
			else
				for (n = 0; n < i; n++)
					х_наиб[n] = отр[n];
		}
		else if (F(х_наим) <= F(отр) && F(отр) <= F(х_2_по_велечене))
		{
			for (n = 0; n < i; n++)
				х_наиб[n] = отр[n];
		}
		else if (F(х_2_по_велечене) <= F(отр) && F(отр) <= F(х_наиб))
		{
			for (n = 0; n < i; n++)
			{
				Temp[n] = отр[n];
				отр[n] = х_наиб[n];
				х_наиб[n] = Temp[n];
				f = 1;
			}
		}
		else if (F(х_наиб) <= F(отр))
			f = 1;
		if (f) {
			for (n = 0; n < i; n++)
				отр_сжат[n] = центр_тяж[n] + b * (х_наиб[n] - центр_тяж[n]);

			if (F(отр_сжат) < F(х_наиб))
				for (n = 0; n < i; n++)
					х_наиб[n] = отр_сжат[n];

			if (F(отр_сжат) >= F(х_наиб))
			{
				for (n = 0; n < i; n++)
				{
					x[i][n] = х_наиб[n];
					x[i - 1][n] = х_2_по_велечене[n];
					x[0][n] = х_наим[n];
				}
				сорт(x);	//сортировка точек
				for (n = 0; n < i; n++)
				{
					х_наиб[n] = x[i][n];
					х_2_по_велечене[n] = x[i - 1][n];
					х_наим[n] = x[0][n];
				}
				for (n = 0; n < i; n++)
				{
					х_наиб[n] = (х_наиб[n] + х_наим[n]) / 2;
					х_2_по_велечене[n] = (х_2_по_велечене[n] + х_наим[n]) / 2;
				}
			}
		}
		for (n = 0; n < i; n++)
		{
			x[i][n] = х_наиб[n];
			x[i - 1][n] = х_2_по_велечене[n];
			x[0][n] = х_наим[n];
		}

		Таблица(x, х_наим, х_2_по_велечене, х_наиб , центр_тяж, отр , отр_рас, отр_сжат, k);
		
	} while (fabs(D(х_наиб, х_2_по_велечене, х_наим, центр_тяж)) > Eps);

	сорт(x);	//сортировка точек

	cout << char(179) << " k = " << left << setfill(char(32)) << setw(17) << k << right
		<< "x* = (" << setfill(char(32)) << setw(7) << round(x[0][0] * 100) / 100
		<< " : " << left << setfill(char(32)) << setw(7) << round(x[0][1] * 100) / 100 << right << ")     "
		<< "f(x*) = " << left << setfill(char(32)) << setw(21) << round(F(x[0]) * 100) / 100 << right
		<< setfill(char(32)) << setw(74) << char(179) << endl;
	cout << char(192) << setfill(char(196)) << setw(154) << char(217) << "\n\n";
	system("pause");
}

void сорт(double x[j][i])
{
	double Min;                	//минимальный элемент
	int jMin;					//индекс минимального элемента
	int iSort;					//граница отсортированной области
	int k;						//индексная переменная
	double Temp[i];				//обменная переменная

	for (iSort = 0; iSort < j - 1; iSort++)
	{
		//первый элемент из неупорядоченных назначаем минимальным
		Min = F(x[iSort]);				//минимум
		jMin = iSort;					//его индекс

		//ищем минимальный элемент в оставшейся части массива
		for (k = iSort + 1; k < j; k++)
		{
			if (F(x[k]) < Min)		//очередной кандидат на минимальный
			{
				//запоминаем минимальный элемент и его номер
				Min = F(x[k]);
				jMin = k;
			}//if

		}//for j

		//нашли минимум в неупорядоченной части массива
		//ставим его на место первого в неупорядоченной части массива
		//меняем элементы местами
		for (k = 0; k < i; k++)
		{
			Temp[k] = x[iSort][k];
			x[iSort][k] = x[jMin][k];
			x[jMin][k] = Temp[k];
		}
	} //for iSort
}

void Таблица(double x[j][i], double	х_наим[2], double	х_2_по_велечене[2], double	х_наиб[2], double	центр_тяж[2], double	отр[2], double	отр_рас[2], double	отр_сжат[2], int k)
{
	cout << char(179) << " k = " << left << setfill(char(32)) << setw(17) << k << right
		<< "x1 = (" << setfill(char(32)) << setw(7) << round(x[0][0] * 100) / 100
		<< " : " << left << setfill(char(32)) << setw(7) << round(x[0][1] * 100) / 100 << right<< ")     "
		<< "x2 = (" << setfill(char(32)) << setw(7) << round(x[1][0] * 100) / 100
		<< " : " << left << setfill(char(32)) << setw(7) << round(x[1][1] * 100) / 100 << right << ")     "
		<< "x3 = (" << setfill(char(32)) << setw(7) << round(x[2][0] * 100) / 100
		<< " : " << left << setfill(char(32)) << setw(7) << round(x[2][1] * 100) / 100 << right << ")     "
		<< setfill(char(32)) << setw(45) << char(179) << endl;

	cout << char(179) << setfill(char(32)) << setw(30)
		<< "f(x1) = " << left << setfill(char(32)) << setw(21) << round(F(х_наим) * 100) / 100 << right
		<< "f(x2) = " << left << setfill(char(32)) << setw(21) << round(F(х_2_по_велечене) * 100) / 100 << right
		<< "f(x3) = " << left << setfill(char(32)) << setw(21) << round(F(х_наиб) * 100) / 100 << right
		<< setfill(char(32)) << setw(45) << char(179) << endl;

	cout << char(195);
	cout << setfill(char(196)) << setw(22);
	for (int i = 0; i < 6; i++)
	{
		cout << char(194) << setfill(char(196)) << setw(22);
	}
	cout << char(180) << endl;

	cout << char(179) << "          xl         "
		 << char(179) << "          xg         "
		 << char(179) << "          xh         "
		 << char(179) << "          xc         "
		 << char(179) << "          xr         "
		 << char(179) << "          xe         "
		 << char(179) << "          xs         "
		 << char(179) << endl;

	cout << char(179) << "        f(xl)        "
		 << char(179) << "        f(xg)        "
		 << char(179) << "        f(xh)        "
		 << char(179) << "        f(xc)        "
		 << char(179) << "        f(xr)        "
		 << char(179) << "        f(xe)        "
		 << char(179) << "        f(xs)        "
		 << char(179) << endl;

	cout << char(195);
	cout << setfill(char(196)) << setw(22);
	for (int i = 0; i < 6; i++)
	{
		cout << char(197) << setfill(char(196)) << setw(22);
	}
	cout << char(180) << endl;
	/*
	double* arrays[] = { х_наим, х_2_по_велечене, х_наиб, центр_тяж, отр, отр_рас, отр_сжат };
	int arrays_size = sizeof(arrays)/sizeof(arrays[0]);*/

	/*for (int i = 0; i < arrays_size; ++i) {
		cout << char(179) << " (" 
			<< fixed << setprecision(2) << arrays[i][0] << "; " << left
			<< arrays[i][1] << right << ") ";
	}
	cout << endl;*/

	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(х_наим[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(х_наим[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(х_2_по_велечене[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(х_2_по_велечене[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(х_наиб[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(х_наиб[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(центр_тяж[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(центр_тяж[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(отр[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(отр[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(отр_рас[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(отр_рас[1] * 100) / 100 << right << ") ";
	cout << char(179) << " (" << setfill(char(32)) << setw(7) << round(отр_сжат[0] * 100) / 100 << " ; " << left << setfill(char(32)) << setw(7) << round(отр_сжат[1] * 100) / 100 << right << ") ";
	cout << char(179) << endl;

	cout << char(179) << setfill(char(32)) << setw(13) << round(F(х_наим) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(х_2_по_велечене) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(х_наиб) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(центр_тяж) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(отр) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(отр_рас) * 100) / 100 << "        ";
	cout << char(179) << setfill(char(32)) << setw(13) << round(F(отр_сжат) * 100) / 100 << "        ";
	cout << char(179) << endl;

	cout << char(195);
	cout << setfill(char(196)) << setw(22);
	for (int i = 0; i < 6; i++)
	{
		cout << char(193) << setfill(char(196)) << setw(22);
	}
	cout << char(180) << endl;
}