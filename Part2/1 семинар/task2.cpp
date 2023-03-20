#include <iostream>
#include <ctime>
using namespace std;

void Trans(int** matrix1, int** matrix2, int a, int b)
{
	int sravn = 0;
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			sravn += 1;
			matrix2[j][i] = matrix1[i][j];
		}
	}
	cout << "sravn = " << sravn << '\n' << '\n';
}

void Create(int** matrix, int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		matrix[i] = new int[b];
	}
}

void Print(int** matrix, int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
}

void Delete(int** matrix, int x)
{
	for (int i = 0; i < x; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main()
{
	srand(time(NULL));
	int a, b;
	cin >> a;
	cin >> b;
	cout << "\n";
	int** matrix1 = new int* [a];
	Create(matrix1, a, b);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			matrix1[i][j] = rand() % 20;
		}
	}
	int** matrix2 = new int* [b];
	Create(matrix2, b, a);
	Print(matrix1, a, b);
	cout << '\n' << '\n';
	Trans(matrix1, matrix2, a, b);
	cout << "\n";
	Print(matrix2, b, a);
	Delete(matrix1, a);
	Delete(matrix2, b);
	return 0;
}