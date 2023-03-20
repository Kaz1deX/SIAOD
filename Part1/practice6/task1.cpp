#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Node {
private:
    Node* leftChild;    // левый ребенок
    Node* rightChild;   // правый ребенок
    char symbol;        // сам символ
    int frequency;      // частота вхождения
public:
    Node()
    {
        leftChild = nullptr;
        rightChild = nullptr;
        symbol = 0;
        frequency = 1;
    }
    Node(char _symbol, int _frequency)
    {
        leftChild = nullptr;
        rightChild = nullptr;
        symbol = _symbol;
        frequency = _frequency;
    }
    Node* getLeftChild() const
    {
        return leftChild;
    }
    void setLeftChild(Node* leftChild)
    {
        this->leftChild = leftChild;
    }
    Node* getRightChild() const
    {
        return rightChild;
    }
    void setRightChild(Node* rightChild)
    {
        this->rightChild = rightChild;
    }
    char getSymbol() const
    {
        return symbol;
    }
    void setSymbol(char symbol)
    {
        this->symbol = symbol;
    }
    int getFrequency() const
    {
        return frequency;
    }
    void setFrequency(int frequency)
    {
        this->frequency = frequency;
    }
};

class Coder {
private:
    vector<char>* allSymbols;               // массив уникальных символов в тексте
    vector<int>* allCountOfSymbols;         // массив вхождений уникальных символов в тексте
    vector<string>* allSymbols_encrypted;   // массив зашифрованных уникальных символов в тексте

public:
    Coder()
    {
        allSymbols = new vector<char>();
        allCountOfSymbols = new vector<int>();
        allSymbols_encrypted = new vector<string>(32);
    }

    // Подготовка: подготавливаем таблицу символов и частоту их вхождений
    void preprocessing(string startString)
    {
        /*
         * Этап нулевой (подготовка):
         * - разбиение текста на все символы и подсчет каждого вхождения символа в текст;
         */

        int lenStartString = startString.length();

        // Проходим по всему тексту
        for (int i = 0; i < lenStartString; i++) {
            bool isFounded = false;

            // Проходим по всему массиву уникальных символов
            for (int j = 0; j < allSymbols->size(); j++) {

                // Если данный символ уже присутствует в массиве уникальных символов ->> увеличиваем прошлое значение вхождений на 1
                if (startString[i] == allSymbols->at(j)) {
                    allCountOfSymbols->at(j) = allCountOfSymbols->at(j) + 1;
                    isFounded = true;
                    break;
                }
            }

            if (!isFounded) {
                allSymbols->push_back(startString[i]);
                allCountOfSymbols->push_back(1);
            }

        }

        // Сортируем значения вхождения по невозврастанию ("пузырёк")
        for (int i = 0; i < allCountOfSymbols->size(); i++) {
            for (int j = i + 1; j < allCountOfSymbols->size(); j++) {
                if (allCountOfSymbols->at(j) > allCountOfSymbols->at(i)) {
                    int localInt = allCountOfSymbols->at(j);
                    allCountOfSymbols->at(j) = allCountOfSymbols->at(i);
                    allCountOfSymbols->at(i) = localInt;

                    char localChar = allSymbols->at(j);
                    allSymbols->at(j) = allSymbols->at(i);
                    allSymbols->at(i) = localChar;
                }
            }
        }
    }

