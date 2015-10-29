#include <fstream>
#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;

const int NUMBERS_WIDTH = 9;

int CreateArray (string** &arr, int amount_str, int amount_col);
int DetermineStrCol (int &amount_str, int &amount_col);
int FillPrintArray (string** &arr, int amount_str, int amount_col);
int CreateNewFileCol (string** arr, bool* numbers_col, int amount_str, int amount_col);
int CreateNewFileStr (string** arr, bool* numbers_str, int amount_str, int amount_col);
int CreateNewFileColStr (string** arr, bool* numbers_col, bool* numbers_str, int amount_str, int amount_col);
int InputColNumbers (bool* numbers_col, int amount_col);
int InputStrNumbers (bool* numbers_str, int amount_str);
int InputStepEps (int &step, int &eps);
int CreateNewFileStep(string** arr, int step, int eps, int amount_col, int amount_str);

int main()
{
	int amount_str = 0, amount_col = 0, step = 0, eps = 0;
	setlocale(LC_ALL, "rus");
	string** arr;

	DetermineStrCol(amount_str, amount_col);
		
	cout << endl << "Количество строк = " << amount_str;
	cout << endl << "Количество столбцов = " << amount_col << endl;

	CreateArray(arr, amount_str, amount_col);
	FillPrintArray(arr, amount_str, amount_col);
	
	bool* numbers_col = new bool [amount_col];
	bool* numbers_str;
	numbers_str = new bool [amount_str + 1];

	int choice;
	cout << endl << "Удалить столбцы - введите 1." << endl << "Удалить строки - введите 2." << endl << "Удалить строки и столбцы - введите 3." << endl << endl;
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
			InputStepEps(step, eps);
			/*InputStrNumbers(numbers_str, amount_str);
			CreateNewFileStr(arr, numbers_str, amount_str, amount_col);*/
			break;
		}
	case 3:
		{
			/*InputColNumbers(numbers_col, amount_col);
			InputStrNumbers(numbers_str, amount_str);
			CreateNewFileColStr(arr, numbers_col, numbers_str, amount_str, amount_col);*/
			break;
		}
	}
	cout << endl << "Новый файл new_test.txt сформирован." << endl; 

	system("pause");
    return 0;
}

int CreateArray(string** &arr, int amount_str, int amount_col)
{
	arr = new string* [amount_str];
	for ( int i = 0; i < amount_str; i++ )
		arr[i] = new string [amount_col];
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
int FillPrintArray (string** &arr, int amount_str, int amount_col)
{
	ifstream fout("test.txt");
	for ( int i = 0; i < amount_str; i++ )
	{
		for ( int j = 0; j < amount_col; j++ )
		{	
			fout >> arr[i][j];
			cout << setw(6) << arr[i][j];
		}
		cout << endl;
	}
	return 0;
}
int CreateNewFileCol(string** arr, bool* numbers_col, int amount_str, int amount_col)
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
			}
		}
	fin << endl;
	}
	fin.close();
	return 0;
}

int CreateNewFileStr (string** arr, bool* numbers_str, int amount_str, int amount_col)
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
int CreateNewFileColStr (string** arr, bool* numbers_col, bool* numbers_str, int amount_str, int amount_col)
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
int InputStepEps (int &step, int &eps)
{
	cout << endl << "Введите нужных строк и погрешность (через пробел)." << endl << "Для завершения ввода номеров строк введите любую букву." << endl;
	cin >> step >> eps;
	return 0;
}
int CreateNewFileStep(string** arr, int step, int eps, int amount_col, int amount_str)
{
	for ( int i = 0; i < amount_col; i++ )
	{
		fin << setw(NUMBERS_WIDTH) << arr[0][i];
	}
	ofstream fin("new_test.txt");
	fin.clear();

	for ( int i = 0; i < step-2; i++ )
	{
		
	}
	return 0;
}