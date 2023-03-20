#include <iostream>
#include <windows.h>
#include <string>
#include <set>
using namespace std;

void deleteWords(string& text) // Удаление повторяющихся слов в тексте
{
    set<string> words;
    string str = "";
    int before; // Размер сета до
    int after;  // Размер сета после
    int k = 0;  // Индекс начала слова
    int i = 0;
    int s = text.size();
    while(i < s)                                      // Перебор символов данной строки
    {
        if ((text[i] != ' ') and (i < text.size()-1)) // Условие для отделения слова
        {
            str += text[i];
            i++;
        }
        else
        {
            if (i == text.size()-1)                        // Условие если слово в конце
            {
                str += text[i];
            }
            before = words.size();
            words.insert(str);                          // Попытка добавить слово в сет
            after = words.size();
            if (before == after)                          // Проверка добавления слова в сет
            {
                if (i == text.size()-1)                   // Условие если слово в конце
                {
                    text.erase(k-1,str.size()+1); // Удаление повторяющегося слова из текста
                }
                else
                {
                    text.erase(k,str.size()+1);   // Удаление повторяющегося слова из текста
                    i -= str.size()+1;                   // Смещение прохода из-за удаления слова
                    s = text.size();                     // Смена размера текста из-за удаления слова
                }
            }
            str = "";
            k = i + 1;
            i++;
        }
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    string text = "school cat house dog mouse red green apple developer grey laptop desktop day";
    cout << "Исходный текст: \n";
    cout << text << '\n';  // Текст до удаления повторяющихся слов
    cout << "\nТекст после удаления нужного слова: \n";
    deleteWords(text); // Вызов функции удаления повторяющихся слов в тексте
    cout << text;         // Текст после удаления повторяющихся слов
    return 0;
}