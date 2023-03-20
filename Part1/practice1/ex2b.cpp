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

    unsigned long long arr = 0;                   // Исходный битовый массив
    const int n = sizeof(unsigned long long) * 8; // Количество разрядов
    unsigned long long maska = (((unsigned long long)1) << (n - 1));
    string start = "";
    int array[64];
    for (int i = 0; i < 64; i++) // Заполнение массива числами
    {
        array[i] = 63 - i;
    }
    cout << "Введите набор из 64 чисел со значениями от 0 до 63" << endl;
    for (int i = 0; i < n; i++) // Заполнение битового массива
    {
        start += to_string(array[i]) + " ";
        maska = maska >> array[i];                  // Сдвиг единицы маски на array[i] разрядов вправо
        arr = arr | maska;                          // Установка нужного разряда в единицу
        maska = ((unsigned long long)1 << (n - 1)); // Сброс маски
    }
    cout << "Начальный набор чисел: " << start << endl;
    cout << "\nОтсортированный набор чисел: ";
    for (int i = 1; i <= n; i++) // Вывод отсортированного набора чисел
    {
        if (((arr & maska) >> (n - i)) == 1) // Проверка на нахождение единицы очередного индекса массива
        {
            cout << i - 1 << " ";
        }
        maska = maska >> (unsigned long long)1;
    }

    return 0;
}