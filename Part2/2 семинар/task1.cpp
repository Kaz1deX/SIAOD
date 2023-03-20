#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

void InsertionSort(int* A, int n) // функция принимает указатель на массив и его размер
{
	long long CF = 0, MF = 0; // переменные, хранящие количество операций сравнения и количество операций перемещения

	auto start = chrono::high_resolution_clock::now(); // засечь время начала алгоритма
	for (int i = 1; i < n; i++) // цикл проходит по всем элементам массива, кроме нулевого
	{
		CF = CF + 1; // произошло 1 сравнение
		for (int j = i; (j > 0) and (A[j - 1] > A[j]); j--) // цикл меняет местами текущий элемент с предыдущим,
		{                                                   // пока текущий элемент не встанет на нужно место
			CF = CF + 2; // произошло 2 сравнения
			swap(A[j - 1], A[j]); // поменять местами элементы массива
			MF = MF + 1; // произошло 1 перемещение
		}
	}
	auto ending = chrono::high_resolution_clock::now(); // засечь время конца алгоритма

	chrono::duration<float> duration = ending - start; // вычесть из времени конца алгоритма время начала, чтобы узнать длительность алгоритма

	cout << "CF = " << CF << '\n'; // вывод на экран количества операций сравнения
	cout << "MF = " << MF << '\n'; // вывод на экран количества операций перемещения
	cout << "Time = " << duration.count() * 1000 << " ms" << '\n'; // вывод на экран длительности работы алгоритма в миллисекундах
	cout << "CF + MF = " << CF + MF; // вывод на экран суммы количества операций сравнения и количества операций перемещения
}

void Random(int* A, int n)
{
	//int value = 500000;
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 10;

		//A[i] = value;
		//value = value - 1;
	}
}

void Print(int* A, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << ' ';
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	int n;
	cin >> n;
	int* A = new int[n];
	Random(A, n);
	cout << "Количество элементов: " << n << '\n';
	//cout << "Исходный массив:" << '\n';
	//Print(A, n);
	//cout << '\n';
	InsertionSort(A, n);
	//cout << '\n' << "Отсортированный массив:" << '\n';
	//Print(A, n);
	delete[] A;
	return 0;
}