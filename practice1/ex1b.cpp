#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    unsigned char x = 255;                                                   // Произвольное число, 7-й бит которого нужно установить в 1
    unsigned char maska = 1;                                                 // Маска с помощью которой будет происходить установка
    cout << "Начальный x: " << (int)x << endl;                               // Вывод на экран начального числа
    x = x | (maska << 6);                                                    // Сдвиг единицы маски на 6 разряда влево и логическое сложение с x
    cout << "Конечный x после установки 7-ого бита в 1: " << (int)x << endl; // Вывод полученного результата

    return 0;
}