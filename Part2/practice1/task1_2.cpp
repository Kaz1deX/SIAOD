#include <iostream>
#include <ctime>
using namespace std;

void delOtherMetod(int *x, int &n, int key)
{
	int j = 0, moving = 0, sravn = 0;
	for (int i = 0; i < n; i++)
	{
		sravn += 1;
		x[j] = x[i];
		moving += 1;
		if (x[i] != key)
		{
			j++;
		}
	}
	n = j;
	cout << "sravn = " << sravn << '\n'
		 << "moving = " << moving << '\n'
		 << '\n';
}

void Random(int *x, int n)
{
	for (int i = 0; i < n; i++)
	{
		x[i] = rand() % 10;
	}
}

void Print(int *x, int n)
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
	int *x = new int[n];
	Random(x, n);
	cin >> key;
	cout << "\n";
	Print(x, n);
	cout << "\n"
		 << "\n";
	delOtherMetod(x, n, key);
	Print(x, n);
	cout << "\n"
		 << "\n";
	delete[] x;
	return 0;
}

// int a;
// for (int i = 0; i < n; i++)
//{
//	cin >> a;
//	x[i] = a;
// }