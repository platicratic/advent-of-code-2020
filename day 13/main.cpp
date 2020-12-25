#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ifstream fin("input.in");

int timestamp;
std::vector<int> V;

void read() {
	fin >> timestamp;
	std::string numberString;
	while (std::getline(fin, numberString, ',')) {
		int number = 0;
		if (numberString != "x") {
			number = std::stoi(numberString, size_t());
		}
		V.push_back(number);
	}
}

void solve1() {
	std::pair<int, int> minim = { 0x3f3f3f3f, 0 };
	for (int it : V) {
		if (it != 0) {
			int diff = timestamp % it;
			diff = (diff != 0 ? it - diff : diff);
			if (diff < minim.first) {
				minim = { diff, it };
			}
		}
	}
	std::cout << minim.first * minim.second << '\n';
}

long long cmmmcCalc(long long a, long long b) {
	long long c = a * b;
	while (b != 0) {
		long long r = a % b;
		a = b;
		b = r;
	}
	return c / a;
}

void solve2() {
	long long time = 0, cmmmc = V[0];
	for (int i = 1; i < V.size(); i++) {
		if (V[i] == 0) continue;
		while ((time + i) % V[i] != 0) {
			time += cmmmc;
		}
		cmmmc = cmmmcCalc(cmmmc, V[i]);
	}
	std::cout << time << '\n';
}

int main() {
	read();
	solve1();
	solve2();
	return 0;
}