#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

string Get_word(string str, int number) {
	vector<string> words;
	string divided = " ";
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(divided, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) words.push_back(token);
		prev = pos + divided.length();
	} while (pos < str.length() && prev < str.length());
	if (number <= words.size()) return words[number - 1];
	else return "";
};

void MergeSort(string name_A, string name_B, string name_C) {
	long long operation_moving = 0, operation_comparison = 0;
	int step = 1;

	//Фаза первого разбиения
	ifstream Faza_divided_A(name_A);
	ofstream Faza_divided_B(name_B), Faza_divided_C(name_C);

	string read_string;
	getline(Faza_divided_A, read_string);
	while (!Faza_divided_A.eof()) {
		for (int i = 0; !Faza_divided_A.eof() && i < step; i++) {
			Faza_divided_B << read_string << endl;
			getline(Faza_divided_A, read_string);
		};
		for (int i = 0; !Faza_divided_A.eof() && i < step; i++) {
			Faza_divided_C << read_string << endl;
			getline(Faza_divided_A, read_string);
		};
	}
	Faza_divided_A.close();
	Faza_divided_B.close();
	Faza_divided_C.close();
	
	while (step < 8) {

		//Фаза слияния
		ofstream Faza_merge_A(name_A);

		ifstream Faza_merge_B(name_B), Faza_merge_C(name_C);

		string first_string, second_string;
		getline(Faza_merge_B, first_string);
		getline(Faza_merge_C, second_string);
		while (!Faza_merge_B.eof() && !Faza_merge_C.eof()) {
			int i = 0, j = 0;
			while ((!Faza_merge_B.eof() && !Faza_merge_C.eof()) && (i < step && j < step)) {
				if (Get_word(first_string, 4) < Get_word(second_string, 4)) {
					Faza_merge_A << first_string << endl;
					getline(Faza_merge_B, first_string);
					operation_moving++;
					i++;
				}
				else {
					Faza_merge_A << second_string << endl;
					getline(Faza_merge_C, second_string);
					operation_moving++;
					j++;
				};
				operation_comparison++;
			};
			while (!Faza_merge_B.eof() && (i < step)) {
				Faza_merge_A << first_string << endl;
				getline(Faza_merge_B, first_string);
				operation_moving++;
				i++;
			};
			while (!Faza_merge_C.eof() && (j < step)) {
				Faza_merge_A << second_string << endl;
				getline(Faza_merge_C, second_string);
				operation_moving++;
				j++;
			};
		};
		while (!Faza_merge_B.eof()) {
			Faza_merge_A << first_string << endl;
			getline(Faza_merge_B, first_string);
			operation_moving++;
		};
		while (!Faza_merge_C.eof()) {
			Faza_merge_A << second_string << endl;
			getline(Faza_merge_C, second_string);
			operation_moving++;
		};
		Faza_merge_A.close();
		Faza_merge_B.close();
		Faza_merge_C.close();

		step *= 2;

		//Фаза последующего разбиения
		ifstream Faza_divided_A(name_A);
		ofstream Faza_divided_B(name_B), Faza_divided_C(name_C);

		string read_string;
		getline(Faza_divided_A, read_string);
		while (!Faza_divided_A.eof()) {
			for (int i = 0; !Faza_divided_A.eof() && i < step; i++) {
				Faza_divided_B << read_string << endl;
				getline(Faza_divided_A, read_string);
			}
			for (int i = 0; !Faza_divided_A.eof() && i < step; i++) {
				Faza_divided_C << read_string << endl;
				getline(Faza_divided_A, read_string);
			}
		}
		Faza_divided_A.close();
		Faza_divided_B.close();
		Faza_divided_C.close();
	};
	cout << "\nC = " << operation_comparison << " M = " << operation_moving;
};

