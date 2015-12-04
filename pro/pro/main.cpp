#include <fstream>
#include <iostream>
#include <string>
#include <iomanip> 
#include <stdlib.h>
#include <math.h>
//#include <boost/lexical_cast.hpp>

using namespace std;

const int NUMBERS_WIDTH = 9;
//const int k = 2;

int CreateArray (double** &arr, int amount_str, int amount_col);
int DetermineStrCol (int &amount_str, int &amount_col);
void FillPrintArray (double** arr, int amount_str, int amount_col);
int CreateNewFileCol (double** arr, bool* numbers_col, int amount_str, int amount_col);
int CreateNewFileStr (double** arr, bool* numbers_str, int amount_str, int amount_col);
int CreateNewFileColStr (double** arr, bool* numbers_col, bool* numbers_str, int amount_str, int amount_col);
int InputColNumbers (bool* numbers_col, int amount_col);
int InputStrNumbers (bool* numbers_str, int amount_str);
int InputStepEps (int &step, double &eps, int &num_col);
//int CreateNewFileStep(string** arr, int step, double eps, int amount_col, int amount_str, int k);
int CreateNewFileStep(double** arr, int amount_str, int amount_col, int step, int col_number, double eps);
void PrintArray (double** &arr, int amount_str, int amount_col);

int main()
{
	int amount_str = 0, amount_col = 0, step = 0, num_col = 0;
	double eps = 0;
	setlocale(LC_ALL, "rus");
	double** arr;
	arr = NULL;

	DetermineStrCol(amount_str, amount_col);
		
	cout << endl << "Количество строк = " << amount_str;
	cout << endl << "Количество столбцов = " << amount_col << endl;

	CreateArray(arr, amount_str, amount_col);
	FillPrintArray(arr, amount_str, amount_col);
	
	bool* numbers_col = new bool [amount_col];
	bool* numbers_str;
	numbers_str = new bool [amount_str + 1];

	int choice;
	cout << endl << "Удалить столбцы - введите 1." << endl << "Удалить строки - введите 2." << endl << /*"Удалить строки и столбцы - введите 3." <<*/ endl << endl;
	cin >> choice;

	switch (choice) 
	{
	case 1:
		{
			InputColNumbers(numbers_col, amount_col);
			CreateNewFileCol(arr, numbers_col, amount_str, amount_col);		
			break;
		}
	case 2:
		{	
			InputStepEps(step, eps, num_col);                                      //!!!!!!!!!!!!!!!!!!!!!!!!!!
			CreateNewFileStep(arr, amount_str, amount_col, step, num_col, eps);
			/*InputStrNumbers(numbers_str, amount_str);
			CreateNewFileStr(arr, numbers_str, amount_str, amount_col);*/
			break;
		}
	////case 3:
	////	{
	////		/*InputColNumbers(numbers_col, amount_col);
	////		InputStrNumbers(numbers_str, amount_str);
	////		CreateNewFileColStr(arr, numbers_col, numbers_str, amount_str, amount_col);*/
	////		break;
	////	}
	}


	cout << endl << "Новый файл new_test.txt сформирован." << endl; 

	system("pause");
    return 0;
}

int CreateArray(double** &arr, int amount_str, int amount_col)
{
	arr = new double* [amount_str];
	for ( int i = 0; i < amount_str; i++ ) {
			arr[i] = new double[amount_col];
	}
/*
	arr = new double* [500];
	for ( int i = 0; i < 500; i++ )
		arr[i] = new double;
	return 0;

	arr = new double* [amount_str + 1];
	for ( int i = 0; i < amount_str + 1; i++ ) {
		for ( int j = 0; j < amount_col + 1; j++)
			arr[i][j] = new double[];
	}

	arr = new double* [amount_str + 1];
	for ( int i = 0; i < amount_str + 1; i++ )
		arr[i] = new double;*/
	return 0;
}

int DetermineStrCol(int &amount_str, int &amount_col)
{
	char buff[100];
	ifstream fin("test.txt");	
	fin.getline(buff, 100);
	char *pointer = strtok(buff, " ");
	while (pointer != NULL)
	{
		amount_col++;
		pointer = strtok (NULL, " ");
	}	
	amount_str++;
	while ( !fin.eof() )
	{
		char p[20];
 		fin.getline(p, 20);
		amount_str++;
	}
	fin.close();
	return 0;
}
void FillPrintArray (double** arr, int amount_str, int amount_col)
{
	ifstream fout("test.txt");
	char str[20];
	fout >> str;
	double temp = atof(str);
	if ( temp == 0 ) {
	}
	for ( int i = 0; i < amount_str; i++ )
	{
		for ( int j = 0; j < amount_col; j++ )
		{	
			fout >> str;
			arr[i][j] = atof(str);
			cout << setw(6) << arr[i][j];
		}
		cout << endl;
	}
	fout.close();
}
int CreateNewFileCol(double** arr, bool* numbers_col, int amount_str, int amount_col)
{
	ofstream fin("new_test.txt");
	fin.clear();
	for ( int i = 0; i < amount_str; i++ )
	{
		for ( int j = 0; j < amount_col; j++ )
		{
			if ( numbers_col[j] != false )
			{
				fin << setw(NUMBERS_WIDTH) << arr[i][j];
				cout << setw(NUMBERS_WIDTH) << arr[i][j];
			}
		}
	fin << endl;
	cout << endl;
	}
	fin.close();
	return 0;
}

