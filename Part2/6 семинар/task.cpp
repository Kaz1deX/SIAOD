#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

struct List
{
private:
	struct Node
	{
	public:
		string number_route;
		string departure_time;
		string number_bus;
		string price;
		string departure_data;
		Node* next;
		Node* previous;
		Node(string number_route, string departure_time, string number_bus, string price, string departure_data, Node* next = nullptr, Node* previous = nullptr)
		{
			this->number_route = number_route;
			this->departure_time = departure_time;
			this->number_bus = number_bus;
			this->price = price;
			this->departure_data = departure_data;
			this->next = next;
			this->previous = previous;
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
	void push_front(string number_route, string departure_time, string number_bus, string price, string departure_data)
	{
		Node* p = new Node(number_route, departure_time, number_bus, price, departure_data);
		if (first == nullptr)
		{
			first = p;
			last = p;
			size++;
			return;
		}
		p->next = first;
		first->previous = p;
		first = p;
		size++;
	}
	void push_back(string number_route, string departure_time, string number_bus, string price, string departure_data)
	{
		Node* p = new Node(number_route, departure_time, number_bus, price, departure_data);
		if (first == nullptr)
		{
			first = p;
			last = p;
			size++;
			return;
		}
		last->next = p;
		p->previous = last;
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
		first->previous = nullptr;
		delete temp;
		size--;
	}
	void pop_back()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* temp = last;
		last = last->previous;
		last->next = nullptr;
		delete temp;
		size--;
	}
	void remove(string number_bus)
	{
		if (first == nullptr)
		{
			return;
		}
		if (first->number_bus == number_bus)
		{
			pop_front();
			return;
		}
		else
		{
			Node* slow = first;
			Node* fast = first->next;
			while ((fast != nullptr) and (fast->number_bus != number_bus))
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
		if (last->number_bus == number_bus)
		{
			pop_back();
			return;
		}
	}
	void printR()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* p = first;
		cout << endl;
		while (p != nullptr)
		{
			cout << p->number_route << ' ';
			cout << p->departure_time << ' ';
			cout << p->number_bus << ' ';
			cout << p->price << ' ';
			cout << p->departure_data << '\n';
			p = p->next;
		}
		cout << endl;
	}
	void printL()
	{
		if (first == nullptr)
		{
			return;
		}
		Node* p = last;
		cout << endl;
		while (p != nullptr)
		{
			cout << p->number_route << ' ';
			cout << p->departure_time << ' ';
			cout << p->number_bus << ' ';
			cout << p->price << ' ';
			cout << p->departure_data << '\n';
			p = p->previous;
		}
		cout << endl;
	}
	Node* FindNode(string number_bus)
	{
		Node* temp = first;
		while (temp)
		{
			if (temp->number_bus != number_bus)
			{
				temp = temp->next;
			}
			else
			{
				return temp;
			}
		}
		return temp;
	}
	void AddAfterLastNodeGivenValue(string number_route, string departure_time, string number_bus, string price, string departure_data)
	{
		Node* temp = last;
		if (temp->number_bus == number_bus)
		{
			push_back(number_route, departure_time, number_bus, price, departure_data);
			return;
		}
		while (temp)
		{
			if (temp->number_bus == number_bus)
			{
				Node* p = new Node(number_route, departure_time, number_bus, price, departure_data);
				p->next = temp->next;
				(p->next)->previous = p;
				p->previous = temp;
				temp->next = p;
				return;
			}
			temp = temp->previous;
		}
		push_back(number_route, departure_time, number_bus, price, departure_data);
	}
	void DeleteAllNodesGivenValue(string number_bus)
	{
		Node* temp = first;
		int counter = 0;
		while (temp)
		{
			if (temp->number_bus == number_bus)
			{
				counter++;
			}
			temp = temp->next;
		}
		for (int i = 0; i < counter; i++)
		{
			remove(number_bus);
		}
	}
	void CountRoutesForGivenDay(string number_bus, string number_route, string departure_data)
	{
		Node* temp = first;
		int counter = 0;
		while (temp)
		{
			if ((temp->number_bus == number_bus) and (temp->number_route == number_route) and (temp->departure_data == departure_data))
			{
				counter++;
			}
			temp = temp->next;
		}
		cout << "Автобус с номером " << number_bus << " выходил на маршрут с номером " << number_route << " в течении " << departure_data << " дня: " << counter << " раз(а)" << '\n';
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
	string number_route;
	string departure_time;
	string number_bus;
	string price;
	string departure_data;
	vector<string> bus_1 = { "100", "12:00", "с516гн", "45р", "29.04.22"};
	vector<string> bus_2 = { "101", "12:10", "п231им", "50р", "26.03.22" };
	//vector<string> bus_2 = { "111", "20:10", "п231им", "50р", "12.11.22" };
	//vector<string> bus_3 = { "131", "15:20", "р814дг", "45р", "11.01.22" };
	vector<string> bus_3 = { "102", "12:20", "р854дм", "45р", "09.05.22" };
	//vector<string> bus_4 = { "111", "12:30", "п231им", "50р", "12.11.22" };
	//vector<string> bus_5 = { "111", "16:40", "п231им", "50р", "12.11.22" };
	//vector<string> bus_5 = { "151", "12:05", "р814дг", "45р", "04.06.22" };
	vector<string> bus_4 = { "103", "12:30", "н676аа", "50р", "29.07.22" };
	vector<string> bus_5 = { "104", "12:40", "в115ук", "45р", "12.11.22" };
	//vector<string> bus_8 = { "171", "10:10", "р814дг", "45р", "30.09.22" };

	vector<vector<string>> bus_inf = { bus_1, bus_2, bus_3, bus_4, bus_5 };
	//vector<vector<string>> bus_inf = { bus_1, bus_2, bus_3, bus_4, bus_5, bus_6, bus_7, bus_8 };
	int variant;
	List L;
	for (int i = 0; i < 5; i++)
	{
		L.push_back(bus_inf[i][0], bus_inf[i][1], bus_inf[i][2], bus_inf[i][3], bus_inf[i][4]);
	}
	while (1)
	{
		cout << "\nКакую операцию над списком желаете выполнить? Введите \"1\", \"2\", \"3\" и т. д." << endl;
		cout << "1) Вставка новой информации об автобусе в начало" << endl;
		cout << "2) Вставка новой информации об автобусе в конец" << endl;
		cout << "3) Удаление информации о первом автобусе из списка" << endl;
		cout << "4) Удаление информации о последнем автобусе из списка" << endl;
		cout << "5) Удаление информации о заданном автобусе" << endl;
		cout << "6) Вывод списка в консоль слева направо" << endl;
		cout << "7) Вывод списка в консоль справа налево" << endl;
		cout << "8) Поиск в списке заданного автобуса" << endl;
		cout << "9) Вставка новой информации об автобусе после последнего элемента списка с заданным номером автобуса" << endl;
		cout << "10) Удалить все элементы из списка с заданным номером автобуса" << endl;
		cout << "11) Подсчитать количества раз, когда заданный автобус выходил на заданный маршрут в течении заданного дня" << endl << endl;
		cin >> variant;
		cout << endl;
		switch (variant)
		{
		case 1: // 899 15:10 е633нд 45р 02.10.22
			cout << "Введите номер маршрута, время отправления, номер автобуса, стоимость одной поездки, дату отправления" << '\n';
			cin >> number_route >> departure_time >> number_bus >> price >> departure_data;
			L.push_front(number_route, departure_time, number_bus, price, departure_data);
			break;
		case 2: // 899 15:10 е633нд 45р 02.10.22
			cout << "Введите номер маршрута, время отправления, номер автобуса, стоимость одной поездки, дату отправления" << '\n';
			cin >> number_route >> departure_time >> number_bus >> price >> departure_data;
			L.push_back(number_route, departure_time, number_bus, price, departure_data);
			break;
		case 3:
			L.pop_front();
			cout << "Информация о первом автобусе в списке была удалена" << endl;
			break;
		case 4:
			L.pop_back();
			cout << "Информация о последнем автобусе в списке была удалена" << endl;
			break;
		case 5: // р854дм
			cout << "Введите номер автобуса, информацию о котором хотите удалить" << endl;
			cin >> number_bus;
			L.remove(number_bus);
			cout << "Информация об автобусе с номером " << number_bus << " была удалена" << endl;
			break;
		case 6:
			cout << "Значения списка слева направо:" << endl;
			L.printR();
			break;
		case 7:
			cout << "Значения списка справа налево:" << endl;
			L.printL();
			break;
		case 8: // н676аа
			cout << "Введите номер автобуса, информацию о котором хотите получить" << endl;
			cin >> number_bus;
			cout << "Адрес заданного номера автобуса: " <<L.FindNode(number_bus) << endl;
			break;
		case 9: // 101 09:53 п231им 40р 22.07.22
			cout << "Введите номер маршрута, время отправления, номер автобуса, стоимость одной поездки, дату отправления" << '\n';
			cin >> number_route >> departure_time >> number_bus >> price >> departure_data;
			L.AddAfterLastNodeGivenValue(number_route, departure_time, number_bus, price, departure_data);
			break;
		case 10: // р814дг
			cout << "Введите номер автобуса, всю информацию о котором хотите удалить" << endl;
			cin >> number_bus;
			L.DeleteAllNodesGivenValue(number_bus);
			break;
		case 11: // п231им 111 12.11.22
			cout << "Введите номер автобуса, номер маршрута и дату отправления" << endl;
			cin >> number_bus >> number_route >> departure_data;
			L.CountRoutesForGivenDay(number_bus, number_route, departure_data);
			break;
		default:
			cout << "Введите корректное значение" << endl;
		}
	}
	return 0;
}