static long long operation_moving = 0, operation_comparison = 0;
void Merge_Sort(string name_A, string name_B, string name_C) {
	while (true) {
		//Фаза разбиения
		ifstream Faza_divided_A(name_A);
		ofstream Faza_divided_B(name_B), Faza_divided_C(name_C);

		string first_string, second_string;
		getline(Faza_divided_A, first_string);
		while (!Faza_divided_A.eof()) {
			if (!Faza_divided_A.eof()) {
				Faza_divided_B << first_string << endl;
				getline(Faza_divided_A, second_string);
				while (!Faza_divided_A.eof() && (Get_word(first_string, 4) <= Get_word(second_string, 4))) {
					first_string = second_string;
					Faza_divided_B << first_string << endl;
					getline(Faza_divided_A, second_string);
				};
			};
			first_string = second_string;
			if (!Faza_divided_A.eof()) {
				Faza_divided_C << first_string << endl;
				getline(Faza_divided_A, second_string);
				while (!Faza_divided_A.eof() && (Get_word(first_string, 4) <= Get_word(second_string, 4))) {
					first_string = second_string;
					Faza_divided_C << first_string << endl;
					getline(Faza_divided_A, second_string);
				};
			};
			first_string = second_string;
		};
		Faza_divided_A.close();
		Faza_divided_B.close();
		Faza_divided_C.close();

		//Фаза пароверки на пустоту файла С
		ifstream Faza_chek_C(name_C);
		char chek;
		Faza_chek_C >> chek;
		if (Faza_chek_C.eof() == 1) {
			Faza_chek_C.close();
			break;
		};
		Faza_chek_C.close();

		//Фаза слияния
		ofstream Faza_merge_A(name_A);
		ifstream Faza_merge_B(name_B), Faza_merge_C(name_C);

		string first_string_B, second_string_B, first_string_C, second_string_C;
		getline(Faza_merge_B, first_string_B);
		getline(Faza_merge_C, first_string_C);
		while (!Faza_merge_B.eof() && !Faza_merge_C.eof()) {
			if (Get_word(first_string_B, 4) < Get_word(first_string_C, 4)) {
				Faza_merge_A << first_string_B << endl;
				getline(Faza_merge_B, second_string_B);
				if (!Faza_merge_B.eof() && (Get_word(first_string_B, 4) > Get_word(second_string_B, 4))) {
					Faza_merge_A << first_string_C << endl;
					getline(Faza_merge_C, second_string_C);
					while (!Faza_merge_C.eof() && (Get_word(first_string_C, 4) <= Get_word(second_string_C, 4))) {
						first_string_C = second_string_C;
						Faza_merge_A << first_string_C << endl;
						getline(Faza_merge_C, second_string_C);
					};
					first_string_C = second_string_C;
				};
				first_string_B = second_string_B;
			}
			else {
				Faza_merge_A << first_string_C << endl;
				getline(Faza_merge_C, second_string_C);
				if (!Faza_merge_C.eof() && (Get_word(first_string_C, 4) > Get_word(second_string_C, 4))) {
					Faza_merge_A << first_string_B << endl;
					getline(Faza_merge_B, second_string_B);
					while (!Faza_merge_B.eof() && (Get_word(first_string_B, 4) <= Get_word(second_string_B, 4))) {
						first_string_B = second_string_B;
						Faza_merge_A << first_string_B << endl;
						getline(Faza_merge_B, second_string_B);
					};
					first_string_B = second_string_B;
				};
				first_string_C = second_string_C;
			};
		};
		while (!Faza_merge_B.eof()) {
			Faza_merge_A << first_string_B << endl;
			getline(Faza_merge_B, first_string_B);
		};
		while (!Faza_merge_C.eof()) {
			Faza_merge_A << first_string_C << endl;
			getline(Faza_merge_C, first_string_C);
		};
		Faza_merge_A.close();
		Faza_merge_B.close();
		Faza_merge_C.close();
	};
};