    // Шифрование алгоритмом Шеннона-Фано
    string ShannonFano_encrypt(string startString)                 // запуск рекурсии и формирование зашифрованной строки
    {
        ShannonFano_recursion(*allSymbols);

        // Формирование и возвращение полученной зашифрованной строки
        string encryptedString = "";
        for (char ch1 : startString) {
            encryptedString += allSymbols_encrypted->at(getIndexOfChar(ch1));
        }
        return encryptedString;
    }
    void ShannonFano_recursion(vector<char> groupSymbols)          // сам рекурсивный алгоритм Шеннона-Фана
    {
        // если в группе оказалось 1 или меньше элементов ---> выходим
        if (groupSymbols.size() <= 1)
            return;

        // создаем две подгруппы символов
        vector<char> firstGroupSymbols;
        vector<char> secondGroupSymbols;

        // Разделение всех элементов группы на две подгруппы
        for (int i = 0; i < groupSymbols.size(); i++) {
            char lclSymbol = groupSymbols.at(i); // получаем каждый символ текущей группы
            int indexOfLclSymbol = getIndexOfChar(lclSymbol); // получаем у такого символа индекс в массиве уникальных символов

            // если в левой подгруппе сейчас находятся элементы с общей суммой вероятности <= чем в правой ---> добавляем этот символ в первую подгруппу
            if (getSumOfChancesSymbols(&firstGroupSymbols) <= getSumOfChancesSymbols(&secondGroupSymbols)) {

                firstGroupSymbols.push_back(lclSymbol);

                // берём нужный индекс в массиве зашифрованных символов и добавляем к этой строке '0'
                allSymbols_encrypted->at(indexOfLclSymbol) = allSymbols_encrypted->at(indexOfLclSymbol) + "0";
            }
            // иначе ---> в правую
            else {
                secondGroupSymbols.push_back(lclSymbol);

                // берём нужный индекс в массиве зашифрованных символов и добавляем к этой строке '1'
                allSymbols_encrypted->at(indexOfLclSymbol) = allSymbols_encrypted->at(indexOfLclSymbol) + "1";
            }
        }

        // вызываем рекурсию для левой и правой подгруппы символов
        ShannonFano_recursion(firstGroupSymbols);
        ShannonFano_recursion(secondGroupSymbols);
    }
    int getSumOfChancesSymbols(vector<char>* groupSymbols)         // получение суммы "шансов" в определенной группе символов
    {
        int sumChances = 0;
        for (int i = 0; i < groupSymbols->size(); i++) {
            for (int j = 0; j < allSymbols->size(); j++) {
                if (groupSymbols->at(i) == allSymbols->at(j)) {
                    sumChances += allCountOfSymbols->at(j);
                }
            }
        }
        return sumChances;
    }
    int getIndexOfChar(char toFind)                                // получение индекса символа в массиве уникальных символов
    {
        for (int i = 0; i < allSymbols->size(); i++) {
            if (toFind == allSymbols->at(i)) {
                return i;
            }
        }
        return -1;
    }
    char getEncryptedSymbolInSymbols(string encryptedSymbol)       // есть ли такой зашифрованный символ среди наших, если есть - возвращает
    {
        for (int i = 0; i < allSymbols_encrypted->size(); i++) {
            if (encryptedSymbol == allSymbols_encrypted->at(i)) {
                return allSymbols->at(i);
            }
        }
        return -1;
    }
    // Шифрование алгоритмом Хаффмана
    string Haffman_encrypt(string startString)                     // сам алгоритм Хаффмана
    {
        vector<Node*> queueHaffman;
        Node* parentNode;
        Node* root;

        // Формируем очередь из узлов, в приоритете добавления символом с низкой частотой вхождения
        for (int i = allSymbols->size() - 1; i >= 0; i--) {
            queueHaffman.push_back(new Node(allSymbols->at(i), allCountOfSymbols->at(i)));
        }

        // пока в очереди есть 2 и более элементов
        while (queueHaffman.size() > 1) {
            // берём два элемента из начала очереди
            Node* localLeftNode = queueHaffman.front();
            queueHaffman.erase(queueHaffman.begin());
            Node* localRightNode = queueHaffman.front();
            queueHaffman.erase(queueHaffman.begin());

            // создаем новый родительский узел с двумя дочерними узлами из начала очереди
            parentNode = new Node();
            parentNode->setLeftChild(localLeftNode);
            parentNode->setRightChild(localRightNode);

            if (queueHaffman.size() == 0) {
                root = parentNode;
            }

            // складываем частоту появления символов левого и правого дочернего узла и присваиваем эту сумму частоте текущего родителя
            parentNode->setFrequency(localLeftNode->getFrequency() + localRightNode->getFrequency());

            /*
             *          Пример
             *
             *      2       | частота родителя (1 + 1)
             *    1   1     | частоты дочерних узлов
             *
             */

             // теперь необходимо вставить в нужное место в очереди новый созданный узел, соблюдая порядок частот по возрастанию
            for (int i = 0; i < queueHaffman.size(); i++) {
                if (i == queueHaffman.size() - 1) {
                    if (parentNode->getFrequency() <= queueHaffman.at(i)->getFrequency()) {
                        queueHaffman.insert(queueHaffman.begin() + i + 1, parentNode);
                    }
                    else {
                        queueHaffman.push_back(parentNode);
                    }
                    break;
                }
                if (parentNode->getFrequency() > queueHaffman.at(i)->getFrequency()) {
                    if (parentNode->getFrequency() <= queueHaffman.at(i + 1)->getFrequency()) {
                        queueHaffman.insert(queueHaffman.begin() + i + 1, parentNode);
                        break;
                    }
                }
                else {
                    queueHaffman.insert(queueHaffman.begin(), parentNode);
                    break;
                }

            }



        }
        // получаем таблицу зашифрованных символов
        Haffman_recursion(root, "");

        // Формирование и возвращение полученной зашифрованной строки
        string encryptedString = "";
        for (char ch1 : startString) {
            encryptedString += allSymbols_encrypted->at(getIndexOfChar(ch1));
        }
        return encryptedString;
    }
    void Haffman_recursion(Node* currentParent, string localStr)   // получение всех зашифрованных символов (бинарное дерево уже построено)
    {
        if (currentParent->getLeftChild() == nullptr && currentParent->getRightChild() == nullptr) {
            if (currentParent->getSymbol() != 0) {
                int indexOfLclSymbol = getIndexOfChar(currentParent->getSymbol());
                allSymbols_encrypted->at(indexOfLclSymbol) = localStr;
            }
            return;
        }

        Node lclLeftNode = *(currentParent->getLeftChild());
        Node lclRightNode = *(currentParent->getRightChild());

        Haffman_recursion(&lclLeftNode, localStr + "0");
        Haffman_recursion(&lclRightNode, localStr + "1");
    }
    string decrypt(string encryptedString)                         // дешифрование зашифрованной строки
    {
        string result = "";
        string bufferStr = "";
        for (int i = 0; i < encryptedString.length(); i++) {
            bufferStr += encryptedString[i];
            char decryptedSymbol = getEncryptedSymbolInSymbols(bufferStr);
            if (decryptedSymbol != -1) {
                result += decryptedSymbol;
                bufferStr = "";
            }
        }
        return result;
    }
};

