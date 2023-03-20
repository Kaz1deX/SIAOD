#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <vector>
using namespace std;
string Word(string word) // Функция для получения ключа строки
{
	stringstream ss(word);
	string s;
	for (int i = 0; i < 5; i++)
	{
		ss >> s;
	}
	return s;
}

void MergeSort2()
{
	vector<int> buf; // Вектор записей для сортировки
	string test;

	ifstream file__A;
	file__A.open("A.txt");
	ofstream file__B;
	file__B.open("B.txt");
	ofstream file__C;
	file__C.open("C.txt");

	while (!file__A.eof())
	{
		for (int i = 0; (i < 5) and (!file__A.eof()); i++) // Считать 5 записей для дальнейшей сортировки
		{
			file__A >> test;
			buf.push_back(stoi(test));
			test = "";
		}
		sort(buf.begin(), buf.end());                      // Сортировать вектор
		for (int i = 0; i < 5; i++)                        // Запись отсортированных записей в файл B
		{
			file__B << buf[i] << ' ';
		}
		buf.clear();

		for (int i = 0; (i < 5) and (!file__A.eof()); i++) // Считать 5 записей для дальнейшей сортировки
		{
			file__A >> test;
			buf.push_back(stoi(test));
			test = "";
		}
		sort(buf.begin(), buf.end());                      // Сортировать вектор
		for (int i = 0; i < 5; i++)                        // Запись отсортированных записей в файл C
		{
			file__C << buf[i] << ' ';
		}
		buf.clear();
	}
	file__A.close();
	file__B.close();
	file__C.close();

	ofstream file___A;
	file___A.open("A.txt");
	ifstream file___B;
	file___B.open("B.txt");
	ifstream file___C;
	file___C.open("C.txt");

	if (!file___B.eof())
	{
		file___B >> test;
		file___A << test;
		test = "";
	}
	while (!file___B.eof())
	{
		file___B >> test;
		file___A << ' ' << test;
		test = "";
	}
	file___A << ' ';

	if (!file___C.eof())
	{
		file___C >> test;
		file___A << test;
		test = "";
	}
	while (!file___C.eof())
	{
		file___C >> test;
		file___A << ' ' << test;
		test = "";
	}
	file___A.close();
	file___B.close();
	file___C.close();

	while (1)
	{
		ifstream file_A;
		file_A.open("A.txt");
		ofstream file_B;
		file_B.open("B.txt");
		ofstream file_C;
		file_C.open("C.txt");

		int number1, number2;
		file_A >> number1;
		while (!file_A.eof())                                    // Считывание записей пока они есть в файле A
		{
			if (!file_A.eof())
			{
				file_B << number1 << ' ';
				file_A >> number2;
				while ((!file_A.eof()) and (number1 <= number2)) // Сравнение записей для записи серий в файл B
				{
					number1 = number2;
					file_B << number1 << ' ';
					file_A >> number2;
				}
			}
			number1 = number2;
			if (!file_A.eof())
			{
				file_C << number1 << ' ';
				file_A >> number2;
				while ((!file_A.eof()) and (number1 <= number2)) // Сравнение записей для записи серий в файл C
				{
					number1 = number2;
					file_C << number1 << ' ';
					file_A >> number2;
				}
			}
			number1 = number2;
		}
		file_A.close();
		file_B.close();
		file_C.close();

		ifstream file0_C;
		file0_C.open("C.txt");
		char test1;
		file0_C >> test1;
		if (file0_C.eof()) // Условие для завершения сортировки
		{
			file0_C.close();
			break;
		}
		file0_C.close();

		ofstream file1_A;
		file1_A.open("A.txt");
		ifstream file1_B;
		file1_B.open("B.txt");
		ifstream file1_C;
		file1_C.open("C.txt");

		int number1B, number2B, number1C, number2C;
		file1_B >> number1B;
		file1_C >> number1C;
		while (!file1_B.eof() and !file1_C.eof())                     // Условие на проверку наличия записей в файлах B и C
		{
			if (number1B < number1C)                                  // Сравнение записей серий двух файлов
			{
				file1_A << number1B << ' ';
				file1_B >> number2B;
				if (!file1_B.eof() and (number1B > number2B))         // Сравнение поочерёдных записей
				{
					file1_A << number1C << ' ';
					file1_C >> number2C;
					while (!file1_C.eof() and (number1C <= number2C)) // Сравнение поочерёдных записей
					{
						number1C = number2C;
						file1_A << number1C << ' ';
						file1_C >> number2C;
					}
					number1C = number2C;
				}
				number1B = number2B;
			}
			else
			{
				file1_A << number1C << ' ';
				file1_C >> number2C;
				if (!file1_C.eof() and (number1C > number2C))
				{
					file1_A << number1B << ' ';
					file1_B >> number2B;
					while (!file1_B.eof() and (number1B <= number2B)) // Сравнение поочерёдных записей
					{
						number1B = number2B;
						file1_A << number1B << ' ';
						file1_B >> number2B;
					}
					number1B = number2B;
				}
				number1C = number2C;
			}
		}
		while (!file1_B.eof()) // Условие на то, остались ли запсии в файле B
		{
			file1_A << number1B << ' ';
			file1_B >> number1B;
		}
		while (!file1_C.eof()) // Условие на то, остались ли запсии в файле C
		{
			file1_A << number1C << ' ';
			file1_C >> number1C;
		}
		file1_A.close();
		file1_B.close();
		file1_C.close();
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	auto start = chrono::high_resolution_clock::now();
	MergeSort2();
	auto ending = chrono::high_resolution_clock::now();
	chrono::duration<float> duration = ending - start;
	cout << "Time (время работы алгоритма) = " << duration.count() * 1000 << " ms" << '\n';

	//cout << "Исходная последовательность чисел:" << '\n' << "17 31 5 59 13 41 43 67 11 23 29 47 3 7 71 2 19 57 37 61" << '\n' << '\n' << "Отсортированная последовательность чисел:" << '\n' << "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 57 59 61 67 71";
	return 0;
}