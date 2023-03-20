#include <iostream>
#include <ctime>
using namespace std;

void delFirstMetod(int* x, int& n, int key)
{
	int i = 0, moving = 0, sravn = 0;
	while (i < n)
	{
		sravn += 1;
		if (x[i] == key)
		{
			for (int j = i; j < (n - 1); j++)
			{
				sravn += 1;
				x[j] = x[j + 1];
				moving += 1;
			}
			n = n - 1;
		}
		else
		{
			i = i + 1;
		}
	}
	cout << "sravn = " << sravn << '\n' << "moving = " << moving << '\n' << '\n';
}

void Random(int* x, int n)
{
	/*for (int i = 0; i < n; i++)
	{
		x[i] = rand() % 10;
	}*/
	int a;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		x[i] = a;
	}
}

void Print(int* x, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << x[i] << ' ';
	}
}

int main()
{
	srand(time(NULL));
	int n, key, a;
	cin >> n;
	int* x = new int[n];
	Random(x, n);
	cin >> key;
	cout << "\n";
	Print(x, n);
	cout << "\n" << '\n';
	delFirstMetod(x, n, key);
	Print(x, n);
	cout << "\n" << '\n';
	delete[] x;
	return 0;
}