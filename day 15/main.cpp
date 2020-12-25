// Part Two

#include <iostream>
#include <fstream>
#include <unordered_map>

std::ifstream fin("input.in");

inline void solve() {
	unsigned int nr, count = 1;
	std::unordered_map<unsigned int, unsigned int> M;
	while (fin >> nr) {
		M[nr] = count ++;
	}
	M.erase(nr); count --;
	while (count < 30000000) {
		if (M[nr]) {
			std::unordered_map<unsigned int, unsigned int>::iterator it = M.find(nr);
			nr = count - it->second;
			it->second = count;
		}
		else {
			M[nr] = count;
			nr = 0;
		}
		++count;
	}
	std::cout << nr << '\n';
}

int main() {
	solve();
	return 0;
}