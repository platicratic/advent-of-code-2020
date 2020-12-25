#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.in");

const int length = 8;
const int cycles = 6;
const int maxLength = 20;

int countActive(int x, int y, int z, vector<vector<vector<bool>>> &V) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i ++) {
		for (int j = y - 1; j <= y + 1; j ++) {
			for (int k = z - 1; k <= z + 1; k ++) {
				count += V[i][j][k];
			}
		}
	}
	count -= V[x][y][z];
	return count;
}

void solve1() {
	vector<vector<vector<bool>>> V1, V2(maxLength + 2, vector<vector<bool>>(maxLength + 2, vector<bool>(maxLength + 2, false)));
	char c;
	
	// read
	for (int i = 1; i <= length; i ++) {
		for (int j = 1; j <= length; j ++) {
			fin.get(c);
			V2[i + cycles][j + cycles][length / 2 + cycles + 1] = (c == '#');
		}
		fin.get();
	}

	// solve
	for (int c = 0; c < cycles; c ++) {
		V1 = V2;
		for (int x = 1; x <= maxLength; x ++) {
			for (int y = 1; y <= maxLength; y ++) {
				for (int z = 1; z <= maxLength; z ++) {
					int count = countActive(x, y, z, V1);
					if (V1[x][y][z]) {
						if (count < 2 || count > 3) {
							V2[x][y][z] = !V2[x][y][z];
						}
					}
					else {
						if (count == 3) {
							V2[x][y][z] = !V2[x][y][z];
						}
					}
				}
			}
		}
	}

	// write
	int sol = 0;
	for (int x = 1; x <= maxLength; x ++) {
		for (int y = 1; y <= maxLength; y ++) {
			for (int z = 1; z <= maxLength; z ++) {
				sol += V2[x][y][z];
			}
		}
	}
	cout << sol << '\n';
}

int countActive(int x, int y, int z, int w, vector<vector<vector<vector<bool>>>> &V) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			for (int k = z - 1; k <= z + 1; k++) {
				for (int l = w - 1; l <= w + 1; l++) {
					count += V[i][j][k][l];
				}
			}
		}
	}
	count -= V[x][y][z][w];
	return count;
}

void solve2() {
	vector<vector<vector<vector<bool>>>> V1, V2(maxLength + 2, vector<vector<vector<bool>>>(maxLength + 2, vector<vector<bool>>(maxLength + 2, vector<bool>(maxLength + 2, false))));
	char c;

	// read
	for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			fin.get(c);
			V2[i + cycles][j + cycles][length / 2 + cycles + 1][length / 2 + cycles + 1] = (c == '#');
		}
		fin.get();
	}

	// solve
	for (int c = 0; c < cycles; c++) {
		V1 = V2;
		for (int x = 1; x <= maxLength; x++) {
			for (int y = 1; y <= maxLength; y++) {
				for (int z = 1; z <= maxLength; z++) {
					for (int w = 1; w <= maxLength; w++) {
						int count = countActive(x, y, z, w, V1);
						if (V1[x][y][z][w]) {
							if (count < 2 || count > 3) {
								V2[x][y][z][w] = !V2[x][y][z][w];
							}
						}
						else {
							if (count == 3) {
								V2[x][y][z][w] = !V2[x][y][z][w];
							}
						}
					}
				}
			}
		}
	}

	// write
	int sol = 0;
	for (int x = 1; x <= maxLength; x++) {
		for (int y = 1; y <= maxLength; y++) {
			for (int z = 1; z <= maxLength; z++) {
				for (int w = 1; w <= maxLength; w++) {
					sol += V2[x][y][z][w];
				}
			}
		}
	}
	cout << sol << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}