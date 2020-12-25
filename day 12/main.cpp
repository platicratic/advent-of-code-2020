#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::ifstream fin("input.in");

void solve1() {
	std::string line;
	int P[4] = { 0, 0, 0, 0 };
	int current = 3;
	std::map<char, int> M; M['N'] = 0; M['W'] = 1; M['S'] = 2; M['E'] = 3;

	while (std::getline(fin, line)) {
		int nr = std::stoi(line.substr(1), std::size_t());
		switch (line[0]) {
			case 'F': {
				P[current] += nr;
				break;
			}
			case 'L' : {
				current = (current + (nr / 90)) % 4;
				break;
			}
			case 'R': {
				current = (current - (nr / 90) + 4) % 4;
				break;
			}
			default: {
				P[M[line[0]]] += nr;
			}
		}
	}
	std::cout << abs(P[0] - P[2]) + abs(P[1] - P[3]) << '\n';
}

void solve2() {
	std::string line;
	int P[4] = { 0, 0, 0, 0 };
	std::pair<int, int> waypoint[2] = { { 0, 1 }, { 3, 10 } };
	std::map<char, int> M; M['N'] = 0; M['W'] = 1; M['S'] = 2; M['E'] = 3;

	while (std::getline(fin, line)) {
		int nr = std::stoi(line.substr(1), std::size_t());
		switch (line[0]) {
			case 'F': {
				for (int i = 0; i < 2; i ++) {
					P[waypoint[i].first] += waypoint[i].second * nr;
				}
				break;
			}
			case 'L': {
				for (int i = 0; i < 2; i ++) {
					waypoint[i].first = (waypoint[i].first + (nr / 90)) % 4;
				}
				break;
			}
			case 'R': {
				for (int i = 0; i < 2; i ++) {
					waypoint[i].first = (waypoint[i].first - (nr / 90) + 4) % 4;
				}
				break;
			}
			default: {
				for (int i = 0; i < 2; i ++) {
					if (M[line[0]] == waypoint[i].first) {
						waypoint[i].second += nr;
						break;
					}
					else if (M[line[0]] == (waypoint[i].first + 2) % 4) {
						if (nr > waypoint[i].second) {
							waypoint[i].first = (waypoint[i].first + 2) % 4;
						}
						waypoint[i].second = abs(waypoint[i].second - nr);
					}
				}
			}
		}
	}
	std::cout << abs(P[0] - P[2]) + abs(P[1] - P[3]) << '\n';
}

int main() {
	//solve1();
	solve2();
	return 1;
}