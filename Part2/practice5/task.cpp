#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct List
{
private:
	struct Node
	{
	public:
		Node* next;
		double val;
		Node(double val, Node* next = nullptr)
		{
			this->val = val;
			this->next = next;
		}
	};

	int size;
	Node* first;
	Node* last;
public:
	List()
	{
		size = 0;
		first = nullptr;
		last = nullptr;
	}
	void push_front(double val)
	{
		Node* p = new Node(val);
		if (first == nullptr)
		{
			first = p;
			last = p;
			size++;
			return;
		}
		p->next = first;
		first = p;
		size++;
	}
	void push_back(double val)
	{
		Node* p = new Node(val);
		if (first == nullptr)
		{
			first = p;
			last = p;
			size++;
			return;
		}
		last->next = p;
		last = p;
		size++;
	}
	void pop_front()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* temp = first;
		first = first->next;
		delete temp;
		size--;
	}
	void pop_back()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* current = first;
		for (int i = 0; i < size - 2; i++)
		{
			current = current->next;
		}
		current->next = nullptr;
		delete last;
		last = current;
		size--;
	}
	void remove(double val)
	{
		if (first == nullptr)
		{
			return;
		}
		if (first->val == val)
		{
			pop_front();
			return;
		}
		else
		{
			Node* slow = first;
			Node* fast = first->next;
			while ((fast != nullptr) and (fast->val != val))
			{
				fast = fast->next;
				slow = slow->next;
			}
			if (fast != nullptr)
			{
				slow->next = fast->next;
				delete fast;
				size--;
				return;
			}
		}
		if (last->val == val)
		{
			pop_back();
			return;
		}
	}
	void print()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* p = first;
		cout << endl;
		while (p != nullptr)
		{
			cout <<  p->val << endl;
			p = p->next;
		}
		cout << endl;
	}
	void Add2NodesBeforeLast(double val1, double val2)
	{
		if ((first == nullptr) or (size == 1))
		{
			push_front(val2);
			push_front(val1);
			return;
		}
		Node* current = first;
		for (int i = 0; i < size - 2; i++)
		{
			current = current->next;
		}
		current->next = new Node(val1);
		current = current->next;
		current->next = new Node(val2);
		current = current->next;
		current->next = last;
		size += 2;
	}
	void RemoveFirstNegativeValue()
	{
		if (first == nullptr)
		{
			return;
		}
		if (first->val < 0)
		{
			pop_front();
			return;
		}
		Node* current = first->next;
		for (int i = 1; i < size; i++)
		{
			if ((current->val < 0) and (current->next != nullptr))
			{
				remove(current->val);
				return;
			}
			if ((current->val < 0) and (current->next == nullptr))
			{
				pop_back();
				return;
			}
			current = current->next;
		}
	}
	void FindMaxValueAndMoveToLast()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* maxim_value = first;
		Node* current = first->next;
		for (int i = 1; i < size; i++)
		{
			if ((current->val) > (maxim_value->val))
			{
				maxim_value = current;
			}
			current = current->next;
		}
		if (maxim_value == last)
		{
			return;
		}
		push_back(maxim_value->val);
		remove(maxim_value->val);
	}
	~List()
	{
		while (size)
		{
			pop_front();
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	double val1, val2, x, y;
	vector<double> numbers = { 2.43, 12.2, 99.2, 65.14, 19.2 };
	int choice, variant;
	List L;
	while (1)
	{
		cout << "Если хотите создать список вручную, то введите \"1\", иначе введите \"0\"" << endl << endl;
		cin >> choice;
		if (choice == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				L.push_front(numbers[i]);
			}
			cout << endl;
			break;
		}
		else if (choice == 1)
		{
			cout << endl;
			double val;
			cout << "Введите дробное число или введите \"0\", чтобы закончить заполнение списка" << endl;
			cin >> val;
			while (val != 0)
			{
				L.push_front(val);
				cout << "Введите дробное число или введите \"0\", чтобы закончить заполнение списка" << endl;
				cin >> val;
			}
			cout << endl;
			break;
		}
		else
		{
			cout << "Введите корректное значение" << endl;
		}
	}
	while (1)
	{
		cout << "Какую операцию над списком желаете выполнить? Введите \"1\", \"2\", \"3\" и т. д." << endl;
		cout << "1) Вставка нового значения в начало" << endl;
		cout << "2) Удаление узла по значению" << endl;
		cout << "3) Вставка нового значения в конец" << endl;
		cout << "4) Удаление первого значения" << endl;
		cout << "5) Удаление последнего значения" << endl;
		cout << "6) Вывод списка в консоль" << endl;
		cout << "7) Вставка двух новых знаечний перед последним значением" << endl;
		cout << "8) Удаление первого отрицательного значения, если оно присутствует" << endl;
		cout << "9) Поиск максимального значения и перенос его в конец" << endl << endl;

		cin >> variant;
		cout << endl;
		switch (variant)
		{
		case 1:
			cout << "Введите дробное значение, которое хотите добавить в начало списка" << endl << endl;
			cin >> x; // 199.2
			cout << endl;
			L.push_front(x);
			break;
		case 2:
			cout << "Введите дробное значение, которое хотите удалить из списка" << endl << endl;
			cin >> x; // 99.2
			cout << endl;
			L.remove(x);
			break;
		case 3:
			cout << "Введите дробное значение, которое хотите добавить в конец списка" << endl << endl;
			cin >> x; // 199.2
			cout << endl;
			L.push_back(x);
			break;
		case 4:
			L.pop_front();
			cout << "Первый значение удалено из списка" << endl;
			break;
		case 5:
			L.pop_back();
			cout << "Последнее значение удалено из списка" << endl;
			break;
		case 6:
			cout << "Значения списка:" << endl;
			L.print();
			break;
		case 7:
			cout << "Введите 2 дробных значения, которое хотите добавить перед последним значением списка" << endl << endl;
			cout << "Введите первое значение" << endl;
			cin >> x; // 34.21
			cout << endl;
			cout << "Введите второе значение" << endl;
			cin >> y; // 9.6
			cout << endl;
			L.Add2NodesBeforeLast(x, y);
			break;
		case 8:
			L.RemoveFirstNegativeValue();
			cout << "Из списка было удалено первое отрицательное значение, если в списке было отрицательное значение" << endl;
			break;
		case 9:
			L.FindMaxValueAndMoveToLast();
			cout << "Найдено максимальное значение и перенесено в конец списка" << endl;
			break;
		default:
			cout << "Введите корректное значение" << endl;
		}
	}
	return 0;
}