#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("input.in");

const long long MOD = 20201227;

void solve() {
	long long cardKey, doorKey, cardLoop = 0, doorLoop = 0, subjectNmber = 7;
	fin >> cardKey >> doorKey;
	
	long long key = 1;
	while (key != cardKey) {
		key = (key * subjectNmber) % MOD;
		cardLoop++;
	}

	subjectNmber = doorKey;
	long long encriptionKey = 1;
	while (cardLoop) {
		encriptionKey = (encriptionKey * subjectNmber) % MOD;
		cardLoop --;
	}
	cout << encriptionKey << '\n';
}

int main() {
	solve();
	return 0;
}