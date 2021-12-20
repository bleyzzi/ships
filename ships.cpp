#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main() {
	fstream fin("ships.in");
	fstream fout("ships.out");
	if (!fin) { //проверка на существование файла
		fout << "file not found";
		return 0;
	}
	else if (fin.peek() == EOF) { //проверка на пустоту файла
		fout << "file is empty";
		return 0;
	}
	int num_berths, com, num_prich;
	deque<string> q; 
	fin >> num_berths;
	vector<string> prich(num_berths); //вектор причалов, количество их неиземенно
	string str;
	while (fin.peek() != EOF) {
		fin >> com;
		auto emp_prich = find(prich.begin(), prich.end(), ""); //поиск пустых причалов в векторе
		switch (com) {
		case 1: //прибытие корабля в порт
			fin.ignore();
			getline(fin, str);
			fout << "Ship " << str << " arrived" << "\n";
			if (emp_prich != prich.end()) { //корабль занимает пустой причал, если такой имеется
				*emp_prich = str;
			}
			else {//иначе корабль становится в очередь
				q.push_back(str);
			}
			fout << "\n";
			break;
		case 2: //освобождение причала
			fin.ignore();
			getline(fin, str);
			prich[stoi(str) - 1] = "";
			if (!q.empty()) { //если в очереди есть корабль, то он становится к пустому причалу и удаляется из очереди
				prich[stoi(str) - 1] = q.front();
				q.pop_front();
			}
			fout << "\n";
			break;
		case 3: //информация о очереди
			if (q.empty()) { //пустая очередь
				fout << "Queue now is empty" << "\n";
			}
			else { //если в очереди есть корабли
				fout << "Ships in queue: " << q.size() << "\n";
				for (int i = 0; i < q.size(); i++) {
					fout << q[i] << "\n";
				}
			}
			fout << "\n";
			break;
		case 4: //информация о причалах
			fout << "Harbour" << "\n";
			for (int i = 0; i < num_berths; i++) {
				fout << "Pier " << i + 1 << ":";
				if (prich[i].empty()) { //пустой причал
					fout << "empty" << "\n";
				}
				else { //если есть корабль у причала
					fout << prich[i] << "\n";
				}
			}
			fout << "\n";
			break;
		default: //запросы, которые не соответсвуют условию
			fout << "bad request" << "\n";
			}
			break;
		}
	fin.close();
	fout.close();
}
