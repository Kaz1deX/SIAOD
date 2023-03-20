#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int Palindrom(string word, int count)
{
	if (word.size() == 0)
	{
		//cout << "Глубина рекурсии - " << count << '\n';
		return 1;
	}
	if (tolower(word[0]) == tolower(word[word.size() - 1]))
	{
		count++;
		return Palindrom(word.substr(1, word.size() - 2), count);
	}
	return 0;
}

struct List
{
private:
	struct Node
	{
	public:
		Node* next;
		int val;
		Node(int val, Node* next = nullptr)
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
	void push_back(int val)
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
	void remove(int val)
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
			cout << p->val << endl;
			p = p->next;
		}
		cout << endl;
	}
	void DeleteAllNodesGivenValue(int value, Node* temp)
	{
		if (temp)
		{
			if (temp->val == value)
			{
				temp = temp->next;
				remove(value);
				return DeleteAllNodesGivenValue(value, temp);
			}
			temp = temp->next;
			return DeleteAllNodesGivenValue(value, temp);
		}
		return;
	}
	Node* FirstElement()
	{
		return first;
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
	SetConsoleCP(1251);
	string word;
	cin >> word;
	int count = 1;
	if (Palindrom(word, count))
	{
		cout << "Да, слово '" << word << "' является палиндромом" << '\n';
	}
	else
	{
		cout << "Нет, слово '" << word << "' не является палиндромом" << '\n';
	}
	vector<int> numbers = { 55, 324, 1, 55, -547733, 101, 55, 55 };
	int value;
	List L;
	for (int i = 0; i < 8; i++)
	{
		L.push_back(numbers[i]);
	}
	cin >> value;
	cout << "Начальный список:" << '\n';
	L.print();
	L.DeleteAllNodesGivenValue(value, L.FirstElement());
	cout << "Список после удаления элементов, равных заданному значению:" << '\n';
	L.print();
	return 0;
}