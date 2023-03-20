#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25;                                         // Произвольное число, которое нужно вывести на экран в 2 СС с 32 разрядами
    const int n = sizeof(int) * 8;                               // = 32 - количество разрядов в числе типа int
    unsigned int maska = (1 << (n - 1));                         // Маска с помощью которой будет происходить вычисления
    cout << "Начальный вид маски: " << bitset<n>(maska) << endl; // Вывод на экран начального числа
    cout << "Результат: ";                                       // Вывод на экран результата
    for (int i = 1; i <= n; i++)                                 // 32 раза - по количеству разрядов
    {
        cout << ((x & maska) >> (n - i)); // Логическое умножение x на маску и сдвиг полученного значения на определенное количество бит
        maska = maska >> 1;               // Смещение 1 в маске на разряд вправо
    }
    cout << endl;

    return 0;
}