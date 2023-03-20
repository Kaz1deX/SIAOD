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

    unsigned char arr = 0;                   // Исходный битовый массив
    const int n = sizeof(unsigned char) * 8; // Количество разрядов
    unsigned char maska = (1 << (n - 1));
    int x;      // Вводимые числа
    int action; // Действие для прекращения считывания чисел
    string start = "";
    cout << "Введите набор до 8-ми чисел со значениями от 0 до 7" << endl;
    for (int i = 0; i < n; i++) // Заполнение битового массива
    {
        cout << "Хотите остановить ввод? 1 - Да, 2 - Нет" << endl;
        cin >> action;
        if (action == 1)
        {
            break;
        }
        cout << endl;
        cin >> x;
        start += to_string(x) + " ";
        maska = maska >> x;     // Сдвиг единицы маски на x разрядов вправо
        arr = arr | maska;      // Установка нужного разряда в единицу
        maska = (1 << (n - 1)); // Сброс маски
    }
    cout << "Начальный набор чисел: " << start << endl;
    cout << "Отсортированный набор чисел: ";
    for (int i = 1; i <= n; i++) // Вывод отсортированного набора чисел
    {
        if (((arr & maska) >> (n - i)) == 1) // Проверка на нахождение единицы очередного индекса массива
        {
            cout << i - 1 << " ";
        }
        maska = maska >> 1;
    }

    return 0;
}