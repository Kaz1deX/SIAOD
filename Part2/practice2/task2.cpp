#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
using namespace std;

void QuickSort(vector<int>& A, int first, int last, int& CF, int& MF)
{
    if (first < last) // условие на то, чтобы начать сортирувку массива, если оно не выполняется,
    {                 // значит массив сортировать не нужно
        CF++; // произошло 1 сравнение
        int left = first; // левая граница массива, который нужно отсортировать
        int right = last; // правая граница массива, который нужно отсортировать
        int middle = A[(left + right) / 2]; // опорный элемент (середина массива)
        do
        {
            CF++; // произошло 1 сравнение
            while (A[left] < middle) // ищем индекс в первой части, элемент которого не меньше опорного элемента
            {
                CF++; // произошло 1 сравнение
                left++; // текущий элемент меньше опорного, значит надо брать следующий элемент первой части
            }
            while (A[right] > middle) // ищем индекс во второй части, элемент которого не больше опорного элемента
            {
                CF++; // произошло 1 сравнение
                right--; // текущий элемент больше опорного, значит надо брать предыдущий элемент второй части
            }
            if (left <= right) // были найдены два индекса элементов из двух частей, сделать проверку на то,
            {                  // чтобы индексы из двух частей не вышли за рамки своих частей
                CF++; // произошло 1 сравнение
                swap(A[left], A[right]); // поменять местами два элемента из двух частей массива
                MF++; // произошло 1 перемещение
                left++; // увеличить левую границу массива
                right--; // уменьшить правую границу массива
            }
        } while (left < right); // условие на продолжение поиска нужных элементов для их последующего обмена
        QuickSort(A, first, right, CF, MF); // рекурсивный вызов этого же алгоритма, но уже для первой части массива
        QuickSort(A, left, last, CF, MF); // рекурсивный вызов этого же алгоритма, но уже для второй части массива
    }
}

void Random(vector<int>& A, int n)
{
    //int value = 0;
    for (int i = 0; i < n; i++)
    {
        A.push_back((rand() % 10));

        //A.push_back(value);
        //value = value + 1;
    }
}

void Print(vector<int>& A)
{
    for (int i = 0; i < A.size(); i++)
    {
        cout << A[i] << ' ';
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ru");
    int n;
    int CF = 0;
    int MF = 0;
    cin >> n;
    vector<int> A;
    Random(A, n);
    cout << "Количество элементов: " << A.size() << '\n';
    //cout << "Исходный вектор:" << '\n';
    //Print(A);
    //cout << '\n';
    auto start = chrono::high_resolution_clock::now();
    QuickSort(A, 0, n - 1, CF, MF);
    auto ending = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = ending - start;
    //cout << "Отсортированный вектор:" << '\n';
    //Print(A);
    //cout << '\n';
    cout << "CF (количество сравнений) = " << CF << '\n'; // вывод на экран количества операций сравнения
    cout << "MF (количество перемещений) = " << MF << '\n'; // вывод на экран количества операций перемещения
    cout << "Time (время работы алгоритма) = " << duration.count() * 1000 << " ms" << '\n'; // вывод на экран длительность работы алгоритма в миллисекундах
    cout << "CF + MF (сумма операций) = " << CF + MF;
    return 0;
}