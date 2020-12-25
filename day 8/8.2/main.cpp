#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ifstream fin("input.in");

std::vector < std::pair < char, int > > V;

void read() {
	std::string line;
	while (std::getline(fin, line)) {
		char c = line[0];
		line.erase(0, line.find(" ") + 1);
		V.push_back({ c, std::stoi(line, size_t()) });
	}
	
}

int solve(int i) {
	int acc = 0;
	std::vector< bool > F(V.size(), false);
	while (i < V.size() && !F[i]) {
		F[i] = true;
		switch (V[i].first) {
			case 'n': {
				i++;
				break;
			}
			case 'a': {
				acc += V[i].second;
				i++;
				break;
			}
			case 'j': {
				i += V[i].second;
				break;
			}
		}
	}
	if (i >= V.size()) {
		return acc;
	}
	return -1;
}

int change() {
	for (int i = 0; i < V.size(); i ++) {
		if (V[i].first != 'a') {
			char c = V[i].first;
			V[i].first = (c == 'n' ? 'j' : 'n');
			if (solve(0) > 0) {
				return solve(0);
			}
			V[i].first = c;
		}
	}
	return -2;
}

int main() {
	read();
	std::cout << change() << '\n';
	return 0;
}
