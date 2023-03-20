#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;
// 8 2 13 4 15 6 9 11 3 7 5 10 1 12 14
string Word(string word)
{
	stringstream ss(word);
	string s;
	for (int i = 0; i < 5; i++)
	{
		ss >> s;
	}
	//cout << s << '\n';
	return s;
}

void MergeSort()
{
	long long C = 0, M = 0;
	int count = 1;        // Размер порции
	int n = 0;            // Количество элементов в файле
	int k = 0;            // Количество разделений и слияний
	string test;          // Переменная для подсчёта количества элементов в файле
	ifstream File_A;
	File_A.open("A.txt"); // Открытие файла A

	while (!File_A.eof()) // Условие для считывания всех элементов файла
	{
		getline(File_A, test); // Считывание строки из файла A
		n++;                   // После считывания очередной строки увеличить количество элементов на 1
	}
	File_A.close();       // Закрыть файл A

	ifstream file_A;
	file_A.open("A.txt");  // Открытие файла A

	ofstream file_B;
	file_B.open("B.txt");  // Открытие файла B

	ofstream file_C;
	file_C.open("C.txt");  // Открытие файла C

	string Number;         // Считываемая строка из файла
	while (!file_A.eof())  // Условие на то, чтобы продолжать считывание, пока в файле есть элементы
	{
		for (int i = 0; (i < count) and (!file_A.eof()); i++) // Условие, чтобы считать из файла необходимую порцию элементов
		{
			getline(file_A, Number);                          // Считать строку из файла A
			file_B << Number << '\n';                         // Записать считанную строку в файл B
		}
		for (int i = 0; (i < count) and (!file_A.eof()); i++)   // Условие, чтобы считать из файла необходимую порцию элементов
		{
			getline(file_A, Number);                            // Считать строку из файла A
			file_C << Number << '\n';                           // Записать считанную строку в файл C
		}
	}
	file_A.close(); // Закрыть файл A
	file_B.close(); // Закрыть файл B
	file_C.close(); // Закрыть файл C
	while (k < n)   // Условие, чтобы определённое количество раз выполнить разделение и слияние последовательности
	{
		ofstream file1_A;
		file1_A.open("A.txt");                       // Открытие файла A

		ifstream file1_B;
		file1_B.open("B.txt");                       // Открытие файла B

		ifstream file1_C;
		file1_C.open("C.txt");                       // Открытие файла C

		string number, number1, number2;             // Считываемые строки из файлов
		getline(file1_B, number1);                   // Считать строку из файла B
		getline(file1_C, number2);                   // Считать строку из файла C
		while (!file1_B.eof() and !file1_C.eof())    // Условие на то, чтобы был смысл сравнивать элементы двух файлов B и C
		{
			int x = 0, y = 0;                        // Длины текущих порций файлов B и C
			while ((!file1_B.eof()) and (!file1_C.eof()) and (x < count) and (y < count)) // В файлах B и C есть элементы и не все порции были считаны
			{
				if (Word(number1) < Word(number2))   // Сравнение строк по ключу из порции
				{
					file1_A << number1 << '\n';      // Записать строку в файл A
					getline(file1_B, number1);       // Считать строку из файла B
					M++;
					x++;                             // Увеличить текущую длину порции
				}
				else
				{
					file1_A << number2 << '\n';      // Записать строку в файл A
					getline(file1_C, number2);       // Считать строку из файла C
					M++;
					y++;                             // Увеличить текущую длину порции
				}
				C++;
			}
			while ((!file1_B.eof()) and (x < count)) // Остались ли элементы в файле B и была ли считана вся порция
			{
				file1_A << number1 << '\n';          // Записать строку в файл A
				getline(file1_B, number1);           // Считать строку из файла B
				M++;
				x++;                                 // Увеличить текущую длину порции
			}
			while ((!file1_C.eof()) and (y < count)) // Остались ли элементы в файле C и была ли считана вся порция
			{
				file1_A << number2 << '\n';          // Записать строку в файл A
				getline(file1_C, number2);           // Считать строку из файла C
				M++;
				y++;                                 // Увеличить текущую длину порции
			}
		}
		while (!file1_B.eof())                       // Остались ли элементы в файле B
		{
			file1_A << number1 << '\n';              // Записать строку в файл A
			getline(file1_B, number1);               // Считать строку из файла B
			M++;
		}
		while (!file1_C.eof())                       // Остались ли элементы в файле C
		{
			file1_A << number2 << '\n';              // Записать строку в файл A
			getline(file1_C, number2);               // Считать строку из файла C
			M++;
		}
		file1_A.close();                             // Закрыть файл A
		file1_B.close();                             // Закрыть файл B
		file1_C.close();                             // Закрыть файл C

		count = count * 2;                           // Увеличить порцию в два раза

		ifstream file2_A;
		file2_A.open("A.txt");                       // Открытие файла A

		ofstream file2_B;
		file2_B.open("B.txt");                       // Открытие файла B

		ofstream file2_C;
		file2_C.open("C.txt");                       // Открытие файла C

		getline(file2_A, number);                    // Считать строку из файла A
		while (!file2_A.eof())                       // Есть ли в файле A элементы
		{
			for (int i = 0; (i < count) and (!file2_A.eof()); i++) // Условие, чтобы считать из файла необходимую порцию элементов
			{
				file2_B << number << '\n';           // Записать считанную строку в файл B
				getline(file2_A, number);            // Считать строку из файла A
			}
			for (int i = 0; (i < count) and (!file2_A.eof()); i++) // Условие, чтобы считать из файла необходимую порцию элементов
			{
				file2_C << number << '\n';           // Записать считанную строку в файл C
				getline(file2_A, number);            // Считать строку из файла A
			}
		}
		file2_A.close(); // Закрыть файл A
		file2_B.close(); // Закрыть файл B
		file2_C.close(); // Закрыть файл C
		k++;             // Увеличить количество разделений и слияний на один
	}
	cout << "C = " << C << '\n' << "M = " << M << '\n';
	cout << "C + M = " << C + M << '\n';
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*ifstream file_A;
	int massive;
	file_A.open("A.txt");
	cout << "Исходная последовательность чисел:" << endl;
	while (!file_A.eof())
	{
		file_A >> massive;
		cout << massive << ' ';
	}
	cout << endl << endl;
	file_A.close();*/

	auto start = chrono::high_resolution_clock::now();
	MergeSort();
	auto ending = chrono::high_resolution_clock::now();
	chrono::duration<float> duration = ending - start;
	cout << "Time (время работы алгоритма) = " << duration.count() * 1000 << " ms" << '\n';
	/*file_A.open("A.txt");
	cout << "Отсортированная последовательность чисел:" << endl;
	file_A >> massive;
	while (!file_A.eof())
	{
		cout << massive << ' ';
		file_A >> massive;
	}
	file_A.close();*/
	return 0;
}