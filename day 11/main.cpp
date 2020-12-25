#include <iostream>
#include <fstream>
#include <vector>

std::ifstream fin("input.in");

const std::pair<int, int> Adj[8] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 } };

std::vector<std::vector<char>> read() {
	std::vector<std::vector<char>> V;
	V.push_back(std::vector<char>());
	char c;
	while (fin.get(c)) {
		if (c == '\n') {
			V.push_back(std::vector<char>());
			continue;
		}
		V.back().push_back(c);
	}
	V.pop_back();
	return V;
}

void checkSolution(const std::vector<std::vector<char>> &V) {
	int sol = 0;
	for (auto itLine : V) {
		for (auto it : itLine) {
			if (it == '#') {
				sol++;
			}
		}
	}
	std::cout << sol << '\n';
}

bool verifyEmpty1(const std::vector<std::vector<char>> &V, const int i, const int j) {
	for (int k = 0; k < 8; k ++) {
		int ii = i + Adj[k].first;
		int jj = j + Adj[k].second;

		if (ii >= 0 && ii < V.size() && jj >= 0 && jj < V[ii].size() && V[ii][jj] == '#') {
			return false;
		}
	}
	return true;
}

bool verifyOcupied1(const std::vector<std::vector<char>> &V, const int i, const int j) {
	int nr = 0;
	for (int k = 0; k < 8; k++) {
		int ii = i + Adj[k].first;
		int jj = j + Adj[k].second;

		if (ii >= 0 && ii < V.size() && jj >= 0 && jj < V[ii].size() && V[ii][jj] == '#') {
			nr ++;
		}
	}
	return (nr > 3);
}

void solve1(std::vector<std::vector<char>> M1) {
	bool changesExists = true;
	std::vector<std::vector<char>> M2 = M1;

	while (changesExists) {
		changesExists = false;
		for (int i = 0; i < M1.size(); i++) {
			for (int j = 0; j < M1[i].size(); j++) {
				char c = M1[i][j];
				if (M1[i][j] == 'L') {
					if (verifyEmpty1(M1, i, j)) {
						c = '#';
						changesExists = true;
					}
				}
				else if (M1[i][j] == '#') {
					if (verifyOcupied1(M1, i, j)) {
						c = 'L';
						changesExists = true;
					}
				}
				M2[i][j] = c;
			}
		}
		M1 = M2;
	}
	checkSolution(M1);
}

std::vector<std::vector<std::vector<std::pair<int, int>>>> precalc(std::vector<std::vector<char>> &V) {
	std::vector<std::vector<std::vector<std::pair<int, int>>>> P(V.size(), std::vector<std::vector<std::pair<int, int>>>(V[0].size(), std::vector<std::pair<int, int>>()));
	for (int i = 0; i < V.size(); i ++) {
		for (int j = 0; j < V[i].size(); j ++) {
			if (V[i][j] != '.') {
				for (int k = 0; k < 8; k++) {
					int ii = i + Adj[k].first;
					int jj = j + Adj[k].second;
					while (ii >= 0 && ii < V.size() && jj >= 0 && jj < V[ii].size()) {
						if (V[ii][jj] != '.') {
							P[i][j].push_back({ ii, jj });
							break;
						}
						ii = ii + Adj[k].first;
						jj = jj + Adj[k].second;
					}
					if (!(ii >= 0 && ii < V.size() && jj >= 0 && jj < V[ii].size())) {
						P[i][j].push_back({ 666013, 666013 });
					}
				}
			}
		}
	}
	return P;
}

bool verifyEmpty2(const std::vector<std::vector<std::vector<std::pair<int, int>>>> &P, const std::vector<std::vector<char>> &V, const int i, const int j) {
	for (int k = 0; k < 8; k++) {
		if (P[i][j][k].first == 666013 && P[i][j][k].second == 666013) continue;
		if (V[P[i][j][k].first][P[i][j][k].second] == '#') {
			return false;
		}
	}
	return true;
}

bool verifyOcupied2(const std::vector<std::vector<std::vector<std::pair<int, int>>>> &P, const std::vector<std::vector<char>> &V, const int i, const int j) {
	int nr = 0;
	for (int k = 0; k < 8; k++) {
		if (P[i][j][k].first == 666013 && P[i][j][k].second == 666013) continue;
		if (V[P[i][j][k].first][P[i][j][k].second] == '#') {
			nr ++;
		}
	}
	return (nr > 4);
}

void solve2(std::vector<std::vector<char>> M1) {
	std::vector<std::vector<std::vector<std::pair<int, int>>>> P = precalc(M1);
	bool changesExists = true;
	std::vector<std::vector<char>> M2 = M1;

	while (changesExists) {
		changesExists = false;
		for (int i = 0; i < M1.size(); i ++) {
			for (int j = 0; j < M1[i].size(); j ++) {
				char c = M1[i][j];
				if (M1[i][j] == 'L') {
					if (verifyEmpty2(P, M1, i, j)) {
						c = '#';
						changesExists = true;
					}
				}
				else if (M1[i][j] == '#') {
					if (verifyOcupied2(P, M1, i, j)) {
						c = 'L';
						changesExists = true;
					}
				}
				M2[i][j] = c;
			}
		}
		M1 = M2;
	}
	checkSolution(M1);
}

int main() {
	/*solve1(read());*/
	solve2(read());
	return 0;
}