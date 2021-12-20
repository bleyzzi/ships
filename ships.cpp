#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main() {
	fstream fin("ships.in");
	fstream fout("ships.out");
	if (!fin) {
		fout << "file not found";
		return 0;
	}
	else if (fin.peek() == EOF) {
		fout << "file is empty";
		return 0;
	}
	int num_berths, com, num_prich;
	deque<string> q;
	fin >> num_berths;
	vector<string> prich(num_berths);
	vector<string> raid;
	string str;
	while (fin.peek() != EOF) {
		fin >> com;
		auto emp_prich = find(prich.begin(), prich.end(), "");
		switch (com) {
		case 1:
			fin.ignore();
			getline(fin, str);
			fout << "Ship " << str << " arrived" << "\n";
			if (emp_prich != prich.end()) {
				*emp_prich = str;
			}
			else {
				q.push_back(str);
			}
			fout << "\n";
			break;
		case 2:
			fin.ignore();
			getline(fin, str);
			prich[stoi(str) - 1] = "";
			if (!q.empty()) {
				prich[stoi(str) - 1] = q.front();
				q.pop_front();
			}
			fout << "\n";
			break;
		case 3:
			if (q.empty()) {
				fout << "Queue now is empty" << "\n";
			}
			else {
				fout << "Ships in queue: " << q.size() << "\n";
				for (int i = 0; i < q.size(); i++) {
					fout << q[i] << "\n";
				}
			}
			fout << "\n";
			break;
		case 4:
			fout << "Harbour" << "\n";
			for (int i = 0; i < num_berths; i++) {
				fout << "Pier " << i + 1 << ":";
				if (prich[i].empty()) {
					fout << "empty" << "\n";
				}
				else {
					fout << prich[i] << "\n";
				}
			}
			fout << "\n";
			break;
		default:
			fout << "bad request" << "\n";
			}
			break;
		}
	fin.close();
	fout.close();
}
