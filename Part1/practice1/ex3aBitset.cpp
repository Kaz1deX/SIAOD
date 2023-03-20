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
    ifstream fin;
    ofstream fout;
    // auto start = chrono::high_resolution_clock::now();
    bitset<8388607> arr;
    int x;
    fin.open("10MillionNumbers.txt");
    while (fin >> x)
    {
        arr.set(x, true);
    }
    fin.close();
    fout.open("10MillionNumbersEND.txt");
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i])
        {
            fout << i << " ";
        }
    }
    fout.close();
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<float> duration = end - start;
    // cout << duration.count() << "с" << endl;
    // cout << sizeof(unsigned char) * 8 * 1250000 << " бит"; // Размер типа данных * кол-во бит в байте * кол-во битовых массивов в массиве arr

    return 0;
}