int CreateNewFileStr (double** arr, bool* numbers_str, int amount_str, int amount_col)
{
	ofstream fin("new_test.txt");
	fin.clear();
	for ( int i = 0; i < amount_str; i++ )
	{
		if ( numbers_str[i] != false )
		{
			for ( int j = 0; j < amount_col; j++ )	
				fin << setw(NUMBERS_WIDTH) << arr[i][j];
			fin << endl;
		}
	}
	fin.close();
	return 0;
}
int CreateNewFileColStr (double** arr, bool* numbers_col, bool* numbers_str, int amount_str, int amount_col)
{
	ofstream fin("new_test.txt");
	fin.clear();
	for ( int i = 0; i < amount_str; i++ )
	{
		if ( numbers_str[i] != false )
		{
			for ( int j = 0; j < amount_col; j++ )	
			{
				if ( numbers_col[j] != false )
				{
					fin << setw(NUMBERS_WIDTH) << arr[i][j];
				}
			}
			fin << endl;
		}
	
	}
	fin.close();
	return 0;
	return 0;
}
int InputColNumbers(bool* numbers_col, int amount_col)
{
	cout << endl << "Введите номера столбцов для удаления (через Enter)." << endl << "Для завершения ввода номеров столбцов введите любую букву." << endl;
	string temp;
	int n;
	do
	{
	cin >> temp;
	n = atoi(temp.c_str());
	if ( n <= amount_col )
		numbers_col[n-1] = false;
	else
		cout << endl << "Введенное число больше количества столбцов." << endl;
	}
	while ( n != 0);
	return 0;
}
int InputStrNumbers (bool* numbers_str, int amount_str)
{
	cout << endl << "Введите номера строк для удаления (через Enter или через пробел)." << endl << "Для завершения ввода номеров строк введите любую букву." << endl;
	string temp;
	int n;
	do
	{
		cin >> temp;
		n = atoi(temp.c_str());
		if ( n <= amount_str-1 )
			numbers_str[n] = false;
		else
			cout << endl << "Введенное число больше количества строк." << endl;
	}
	while ( n != 0);
	numbers_str[0] = true;
	return 0;
}
int InputStepEps (int &step, double &eps, int &num_col)
{
	cout << endl << "Введите шаг:" << endl;
	cin >> step;
	cout << endl << "Введите погрешность:" << endl;
	cin >> eps;
	cout << endl << "Введите номер столбца, по которому будем прорежевать:" << endl;
	cin >> num_col;
	num_col--;
	return 0;
}
int CreateNewFileStep(double** arr, int amount_str, int amount_col, int step, int col_number, double eps) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	ofstream fin("new_test.txt");
	fin.clear();

	for ( int k = 0; k < amount_col; k++ )
	{
		fin << setw(NUMBERS_WIDTH) << arr[0][k];
		cout << setw(NUMBERS_WIDTH) << arr[0][k]; 
	}
	fin << endl;
	cout << endl;

	for ( int k = 0; k < amount_col; k++ )
	{
		fin << setw(NUMBERS_WIDTH) << arr[1][k];
		cout << setw(NUMBERS_WIDTH) << arr[1][k]; 
	}
	fin << endl;
	cout << endl;

	int ptr_tek_el = 1;
	int j = ptr_tek_el + 1;
	while ( j < amount_str )
	{		
		while ( (j < ptr_tek_el + step) && (j < amount_str) )
		{
			double arr_ptr = arr[ptr_tek_el][col_number];
			float arr_tek = arr[j][col_number];
			
			if ( abs((arr_ptr - arr_tek)/arr_ptr) > eps )
			{
				for ( int k = 0; k < amount_col; k++ )
				{
					fin << setw(NUMBERS_WIDTH) << arr[j][k];
					cout << setw(NUMBERS_WIDTH) << arr[j][k]; 
				}
				fin << endl;
				cout << endl;
				ptr_tek_el = j;
				j = ptr_tek_el + 1;
			}
			else
				j = j+1;
		}
		if ( ptr_tek_el + step < amount_str)
		{
			for ( int k = 0; k < amount_col; k++ )
					{
						fin << setw(NUMBERS_WIDTH) << arr[ptr_tek_el + step][k];
						cout << setw(NUMBERS_WIDTH) << arr[ptr_tek_el + step][k]; 
					}
					fin << endl;
					cout << endl;
					ptr_tek_el += step;
					j = ptr_tek_el + 1;
		}
	}

	fin.close();
	return 0;
}
void PrintArray ( double** &arr, int amount_str, int amount_col ) {
	for ( int i = 0; i < amount_str; i++ )
	{
		for ( int j = 0; j < amount_col; j++ )
		{	
			cout << setw(6) << arr[i][j];
		}
		cout << endl;
	}
}
//int CreateNewFileStep(string** arr, int amount_str, int amount_col, int step, int col_number, double eps) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//{
//	ofstream fin("new_test.txt");
//	fin.clear();
//
//	for ( int j = 0; j < amount_col; j++ )
//	{
//		fin << setw(NUMBERS_WIDTH) << arr[0][j];
//		cout << setw(NUMBERS_WIDTH) << arr[0][j]; 
//	}
//	fin << endl;
//	cout << endl;
//
//
//	for ( int j = 0; j < amount_col; j++ )
//	{
//		fin << setw(NUMBERS_WIDTH) << arr[1][j];
//		cout << setw(NUMBERS_WIDTH) << arr[1][j]; 
//	}
//	fin << endl;
//	cout << endl;
//
//	//int ptr_tek_el = 1; //указатель на текущий элемент(для сравнения и печати)
//	int i = 1;
//	while ( i < amount_str )
//	{
//		bool flag = false;
//		int perem;
//		int j = i + 1;
//		while ( (j != i + step) || ( i >= amount_str) )
//		{
//			
//			double arr_ptr = atof(arr[i][col_number].c_str());
//			double arr_tek = atof(arr[j][col_number].c_str());
//			if ( abs(arr_ptr - arr_tek) > eps  )
//			{
//				flag = true;
//				for ( int k = 0; k < amount_col; k++ )
//				{
//					fin << setw(NUMBERS_WIDTH) << arr[j][k];
//					cout << setw(NUMBERS_WIDTH) << arr[j][k];
//				}
//				fin << endl;
//				cout << endl;
//
//
//				perem = j;
//				i = perem;	
//				j = i + 1;
//			}
//			else 
//				j++;
//		//ptr_tek_el += step;	
//		
//		}
//		
//		for ( int k = 0; k < amount_col; k++ )
//		{
//			fin << setw(NUMBERS_WIDTH) << arr[i + step][k];
//			cout << setw(NUMBERS_WIDTH) << arr[i + step][k];
//		}
//		fin << endl;
//		cout << endl;
//
//		i += step;
//
//		//j = i + step;
//		/*if ( flag == false ) 
//		{
//			for ( int k = 0; k < amount_col; k++ )
//			{
//				fin << setw(NUMBERS_WIDTH) << arr[i + step][k];
//				cout << setw(NUMBERS_WIDTH) << arr[i + step][k];
//			}
//			fin << endl;
//			cout << endl;*/
//		//	i += step;
//
//		//}
//
//		//else 
//		//	i = perem;
//		
//	}
//
//	fin.close();
//	return 0;
//}
//int CreateNewFileStep(string** arr, int step, double eps, int amount_col, int amount_str, int k)
//{
//	ofstream fin("new_test.txt");
//	fin.clear();
//
//	for ( int i = 0; i < amount_col; i++ )
//	{
//		fin << setw(NUMBERS_WIDTH) << arr[0][i];
//	}
//	fin << endl;
//
//	int number_col_from = 1, number_col_to;
//	for ( int i = 1; i < step-1; i++ )
//	{
//		double temp_value;
//		
//		number_col_to = amount_col/(step-1)*i;
//		double value_col_to = ::strtod(arr[number_col_to][k].c_str(), 0);
//		//double value_col_from = (double)atof(arr[number_col_from][k]);
//		double value_col_from = ::strtod(arr[number_col_from][k].c_str(), 0);
//		//::strtod(num.c_str(), 0)
//		double temp_max = 0;
//		int number_diff = 0;
//		for ( int j = number_col_from+1; j < number_col_to; j++ )
//		{
//			temp_value = ::strtod(arr[j][k].c_str(), 0);
//			if ( abs(temp_value - value_col_to) > temp_max)
//			{
//				temp_max = abs(temp_value - value_col_to);
//				number_diff = j;
//			}
//			if ( abs(temp_value - value_col_from) > temp_max)
//			{
//				temp_max = abs(temp_value - value_col_from);
//				number_diff = j;
//			}
//		}
//		if ( temp_max > eps )
//		{			
//			for ( int i = 0; i < step-2; i++ )
//			{
//				fin << setw(NUMBERS_WIDTH) << arr[number_diff][i];
//			}
//			fin << endl;
//		}
//		for ( int i = 0; i < step-2; i++ )
//			{
//				fin << setw(NUMBERS_WIDTH) << arr[number_col_to][i];
//			}
//		fin << endl;
//		number_col_from = number_col_to;
//	}
//	fin.close(); 
//	return 0;
//}