void StartShannonFano() {
    string str1, str1_encrypted, str1_decrypted;
    Coder coder1;

    //ifstream text("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text");
    ifstream text("C:\\Users\\Maxim\\Desktop\\6SIAOD\\Text.txt");
    //ofstream text_encrypted("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text_encrypted");
    ofstream text_encrypted("C:\\Users\\Maxim\\Desktop\\6SIAOD\\TextAfter.txt");
    //ofstream text_decrypted("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text_decrypted");
    ofstream text_decrypted("C:\\Users\\Maxim\\Desktop\\6SIAOD\\TextBefore.txt");

    getline(text, str1);
    cout << "ДО    сжатия | " << str1 << endl;

    coder1.preprocessing(str1);

    str1_encrypted = coder1.ShannonFano_encrypt(str1);
    cout << "ПОСЛЕ сжатия | " << str1_encrypted << endl;
    text_encrypted << str1_encrypted;

    cout << endl << "Размер до сжатия    | " << str1.length() * 8 << " бит (" << str1.length() << " символов x 8 бит)";
    cout << endl << "Размер после сжатия | " << str1_encrypted.length() << " бит" << endl;
    cout << "Процент сжатия: " << int(str1_encrypted.length() / (double)(str1.length() * 8) * 100) << "%" << endl;

    cout << endl << "Зашифрованная строка | " << str1_encrypted;
    str1_decrypted = coder1.decrypt(str1_encrypted);
    cout << endl << "Дешифрованная строка | " << str1_decrypted;
    text_decrypted << str1_decrypted;
}

void StartHaffman() {
    string str1, str1_encrypted, str1_decrypted;
    Coder coder1;

    ifstream text("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text");
    ofstream text_encrypted("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text_encrypted");
    ofstream text_decrypted("C:\\Users\\towic\\OneDrive\\3 semak\\SIAOD\\6 encryption\\Code\\Text_decrypted");


    getline(text, str1);
    cout << "ДО    сжатия | " << str1 << endl;

    coder1.preprocessing(str1);

    str1_encrypted = coder1.Haffman_encrypt(str1);
    cout << "ПОСЛЕ сжатия | " << str1_encrypted << endl;
    text_encrypted << str1_encrypted;

    cout << endl << "Размер до сжатия    | " << str1.length() * 8 << " бит (" << str1.length() << " символов x 8 бит)";
    cout << endl << "Размер после сжатия | " << str1_encrypted.length() << " бит" << endl;
    cout << "Процент сжатия: " << int(str1_encrypted.length() / (double)(str1.length() * 8) * 100) << "%" << endl;

    cout << endl << "Зашифрованная строка | " << str1_encrypted;
    str1_decrypted = coder1.decrypt(str1_encrypted);
    cout << endl << "Дешифрованная строка | " << str1_decrypted;
    text_decrypted << str1_decrypted;
}

int main() {
    //cout << "~~~~~~~~~~~~~~~~~~~~~Алгоритм Шеннона-Фано~~~~~~~~~~~~~~~~~~~~~" << endl;
    //StartShannonFano();
    
    cout << "~~~~~~~~~~~~~~~~~~~~~Алгоритм Хаффмана~~~~~~~~~~~~~~~~~~~~~" << endl;
    StartHaffman();

    return 0;
}