void MergeSortN(string name_A, string name_B, string name_C) {
	while (true) {
		//Фаза разбиения
		ifstream Faza_divided_A(name_A);
		ofstream Faza_divided_B(name_B), Faza_divided_C(name_C);

		string first_string, second_string;
		Faza_divided_A >> first_string;
		while (!Faza_divided_A.eof()) {
			if (!Faza_divided_A.eof()) {
				Faza_divided_B << first_string << ' ';
				Faza_divided_A >> second_string;
				while (!Faza_divided_A.eof() && (stoi(first_string) <= stoi(second_string))) {
					first_string = second_string;
					Faza_divided_B << first_string << ' ';
					Faza_divided_A >> second_string;
				};
			};
			first_string = second_string;
			if (!Faza_divided_A.eof()) {
				Faza_divided_C << first_string << ' ';
				Faza_divided_A >> second_string;
				while (!Faza_divided_A.eof() && (stoi(first_string) <= stoi(second_string))) {
					first_string = second_string;
					Faza_divided_C << first_string << ' ';
					Faza_divided_A >> second_string;
				};
			};
			first_string = second_string;
		};
		Faza_divided_A.close();
		Faza_divided_B.close();
		Faza_divided_C.close();

		//Фаза пароверки на пустоту файла С
		ifstream Faza_chek_C(name_C);
		char chek;
		Faza_chek_C >> chek;
		if (Faza_chek_C.eof() == 1) {
			Faza_chek_C.close();
			break;
		};
		Faza_chek_C.close();

		//Фаза слияния
		ofstream Faza_merge_A(name_A);
		ifstream Faza_merge_B(name_B), Faza_merge_C(name_C);

		string first_string_B, second_string_B, first_string_C, second_string_C;
		Faza_merge_B >> first_string_B;
		Faza_merge_C >> first_string_C;
		while (!Faza_merge_B.eof() && !Faza_merge_C.eof()) {
			if (stoi(first_string_B) < stoi(first_string_C)) {
				Faza_merge_A << first_string_B << ' ';
				Faza_merge_B >> second_string;
				if (!Faza_merge_B.eof() && (stoi(first_string_B) > stoi(second_string))) {
					Faza_merge_A << first_string_C << ' ';
					Faza_merge_C >> second_string_C;
					while (!Faza_merge_C.eof() && (stoi(first_string_C) <= stoi(second_string_C))) {
						first_string_C = second_string_C;
						Faza_merge_A << first_string_C << ' ';
						Faza_merge_C >> second_string_C;
					};
					first_string_C = second_string_C;
				};
				first_string_B = second_string;
			}
			else {
				Faza_merge_A << first_string_C << ' ';
				Faza_merge_C >> second_string_C;
				if (!Faza_merge_C.eof() && (stoi(first_string_C) > stoi(second_string_C))) {
					Faza_merge_A << first_string_B << ' ';
					Faza_merge_B >> second_string;
					while (!Faza_merge_B.eof() && (stoi(first_string_B) <= stoi(second_string))) {
						first_string_B = second_string;
						Faza_merge_A << first_string_B << ' ';
						Faza_merge_B >> second_string;
					};
					first_string_B = second_string;
				};
				first_string_C = second_string_C;
			};
		};
		while (!Faza_merge_B.eof()) {
			Faza_merge_A << first_string_B << ' ';
			Faza_merge_B >> first_string_B;
		};
		while (!Faza_merge_C.eof()) {
			Faza_merge_A << first_string_C << ' ';
			Faza_merge_C >> first_string_C;
		};
		Faza_merge_A.close();
		Faza_merge_B.close();
		Faza_merge_C.close();
	};
};

int main() {
	setlocale(LC_ALL, "rus");
	time_t begin = clock();
	Merge_Sort("A.txt", "B.txt", "C.txt");
	time_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	cout << "\nC = " << operation_comparison << " M = " << operation_moving;
	cout << "\nT = " << time_spent;
	return(0);
};