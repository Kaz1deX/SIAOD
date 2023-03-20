#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <string>
#include <fstream>
#include <thread>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char *arr = new unsigned char[1250000];
    for (int i = 0; i < 1250000; i++) // Заполнение массива нулями
    {
        arr[i] = 0;
    }
    ofstream field("C:\\Users\\Maxim\\CLionProjects\\untitled\\10MillionNumbers.txt");
    for (int i = 9999999; i >= 1000000; i--)
    {
        field << i << " ";
    }
    field.close();

    ifstream fin("C:\\Users\\Maxim\\CLionProjects\\untitled\\10MillionNumbers.txt");
    ofstream fout("C:\\Users\\Maxim\\CLionProjects\\untitled\\10MillionNumbersEND.txt");

    auto start = chrono::high_resolution_clock::now();
    const int n = sizeof(unsigned char) * 8; // Количество разрядов 8
    unsigned char maska = (1 << (n - 1));
    int x;
    for (int i = 1000000; i < 10000000; i++) // Заполнение битовых массивов
    {
        fin >> x;                        // Считывание числа из файла
        maska = maska >> (x % 8);        // Сдвиг единицы маски на x % 8 разрядов вправо
        arr[x / 8] = arr[x / 8] | maska; // Установка нужного разряда в единицу
        maska = (1 << (n - 1));          // Сброс маски
    }
    fin.close();
    for (int i = 0; i < 1250000; i++) // Проход по 8 битным массивам
    {
        for (int j = 1; j <= n; j++) // Проход по битам 8-ми битного массива
        {
            if (((arr[i] & maska) >> (n - j)) == 1) // Проверка на нахождение единицы очередного индекса массива
            {
                fout << ((j - 1) + (n * i)) << " "; // Вывод на экран индексов с учетом пройденных 8-битных массивов
            }
            maska = maska >> 1;
        }
        maska = (1 << (n - 1)); // Сброс маски
    }
    fout.close();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << duration.count() << "c" << endl;
    cout << sizeof(unsigned char) * 8 * 1250000 << "bit"; // Размер типа данных * кол-во бит в байте * кол-во битовых массивов в массиве arr

    delete[] arr;
    return 0;
}