#include <iostream>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

void printG(vector<vector<int>> G) // Вывод матрицы с кратчайшими весами путей в консоль
{
    for(auto& i : G)
    {
        for(auto& j : i)
        {
            cout << j << setw(5);
        }
        cout << '\n';
    }
}

void printPath(int i, int j, vector<vector<int>>& minimalPath, vector<vector<int>>& G) // Вывод в консоль кратчайшего пути от одной точки до другой
{
    vector<int> path;
    path.push_back(i);
    while(1)
    {
        if(G[j][i] == 0) // Проверка на существование пути
        {
            cout << "Между этими вершинами нет пути!\n";
            return;
        }
        else if(minimalPath[j][i] != 0) // Проверка на то, есть ли еще вершины между заданными
        {
            i = minimalPath[j][i];
            path.push_back(i);
        }
        else
        {
            path.push_back(j);
            break;
        }
    }
    for (int k = path.size()-1; k > 0; k--) // Вывод вершин кратчайшего пути в консоль
    {
        cout << path[k] + 1 << " -> ";
    }
    cout << path[0] + 1;
}

void Floyd(vector<vector<int>>& G, vector<vector<int>>& minimalPath) // Алгоритм Флойда
{
    int inf = 1000000000;
    size_t k, i, j, w = G.size();
    vector<vector<int>> minP = G; // Матрица с inf
    // Установка inf в вершины, где нет путей
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < w; j++)
        {
            if(minP[i][j] == 0 && i != j)
            {
                minP[i][j] = inf;
            }
        }
    }
    // Нахождение кратчайших путей
    for (k = 0; k < w; k++)
    {
        for (i = 0; i < w; i++)
        {
            for (j = 0; j < w; j++)
            {
                if(minP[i][k] + minP[k][j] < minP[i][j]) // Если в текущую вершину можно попасть менее длинным путем
                {
                    G[i][j] = minP[i][k] + minP[k][j];   // Поменять вес пути до данной вершины на менее большой
                    minP[i][j] = G[i][j];                // Поменять вес пути до данной вершины на менее большой
                    minimalPath[i][j] = k;               // Текущей вершине присвоить вершину, из которой получилось прийти кратчайшим путем
                }
            }
        }
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    bool flag = 1;
    int number, n, m, n1, n2, rebro;

    vector<vector<int>> G // Исходная матрица смежности
    {
            {0, 3, 4, 2, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 6, 0, 0, 0, 0},
            {0, 0, 0, 0, 5, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 6, 0, 12, 0},
            {0, 0, 0, 0, 1, 0, 8, 7, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
            {0, 0, 0, 0, 0, 0, 0, 6, 0, 11},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    while(flag)
    {
        cout << "\nВведите цифру действия, которое хотите совершить: \n";
        cout << "1) - Найти кратчайший путь в данном графе: \n";
        printG(G);
        cout << "2) - Найти кратчайший путь в произвольном графе \n";
        cout << "0) - Закончить работу\n\n";
        cin >> number;
        if(number == 1)
        {
            vector<vector<int>> minimalPath1(10, vector<int>(10, 0));
            int i = 8, j = 9;
            Floyd(G, minimalPath1);
            cout << "\nКратчайший путь из вершины " << j << " в вершину " << i << ":\n";
            printPath(i-1, j-1, minimalPath1, G);
            cout << "\nВес данного пути:\n";
            cout << G[j-1][i-1];
            cout << '\n';
        }
        else if(number == 2)
        {
            cout << "Сколько вершин будет в вашем графе?\n";
            cin >> n;
            cout << "Сколько рёбер будет в вашем графе?\n";
            cin >> m;
            vector<vector<int>> G_new(n, vector<int>(n, 0));
            vector<vector<int>> minimalPath2(n, vector<int>(n, 0));
            for (int i = 0; i < m; i++) // Ввод графа
            {
                cout << "\nНеобходимо будет ввести номера двух вершин, соединённых одним ребром" <<
                        "(сначала вводится вершина из которой выходит ребро, а затем вершина, в которое входит ребро), а" <<
                        "также вес этого ребра\n";
                cout << "Введите номер первой вершины (из которой выходит ребро)\n";
                cin >> n1;
                cout << "Введите номер второй вершины (в которую входит ребро)\n";
                cin >> n2;
                cout << "Введите вес ребра\n";
                cin >> rebro;
                G_new[n1-1][n2-1] = rebro;
            }
            cout << "Ваш граф:\n";
            printG(G_new);
            Floyd(G_new, minimalPath2);
            cout << "\n";
            int flag1 = 1, start, finish;
            while(flag1)
            {
                cout << "Из какой вершины в какую вы хотите узнать кратчайший путь?\n";
                cout << "Введите вершину, из которой будет начинаться путь (Если хотите закончить работу введите: 0)\n";
                cin >> start;
                if(start == 0)
                {
                    break;
                }
                cout << "Введите вершину, в которой будет заканчиваться путь (Если хотите закончить работу введите: 0)\n";
                cin >> finish;
                if(finish == 0)
                {
                    break;
                }
                cout << "\nКратчайший путь из вершины " << start << " в вершину " << finish << ":\n";
                printPath(finish-1, start-1, minimalPath2, G_new);
                cout << "\nВес данного пути:\n";
                cout << G_new[start-1][finish-1];
                cout << '\n';
            }
        }
        else if(number == 0)
        {
            flag = 0;
        }
        else
        {
            cout << "Такой цифры нет. Попробуйте ещё раз\n";
        }
    }
    return 0;
}