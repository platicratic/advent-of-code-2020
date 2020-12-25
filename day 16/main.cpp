#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

ifstream fin("input.in");

void readInterval(stringstream &ss, vector<bool> &F) {
	int a, b;
	ss >> a;
	ss.get();
	ss >> b;
	for (int i = a; i <= b; i++) {
		F[i] = true;
	}
}

void solve1() {
	string line;
	vector<bool> F(1024, false);
	while (getline(fin, line) && line.size() > 0) {
		stringstream ss(line);
		getline(ss, line, ':');
		readInterval(ss, F);
		getline(ss, line, 'r');
		readInterval(ss, F);
	}
	for (int i = 0; i < 4; i ++) {
		getline(fin, line);
	}
	int sol = 0;
	while (getline(fin, line)) {
		stringstream ss(line);
		int nr;
		while (ss >> nr) {
			if (!F[nr]) {
				sol += nr;
			}
			ss.get();
		}
	}
	cout << sol << '\n';
}

vector<int> createTicket(string line) {
	stringstream ss(line);
	int nr;
	vector<int> V;
	while (ss >> nr) {
		V.push_back(nr);
		ss.get();
	}
	return V;
}

void solve2() {
	string line, key;
	map<string, vector<bool>> M;

	while (getline(fin, line) && line.size() > 0) {
		vector<bool> F(1024, false);
		stringstream ss(line);
		getline(ss, key, ':');
		readInterval(ss, F);
		getline(ss, line, 'r');
		readInterval(ss, F);

		M[key] = F;
	}
	getline(fin, line);
	getline(fin, line);
	vector<int> My = createTicket(line);

	getline(fin, line);
	getline(fin, line);
	vector<vector<int>> Tickets;

	while (getline(fin, line)) {
		stringstream ss(line);
		int nr, ok = 1;
		while (ss >> nr && ok) {
			ok = 0;
			for (auto it : M) {
				if (it.second[nr]) {
					ok = 1;
				}
			}
			ss.get();
		}
		if (ok) Tickets.push_back(createTicket(line));
	}

	vector<string> Order(My.size());
	set<string> All;
	for (auto it : M) All.insert(it.first);

	while (!All.empty()) {
		for (int j = 0; j < My.size(); j ++) {
			set<string> S(All);
			for (int i = 0; i < Tickets.size(); i ++) {
				for (string it : All) {
					if (M[it][Tickets[i][j]] == false) {
						S.erase(it);
					}
				}
			}
			if (S.size() == 1) {
				Order[j] = *S.begin();
				All.erase(*S.begin());
				break;
			}
		}
	}

	long long sol = 1;
	for (int i = 0; i < Order.size(); i ++) {
		cout << i + 1 << ": " << Order[i] << '\n';
 		if (Order[i].find("departure") < Order[i].size()) {
			sol *= My[i];
		}
	}
	cout << sol << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}