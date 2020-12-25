#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ifstream fin("input.in");

std::vector < std::pair < char, int > > V;
std::vector < bool > F;

void read() {
	std::string line;
	while (std::getline(fin, line)) {
		char c = line[0];
		line.erase(0, line.find(" ") + 1);
		V.push_back({ c, std::stoi(line, size_t()) });
	}
	F = std::vector< bool >(V.size(), false);
}

int solve(int i) {
	int acc = 0;
	while (!F[i]) {
		F[i] = true;
		switch (V[i].first) {
			case 'n': {
				i ++;
				break;
			}
			case 'a': {
				acc += V[i].second;
				i ++;
				break;
			}
			case 'j': {
				i += V[i].second;
				break;
			}
		}
	}
	return acc;
}

int main() {
	read();
	std::cout << solve(0) << '\n';
	return 0;
}
