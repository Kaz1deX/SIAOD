#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
using namespace std;

struct Information              // Информация о человеке
{
public:
    long long int phone_number; // Номер телефона
    string human_adress;        // Адрес проживания
    bool flag;                  // Флаг для коллизий
    Information(bool flag)
    {
        this->flag = flag;
        this->phone_number = 0;
        this->human_adress = "";
    }
    Information(long long int phone_number, string human_adress)
    {
        this->phone_number = phone_number;
        this->human_adress = human_adress;
        this->flag = 0;
    }
};
class Table
{
private:
    int size_hash_table;            // Количество возможных записей
    int fill_hash_table;            // Количество существующих записей
    vector<Information*> hashTable; // Хеш-таблица
public:
    Table()
    {
        this->hashTable.resize(10, nullptr); // Создание пустой таблицы
        this->size_hash_table = 10;                     // Количество возможных записей
        this->fill_hash_table = 5;                      // Количество существующих записей
        hashTable[HashFunc(9998887766, 0)] = new struct Information(9998887766, "Puskina street, 1");
        hashTable[HashFunc(9998887755, 0)] = new struct Information(9998887755, "Nikolskaya street, 2");
        hashTable[HashFunc(9998887744, 0)] = new struct Information(9998887744, "Vavilov street, 3");
        hashTable[HashFunc(9998887733, 0)] = new struct Information(9998887733, "Volnaya street, 4");
        hashTable[HashFunc(9998887722, 0)] = new struct Information(9998887722, "Veshnyakovskaya street, 5");
    }
    int HashFunc(long long int phone_number, int i) // Хеш-функция
    {
        int key = phone_number % size_hash_table + i * (1 + (phone_number % (size_hash_table - 2)));
        return key;
    }
    bool Add(Information* temp)                     // Вставка данных
    {
        long long int phone_number = temp->phone_number;
        int key;
        for (int i = 0; i < size_hash_table; i++) // Поиск места для записи
        {
            key = phone_number % size_hash_table + i * (1 + (phone_number % (size_hash_table - 2))); // Вычисление индекса через хеш-функцию
            if (key >= size_hash_table) // Индекс выходит за рамки таблицы
            {
                reHash();
            }
            if (hashTable[key] == nullptr)                                      // Проверка на то, чтобы ячейка таблицы была свободна
            {
                hashTable[key] = temp;
                fill_hash_table++;
                if (((double)fill_hash_table / (double)size_hash_table) > 0.75) // Проверка на заполненность более 75 процентов
                {
                    reHash();                                                   // Если больше 75 процентов, то нужно рехешировать
                }
                return 1;
            }
            else if (hashTable[key]->phone_number == 0)
            {
                hashTable[key]->phone_number = temp->phone_number;
                hashTable[key]->human_adress = temp->human_adress;
                fill_hash_table++;
                if (((double)fill_hash_table / (double)size_hash_table) > 0.75) // Проверка на заполненность более 75 процентов
                {
                    reHash();                                           // Если больше 75 процентов, то нужно рехешировать
                }
                return 1;
            }
            else                                                        // Если ячейка занята
            {
                if (hashTable[key]->phone_number == temp->phone_number) // Проверка на повторяющиеся данные в ячейке
                {
                    return 0;
                }
                else
                {
                    hashTable[key]->flag = 1; // Поставить флаг 1, так как образовалась коллизия
                }
            }
        }
        return 0;
    }
    bool Delete(long long int phone_number) // Удаление
    {
        int key;
        int key2;
        for (int i = 0; i < size_hash_table; i++)
        {
            key = phone_number % size_hash_table + i * (1 + (phone_number % (size_hash_table - 2))); // Вычисление индекса через хеш-функцию
            if (hashTable[key] == nullptr) // Проверка на пустоту ячейки
            {
                return 0;
            }
            else if (hashTable[key]->phone_number == 0)
            {
                if (hashTable[key]->flag == 0) // Если ячейка пустая и флаг 0, значит не было коллизии и дальше можно не искать
                {
                    return 0;
                }
            }
            else                                                  // В ячейке что-то есть
            {
                if (hashTable[key]->phone_number == phone_number) // Если в ячейке искомые данные
                {
                    if (hashTable[key]->flag == 0)                // Если в этой ячейке не было коллизий
                    {
                        key2 = phone_number % size_hash_table + (i-1) * (1 + (phone_number % (size_hash_table - 2))); // Вычисление индекса через хеш-функцию
                        if (i>0)                                  // Попали ли мы сюда из-за коллизии
                        {
                            hashTable[key2]->flag = 0;                   // В этой ячейке больше нет коллизии
                        }
                        delete hashTable[key];                           // Удаление данных
                        hashTable[key] = new struct Information(0); // Вернуть флаг
                        fill_hash_table--;
                        return 1;
                    }
                    else
                    {
                        delete hashTable[key];                           // Удалить данные
                        hashTable[key] = new struct Information(1); // Вернуть флаг
                        fill_hash_table--;
                        return 1;
                    }
                }
                else
                {
                    if (hashTable[key]->flag == 0) // Если флаг 0, значит не было коллизии и дальше можно не искать
                    {
                        return 0;
                    }
                }
            }
        }
        return 0;                                                 // Таких данных нет
    }
    int Find(long long int phone_number) // Поиск по ключу
    {
        int key;
        for (int i = 0; i < size_hash_table; i++)
        {
            key = phone_number % size_hash_table + i * (1 + (phone_number % (size_hash_table - 2))); // Вычисление индекса через хеш-функцию
            if (hashTable[key] == nullptr)     // Проверка на пустоту ячейки
            {
                return -1;
            }
            else if (hashTable[key]->phone_number == 0)
            {
                if (hashTable[key]->flag == 0) // Если ячейка пустая и флаг 0, значит не было коллизии и дальше можно не искать
                {
                    return -1;
                }
            }
            else if (hashTable[key]->phone_number == phone_number) // Если в ячейке искомые данные
            {
                return key;
            }
            else
            {
                if (hashTable[key]->flag == 0) // Если флаг 0, значит не было коллизии и дальше можно не искать
                {
                    return -1;
                }
            }
        }
        return -1;                                                 // Таких данных нет
    }
    void OutPutAll() // Вывод всех данных
    {
        for (int i = 0; i < size_hash_table; i++) // Перебор всех ячеек хеш-таблицы
        {
            if ((hashTable[i] != nullptr) and (hashTable[i]->phone_number != 0)) // Проверка на пустоту ячейки
            {                                                // Если ячейка не пустая, то вывести данные из этой ячейки
                cout << "\nНомер телефона: " << hashTable[i]->phone_number << " Адрес: " << hashTable[i]->human_adress;
            }
        }
    }
    void OutPut(long long int phone_number) // Вывод конкретных данных
    {
        int key = Find(phone_number);
        if (key != -1) // Проверка на существование ячейки
        {              // Если данные существуют, то вывести их из этой ячейки
            cout << "\nНомер телефона: " << hashTable[key]->phone_number << " Адрес: " << hashTable[key]->human_adress;
        }
        else           // Если не существует, то вывести информацию об этом
        {
            cout << "\nТаких данных нет";
        }
    }
    void reHash() // Рехеширование
    {
        vector<Information*> temp; // Временный вектор, для записи существующих данных
        for (int i = 0; i < size_hash_table; i++) // Запись данных во временный вектор
        {
            if (hashTable[i] != nullptr) // Если ячейка не пустая, то записать данные из неё во временный вектор
            {
                temp.push_back(hashTable[i]);
            }
        }
        hashTable.clear(); // Очищение таблицы
        hashTable.resize(size_hash_table * 5, nullptr); // Увеличение размера таблицы
        size_hash_table = size_hash_table * 5;
        for (int i = 0; i < temp.size(); i++)                      // Возвращение старых данных в увеличенную таблицу
        {
            Add(temp[i]); // При возвращении все данные снова проходят через хеш-функцию
        }
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Table table; // Создание таблицы
    bool flag = true;
    while (flag) // Цикл для выбора пользователем операций над таблицей
    {
        cout << "\n\nЧто вы хотите сделать? (введите цифру нужного пункта от 0 до 4)";
        cout << "\n1. Вставить новые данные о человеке";
        cout << "\n2. Удалить данные о человеке";
        cout << "\n3. Посмотреть данные о человеке";
        cout << "\n4. Посмотреть все существующие данные";
        cout << "\n0. Закончить действия\n";
        int number;
        cin >> number;
        if (number == 1)
        {
            long long int phone_number;
            string human_adress;
            cout << "\nВведите номер телефона (10 значений): ";
            cin >> phone_number;
            cin.ignore();
            cout << "\nВведите адрес проживания (улица, дом): ";
            getline(cin, human_adress);
            Information* temp = new Information(phone_number, human_adress); // Создание структуры данных
            if (table.Add(temp)) // Добавление полученных данных в таблицу, если это возможно
            {
                cout << "\nДанные добавлены"; // Вывод информации об успехе выполнения операции
            }
            else
            {
                cout << "\nТакие данные уже есть";
            }
        }
        if (number == 2)
        {
            long long int phone_number;
            cout << "\nВведите номер телефона, информацию о котором хотите удалить: ";
            cin >> phone_number;
            if (table.Delete(phone_number)) // Удаление данных по полученному ключу из таблицы, если это возможно
            {
                cout << "\nДанные удалены"; // Вывод информации об успехе выполнения операции
            }
            else
            {
                cout << "\nТаких данных не было"; // Вывод информации о провале выполнения операции
            }
        }
        else if (number == 3)
        {
            long long int phone_number;
            cout << "\nВведите номер телефона, информацию о котором хотите узнать: ";
            cin >> phone_number;
            table.OutPut(phone_number); // Вывод на экран данных по полученному номеру телефона
        }
        else if (number == 4)
        {
            table.OutPutAll(); // Вывод на экран всех данных из таблицы
        }
        else if (number == 0)
        {
            flag = false;
        }
    }
    return 0;
}