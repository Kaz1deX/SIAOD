#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <string>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char arr[8]{0, 0, 0, 0, 0, 0, 0, 0};
    const int n = sizeof(unsigned char) * 8;      // Количество разрядов 8
    const int m = sizeof(unsigned long long) * 8; // Количество разрядов 64
    unsigned char maska = (1 << (n - 1));
    string start = "";
    int array[64];
    for (int i = 0; i < 64; i++) // Заполнение массива числами
    {
        array[i] = 63 - i;
    }
    cout << "Введите набор из 64 чисел со значениями от 0 до 63" << endl;
    for (int i = 0; i < m; i++) // Заполнение битового массива
    {
        start += to_string(array[i]) + " ";
        maska = maska >> array[i] % 8;                 // Сдвиг единицы маски на array[i] % 8 разрядов вправо
        arr[array[i] / 8] = arr[array[i] / 8] | maska; // Установка нужного разряда в единицу
        maska = (1 << (n - 1));                        // Сброс маски
    }
    cout << "Начальный набор чисел: " << start << endl;
    cout << "\nОтсортированный набор чисел: ";
    for (int i = 0; i < n; i++) // Проход по 8 битным массивам
    {
        for (int j = 1; j <= n; j++) // Проход по битам 8-ми битного массива
        {
            if (((arr[i] & maska) >> (n - j)) == 1) // Проверка на нахождение единицы очередного индекса массива
            {
                cout << (j - 1) + (n * i) << " "; // Вывод на экран индексов с учетом пройденных 8-битных массивов
            }
            maska = maska >> 1;
        }
        maska = (1 << (n - 1)); // Сброс маски
    }

    return 0;
}