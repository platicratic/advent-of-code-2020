#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin("input.in");

int solve1() {
	int number, oneJolt = 0, threeJolts = 1, lastNumber = 0;
	std::vector<int> V;
	while (fin >> number) {
		V.push_back(number);
	}
	sort(V.begin(), V.end());
	for (int i = 0; i < V.size(); i++) {
		int difference = V[i] - lastNumber;
		if (difference == 1) {
			oneJolt ++;
		}
		else if (difference == 3) {
			threeJolts ++;
		}
		lastNumber = V[i];
	}
	return oneJolt * threeJolts;
}

long long solve2() {
	int number;
	std::vector<std::pair<int, long long>> V;
	while (fin >> number) {
		V.push_back({ number, 0 });
	}
	V.push_back({ 0, 1 });
	sort(V.begin(), V.end());
	for (int i = 0; i < V.size(); i++) {
		for (int j = (i - 3 > 0 ? i - 3 : 0); j < i; j ++) {
			if (V[i].first - V[j].first <= 3) {
				V[i].second += V[j].second;
			}
		}
	}
	return V.back().second;
}

int main() {
	//std::cout << solve1() << '\n';
	std::cout << solve2() << '\n';
	return 0;
}