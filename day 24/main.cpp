#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

ifstream fin("input.in");

const int hexagons = 67951; // 150 hexagons in every direction
const int border = 906;
const map<string, int> Directions({ { "ne", 0 }, { "e", 1 }, { "se", 2 }, { "sw", 3 }, { "w", 4 }, { "nw", 5 } });

inline int opposite(int i) {
	return (i + 3) % 6;
}

inline int upper(int i) {
	return (i - 1 + 6) % 6;
}

inline int lower(int i) {
	return (i + 1) % 6;
}

void createHexGrid(vector<vector<int>> &G) {

	int total = 1;
	for (int i = 0; i < 151; i++) {
		total += (i * 6);
	}
	cout << total << '\n';

	int futureNodes = 1;

	for (int node = 0; node < hexagons; node ++) {
		vector<bool> A(6, false);
		for (int i = 0; i < 6; i ++) {
			if (G[node][i] < 0) {
				A[i] = true;
				G[node][i] = futureNodes ++;
				G[G[node][i]][opposite(i)] = node;
			}
		}
		for(int i = 0; i < 6; i ++) {
			if (A[i]) {
				int upNode = G[node][upper(i)];
				int upEdge = upper(opposite(upper(i)));

				int middleNode = G[node][i];
				int middleEdgeUp = lower(opposite(i));
				int middleEdgeDown = upper(opposite(i));

				int downNode = G[node][lower(i)];
				int downEdge = lower(opposite(lower(i)));

				G[upNode][upEdge] = middleNode;
				G[middleNode][middleEdgeUp] = upNode;
				G[middleNode][middleEdgeDown] = downNode;
				G[downNode][downEdge] = middleNode;
			}
		}
	}
}

void simultaneously(vector<bool> &F, vector<bool> &FF, vector<vector<int>> &G) {
	for (int i = 0; i < hexagons; i ++) {
		int black = 0;
		for (int j = 0; j < 6; j ++) {
			black += F[G[i][j]];
		}
		
		if ((F[i] && (black == 0 || black > 2)) || (!F[i] && black == 2)) {
			FF[i] = !F[i];
		}
	}
}

void countBlack(vector<bool> &F) {
	int sol = 0;
	for (int i = 0; i < hexagons; i++) {
		sol += F[i];
	}
	cout << sol << '\n';
}

void solve() {
	string line;
	vector<vector<int>> G(hexagons + border, vector<int>(6, -1));
	vector<bool> F(hexagons + border, false), FF(hexagons + border, false);
	
	createHexGrid(G);
	
	while (getline(fin, line)) {
		int node = 0;
		for (int i = 0; i < line.size(); i ++) {
			string direction = string(1, line[i]);
			if (line[i] == 's' || line[i] == 'n') {
				i++;
				direction += line[i];
			}
			node = G[node][Directions.at(direction)];
		}
		F[node] = !F[node];
	}

	// solve 1
	cout << "black tiles: ";
	countBlack(F);

	// solve 2
	FF = F;
	for (int i = 1; i <= 100; i ++) {
		simultaneously(F, FF, G);
		F = FF;
		cout << "day " << i << ": ";
		countBlack(F);
	}
}


int main() {
	solve();
	return 0;
}
