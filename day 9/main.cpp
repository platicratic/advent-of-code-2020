#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <vector>

std::ifstream fin("input.in");

const int preamble = 25;
std::vector<long long> V;

void insert(long long nr, std::deque<long long> &DQ, std::multiset<long long> &S) {
	for (int i = 0; i < DQ.size(); i++) {
		S.insert(DQ[i] + nr);
	}
	DQ.push_back(nr);
}

void remove(std::deque<long long> &DQ, std::multiset<long long> &S) {
	for (int i = 1; i < DQ.size(); i++) {
		S.erase(S.find(DQ[0] + DQ[i]));
	}
	DQ.pop_front();
}

long long solve1() {
	long long nr;
	std::deque<long long> DQ;
	std::multiset<long long> S;

	for (int i = 0; i < preamble; i++) {
		fin >> nr;
		V.push_back(nr);
		insert(nr, DQ, S);
	}
	while (fin >> nr) {
		V.push_back(nr);
		if (S.find(nr) == S.end()) {
			return nr;
		}
		remove(DQ, S);
		insert(nr, DQ, S);
	}
}

long long solve2(long long invalid) {
	long long sum = 0;
	std::deque<long long> DQ;
	
	for (int i = 0; i < V.size(); i ++) {
		sum += V[i];
		DQ.push_back(V[i]);

		while (sum > invalid && DQ.size() > 2) {
			sum -= DQ.front();
			DQ.pop_front();
		}

		if (sum == invalid && DQ.size() > 1) {
			long long max = 0, min = 1LL * 0x3f3f3f3f * 0x3f3f3f3f;
			for (int j = 0; j < DQ.size(); j ++) {
				if (DQ[j] > max) max = DQ[j];
				if (DQ[j] < min) min = DQ[j];
			}
			return min + max;
		}
	}
}

int main() {
	std::cout << solve2(solve1()) << '\n';
	return 0;
}