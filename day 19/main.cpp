#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

ifstream fin("input.in");

map<int, vector<int>> M1;
map<int, pair<vector<int>, vector<int>>> M2;
map<int, set<string>> All;
vector<bool> F(131, false);
int size8, size11, size42, size31;

bool isOne(vector<int> V) {
	for (int it : V) {
		if (All.find(it) == All.end()) {
			return false;
		}
	}
	return true;
}

pair<bool, int> findOne() {
	for (pair<int, vector<int>> m1 : M1) {
		if (!F[m1.first]) {
			if (isOne(m1.second)) {
				F[m1.first] = true;
				return { false, m1.first };
			}
		}
	}
	for (pair<int, pair<vector<int>, vector<int>>> m2 : M2) {
		if (!F[m2.first]) {
			if (isOne(m2.second.first) && isOne(m2.second.second)) {
				F[m2.first] = true;
				return { true, m2.first };
			}
		}
	}
	return { true, -1 };
}

set<string> back(vector<int> &M) {
	set<string> A, B;
	A.insert("");
	for (int mId : M) {
		for (string addMe : All[mId]) {
			for (string a : A) {
				B.insert(a + addMe);
			}
		}
		A = B;
		B.clear();
	}
	return A;
}

void verif(string line, int nr, bool &alike) {
	if (nr == 8) {
		if (line.size() >= size8 + size11) {
			for (string str : All[8]) {
				if (line.substr(0, str.size()) == str) {
					verif(line.substr(str.size()), 8, alike);
				}
			}
		}
		return verif(line, 11, alike);
	}
	else if (nr == 11) {
		if (line.size() >= size11) {

			for (string str : All[11]) {
				if (line.substr(0, str.size()) == str && line.size() == str.size()) {
					alike = true;
				}
				else if (line.substr(0, size42) == str.substr(0, size42) && line.substr(line.size() - size31, line.size()) == str.substr(size42)) {
					return verif(line.substr(size42, line.size() - 2 * size31), 11, alike);
				}
			}
		}
	}
}

void solve() {
	string line;
	int id, number;

	// read
	while (getline(fin, line) && line.size() > 0) {
		id = stoi(line.substr(0, line.find(':')));
		if (line.find('|') != string::npos) {
			stringstream part1(line.substr(line.find(':') + 2, line.find('|')));
			while (part1 >> number) {
				M2[id].first.push_back(number);
			}
			stringstream part2(line.substr(line.find('|') + 1));
			while (part2 >> number) {
				M2[id].second.push_back(number);
			}
		}
		else if (line.find('\"') != string::npos) {
			All[id].insert(line.substr(line.find('\"') + 1, 1));
			F[id] = true;
		}
		else {
			stringstream part(line.substr(line.find(':') + 2));
			while (part >> number) {
				M1[id].push_back(number);
			}
		}
	}

	cout << "faze 1...\n";

	// solve 1
	while (All.find(0) == All.end()) {
		pair<bool, int> id = findOne();

		if (id.first == false) {
			All[id.second] = back(M1[id.second]);
		}
		else {
			set<string> A = back(M2[id.second].first);
			set<string> B = back(M2[id.second].second);
			for (auto b : B) {
				A.insert(b);
			}
			All[id.second] = A;
		}
	}

	size8 = All[8].begin()->size();
	size11 = All[11].begin()->size();
	size42 = All[42].begin()->size();
	size31 = All[31].begin()->size();

	cout << "faze 2...\n";

	unordered_set<string> S;
	for (auto it : All[0]) {
		S.insert(it);
	}

	cout << "faze 3...\n";

	int sol = 0;
	while (getline(fin, line)) {
		// solve 1
		if (S.find(line) != S.end()) {
			sol ++;
		}
		// solve 2
		else {
			for (string str : All[8]) {
				if (line.substr(0, str.size()) == str) {
					bool alike = false;
					verif(line.substr(str.size()), 8, alike); 
					if (alike) {
						sol ++;
						break;
					}
				}
			}
		}
	}
	cout << sol << '\n';
}

int main() {
	solve();
	return 0;
}