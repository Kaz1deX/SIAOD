#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

void preFunc(string &obraz, vector<int> &p) // Заполнение префикс-функции
{
    /// O(m), m - длина образа
    p[0] = 0;                               // Первое значение - 0
    int i = 1, j = 0;
    while(i < obraz.size())                 // Перебор символов образа, сравнение префикса и суффикса
    {
        if (obraz[i] == obraz[j])           // Если префикс и суффикс равны
        {
            p[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)                    // Если префикс и суффикс не равны и j стоит в начале
        {
            p[i] = 0;
            i++;
        }
        else                                // // Если префикс и суффикс не равны и j стоит не в начале
        {
            j = p[j-1];
        }
    }
}

int KMP(string &text, string &obraz, vector<int> &p)     // Алгоритм поиска КМП
{
    /// O(n), n - длина текста
    int k = 0;                                           // Индекс, который указывает на символ из текста
    int l = 0;                                           // Индекс, который указывает на символ из образа
    int n = text.size();                                 // Длина текста
    int m = obraz.size();                                // Длина образа
    while(k < n)                                         // Сравнение символов текста с образом
    {
        if (text[k] == obraz[l])                         // Если символ из текста совпал с символом образа
        {
            k++;
            l++;
            if (l == m)                                  // Если текущий индекс совпал с длиной образа, то образ найден
            {
                return k-l;                              // Вернуть индекс первого символа искомого слова в тексте
            }
        }
        else if (l == 0)
        {
            k++;
            if (k == n)                                  // Если текущий индекс совпал с длиной текста, то образ не найден
            {
                return -1;
            }
        }
        else
        {
            l = p[l - 1];                                // Сдвиг индекса образа на некоторое кол-во шагов из префикс-функции
        }
    }
}

void deleteWord(string &text, int index, int obraz_size) // Удаление всех слов, равных образу, из текста
{
    if (index == 0)                                      // Если слово стоит в начале текста
    {
        text.erase(index, obraz_size+1);         // Удалить слово и пробел после него
    }
    else                                                // Если слово стоит не в начале текста
    {
        text.erase(index-1, obraz_size+1);      // Удалить слово и пробел перед ним
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    /// O(n + m) - сложность КМП
    /// O(n * m) - сложность прямого поиска

    string text = "school cat house cat"; // Исходный текст
    string obraz = "cat";                 // Образ
    vector<int> p(obraz.size());       // Префикс-функция

    preFunc(obraz, p);             // Вызов заполнения префикс-функции

    cout << "Исходный текст: \n";
    cout << text << '\n';
    int index = KMP(text, obraz, p);
    if (index == -1)
    {
        cout << "\nОбраз не найден\n";
    }
    while (index != -1)                  // Цикл для удаления всех слов, равных образу
    {
        deleteWord(text, index, obraz.size()); // Вызов функции удаления слова из текста
        if (index+obraz.size() == text.size())             // Если слово стоит в конце текста, то таких слов больше точно не будет
        {
            break;
        }
        index = KMP(text, obraz, p);
    }
    cout << "\nТекст после удаления нужного слова: \n";
    cout << text;
    return 0;
}