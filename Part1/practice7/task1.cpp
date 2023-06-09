#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

int minim(int a, int b) // Определение наименьшего числа из двух чисел
{
    if(a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int inf = 1000000000;       // Заведомо большое число
    int n = 5, m = 6;           // Размер поля
    vector<vector<int>> matrix1 // Поле со значениями времени
            {
                    {1, 3, 4, 2, 7, 6},
                    {3, 20, 12, 9, 4, 1},
                    {8, 5, 4, 3, 7, 5},
                    {3, 7, 11, 10, 5, 13},
                    {2, 6, 7, 9, 4, 9}
            };
    cout << "Имеется поле движения черепашки, размером 5 на 6:\n";
    for(auto& i : matrix1) // Вывод на экран поля
    {
        for(auto& j : i)
        {
            cout << j << '\t';
        }
        cout << '\n';
    }
    cout << "Черепашке нужно попасть из ЛЕВОГО НИЖНЕГО угла в ПРАВЫЙ ВЕРХНИЙ угол\n";
    cout << "\nЧерепашка может перемещаться только ВВЕРХ или ВПРАВО\n";
    cout << "\nНа каждой клетке известно время движения в эту клетку\n";

    vector<vector<int>> matrix2(n, vector<int>(m)); // Создание второго поля, которое будет хранить промежуточные результаты
    matrix2[4][0] = 2;

    for (int j = 1; j < m; j++) {  // Заполнение клеток самой нижней строки суммой времени в текущей клетке и времени в левой клетки
        matrix2[4][j] = matrix2[4][j-1] + matrix1[4][j];
    }
    for (int i = 3; i >= 0; i--) { // Заполнение клеток самого левого столбца суммой времени в текущей клетке и времени в нижней клетки
        matrix2[i][0] = matrix2[i+1][0] + matrix1[i][0];
    }

    // Заполнение оставшихся клеток суммой времени в текущей клетке и наименьшим временем из левой и нижней клетки
    for (int i = 3; i >= 0; i--) {
        for (int j = 1; j < m; j++) {
            matrix2[i][j] = minim(matrix2[i+1][j], matrix2[i][j-1]) + matrix1[i][j];
        }
    }

    cout << "\nС помощью метода динамического программирования получим:\n";
    cout << "Минимальное время, за которое черепашка может попасть из ЛЕВОГО НИЖНЕГО угла в ПРАВЫЙ ВЕРХНИЙ угол - " << matrix2[0][m-1];

    // Вывод на экран поля с промежуточными результатами
    cout << "\n\nПоле с промежуточными результатами:\n";
    for(auto& i : matrix2)
    {
        for(auto& j : i)
        {
            cout << j << '\t';
        }
        cout << '\n';
    }

    return 0;
}