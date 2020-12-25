#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<map>

using namespace std;

ifstream fin("input.in");

const int tileSize = 10;

string reverse(string s) {
	int first = 0;
	int last = s.size() - 1;
	while (first < last) {
		swap(s[first], s[last]);
		++first;
		--last;
	}
	return s;
}

void check1(vector<string> &T1, vector<string> &T2, vector<pair<int, int>> &V1, vector<pair<int, int>> &V2) {
	for (int i = 0; i < 4; i ++) {
		for (int j = 0; j < 4; j ++) {
			string r1 = reverse(T1[i]);
			string r2 = reverse(T2[j]);
			if ((T1[i] == T2[j]) || (T1[i] == r2) || (r1 == T2[j]) || (r1 == r2)) {
				V1[i + 1].first ++;
				V1[i + 1].second = V2[0].first;
				V2[j + 1].first ++;
				V2[j + 1].second = V1[0].first;
				return;
			}
		}
	}
}

void solve1() {
	string line;
	int id;
	vector<vector<pair<int, int>>> V;
	vector<vector<string>> M;

	while (fin >> line && fin >> id && getline(fin, line)) {
		vector<pair<int, int>> I(5, { 0, 0 });
		I[0].first = id;
		V.push_back(I);

		vector<string> S, E;
		for (int i = 0; i < tileSize; i ++) {
			getline(fin, line);
			S.push_back(line);
		}
		E.push_back(S[0]);
		string e = "";
		for (int i = 0; i < tileSize; i ++) e += S[i][tileSize - 1];
		E.push_back(e);
		E.push_back(S[tileSize - 1]);
		e = "";
		for (int i = 0; i < tileSize; i ++) e += S[i][0];
		E.push_back(e);
		M.push_back(E);

		getline(fin, line);
	}

	for (int i = 0; i < V.size(); i ++) {
		for (int j = i + 1; j < V.size(); j ++) {
			check1(M[i], M[j], V[i], V[j]);
		}
	}
	
	long long sol = 1;
	for (int i = 0; i < V.size(); i ++) {
		int corner = 0;
		for (int j = 1; j <= 4; j ++) {
			if (V[i][j].first == 0) {
				corner ++;
			}
		}
		if (corner == 2) {
			sol *= V[i][0].first;
		}
	}

	cout << sol << '\n';
}

void rotate(vector<string> &T) {
	vector<string> R(T.size(), string(T.size(), ' '));
	for (int j1 = 0, i2 = 0; j1 < T.size(); j1++, i2++) {
		for (int i1 = T.size() - 1, j2 = 0; i1 >= 0; i1--, j2++) {
			R[i2][j2] = T[i1][j1];
		}
	}
	T = R;
}

void flipX(vector<string> &T) {
	int nr = T.size() - 1;
	for (int i = 0; i < T.size() / 2; i++) {
		swap(T[i], T[nr - i]);
	}
}

void flipY(vector<string> &T) {
	int nr = T.size() - 1;
	for (int i = 0; i < T.size(); i++) {
		for (int j = 0; j < T.size() / 2; j++) {
			swap(T[i][j], T[i][nr - j]);
		}
	}
}

void rotate(vector<string> &T, vector<pair<int, int>> &V) {
	vector<string> R(tileSize, string(10, ' '));
	for (int j1 = 0, i2 = 0; j1 < tileSize; j1++, i2++) {
		for (int i1 = tileSize - 1, j2 = 0; i1 >= 0; i1--, j2++) {
			R[i2][j2] = T[i1][j1];
		}
	}
	T = R;
	pair<int, int> aux = V[3];
	for (int i = 3; i > 0; i--) {
		V[i] = V[i - 1];
	}
	V[0] = aux;
}

void flipX(vector<string> &T, vector<pair<int, int>> &V) {
	int nr = tileSize - 1;
	for (int i = 0; i < tileSize / 2; i ++) {
		swap(T[i], T[nr - i]);
	}
	swap(V[0], V[2]);
}

void flipY(vector<string> &T, vector<pair<int, int>> &V) {
	int nr = tileSize - 1;
	for (int i = 0; i < tileSize; i ++) {
		for (int j = 0; j < tileSize / 2; j ++) {
			swap(T[i][j], T[i][nr - j]);
		}
	}
	swap(V[1], V[3]);
}

vector<string> getEdges(vector<string> S) {
	vector<string> E;
	E.push_back(S[0]);
	string e = "";
	for (int i = 0; i < tileSize; i ++) e += S[i][tileSize - 1];
	E.push_back(e);
	E.push_back(reverse(S[tileSize - 1]));
	e = "";
	for (int i = tileSize - 1; i >= 0; i --) e += S[i][0];
	E.push_back(e);
	return E;
}

void check2(int id1, int id2, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	vector<string> &T1 = Matrix[id1];
	vector<string> &T2 = Matrix[id2];
	vector<pair<int, int>> &M1 = Map[id1];
	vector<pair<int, int>> &M2 = Map[id2];
	vector<string> E1 = getEdges(T1), E2 = getEdges(T2);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			string r1 = reverse(E1[i]);
			string r2 = reverse(E2[j]);
			if ((E1[i] == E2[j]) || (E1[i] == r2) || (r1 == E2[j]) || (r1 == r2)) {
				M1[i].first = 1;
				M1[i].second = id2;
				M2[j].first = 1;
				M2[j].second = id1;
				return;
			}
		}
	}
}

bool checkEdgeRightLeft(vector<string> &M1, vector<string> &M2) {
	for (int i = 0; i < tileSize; i ++) {
		if (M1[i][tileSize - 1] != M2[i][0]) {
			return false;
		}
	}
	return true;
}

bool checkEdgeDownUp(vector<string> &M1, vector<string> &M2) {
	return M1[tileSize - 1] == M2[0];
}

void afis(vector<string> A, vector<string> B) {
	for (int i = 0; i < A.size(); i ++) {
		cout << A[i] << ' ' << B[i] << '\n';
	}
	cout << '\n';
}

bool positionateRightLeft(int lastId, int id, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	for (int k = 0; k < 4; k++) {
		rotate(Matrix[id], Map[id]);
		if (Map[id][3].second == lastId) {
			if (checkEdgeRightLeft(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipX(Matrix[id], Map[id]);
			if (checkEdgeRightLeft(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipX(Matrix[id], Map[id]);
		}
		else if (Map[id][1].second == lastId) {
			flipY(Matrix[id], Map[id]);
			if (checkEdgeRightLeft(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipX(Matrix[id], Map[id]);
			if (checkEdgeRightLeft(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipX(Matrix[id], Map[id]);
			flipY(Matrix[id], Map[id]);
		}
	}
	return false;
}

bool positionateDownUp(int lastId, int id, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	for (int k = 0; k < 4; k++) {
		rotate(Matrix[id], Map[id]);
		if (Map[id][0].second == lastId) {
			if (checkEdgeDownUp(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipY(Matrix[id], Map[id]);
			if (checkEdgeDownUp(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipY(Matrix[id], Map[id]);
		}
		else if (Map[id][2].second == lastId) {
			flipX(Matrix[id], Map[id]);
			if (checkEdgeDownUp(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipY(Matrix[id], Map[id]);
			if (checkEdgeDownUp(Matrix[lastId], Matrix[id])) {
				return true;
			}
			flipY(Matrix[id], Map[id]);
			flipX(Matrix[id], Map[id]);
		}
	}
	return false;
}

pair<bool, vector<vector<int>>> populate(int corner, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	int matrixSize = sqrt(Matrix.size());

	vector<vector<int>> V(matrixSize, vector<int>(matrixSize, 0));
	V[0][0] = corner;

	for (int j = 1; j < matrixSize; j ++) {
		if (positionateRightLeft(V[0][j - 1], Map[V[0][j - 1]][1].second, Matrix, Map)) {
			V[0][j] = Map[V[0][j - 1]][1].second;
		}
		else {
			return { false, V };
		}
	}

	for (int i = 1; i < matrixSize; i ++) {
		for (int j = 0; j < matrixSize; j ++) {
			if (positionateDownUp(V[i - 1][j], Map[V[i - 1][j]][2].second, Matrix, Map)) {
				V[i][j] = Map[V[i - 1][j]][2].second;
			}
			else {
				return { false, V };
			}
		}
	}

	return { true, V };
}

pair<bool, vector<vector<int>>> isThisGoingToEnd(int corner, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	if (Map[corner][1].first == 1 && Map[corner][2].first == 1) {
		return populate(corner, Matrix, Map);
	}
	return { false, vector<vector<int>>() };
}

pair<bool, vector<vector<int>>> createPicture(int corner, map<int, vector<string>> &Matrix, map<int, vector<pair<int, int>>> &Map) {
	pair<bool, vector<vector<int>>> aux;

	for (int k = 0; k < 4; k++) {
		rotate(Matrix[corner], Map[corner]);
		aux = isThisGoingToEnd(corner, Matrix, Map);
		if (aux.first) {
			return aux;
		}

		flipX(Matrix[corner], Map[corner]);
		aux = isThisGoingToEnd(corner, Matrix, Map);
		if (aux.first) {
			return aux;
		}
		flipX(Matrix[corner], Map[corner]);

		flipY(Matrix[corner], Map[corner]);
		aux = isThisGoingToEnd(corner, Matrix, Map);
		if (aux.first) {
			return aux;
		}
		flipY(Matrix[corner], Map[corner]);

		flipX(Matrix[corner], Map[corner]);
		flipY(Matrix[corner], Map[corner]);
		aux = isThisGoingToEnd(corner, Matrix, Map);
		if (aux.first) {
			return aux;
		}
		flipX(Matrix[corner], Map[corner]);
		flipY(Matrix[corner], Map[corner]);
	}
	return {};
}

int countMonsters(vector<string> &monsterPicture, vector<pair<int, int>> &seaMonster) {
	int count = 0;
	for (int i = 0; i < monsterPicture.size() - 3; i++) {
		for (int j = 0; j < monsterPicture[i].size() - 20; j++) {
			bool ok = true;
			for (auto it : seaMonster) {
				if (monsterPicture[i + it.first][j + it.second] != '#') {
					ok = false;
					break;
				}
			}
			if (ok) {
				count ++;
				for (auto it : seaMonster) {
					monsterPicture[i + it.first][j + it.second] = 'O';
				}
			}
		}
	}
	return count;
}

void solve2() {
	string line;
	int id;
	map<int, vector<pair<int, int>>> Map;
	map<int, vector<string>> Matrix;
	vector<int> Ids;

	while (fin >> line && fin >> id && getline(fin, line)) {
		vector<pair<int, int>> I(4, { 0, 0 });
		Map[id] = I;
		Ids.push_back(id);

		vector<string> S;
		for (int i = 0; i < tileSize; i++) {
			getline(fin, line);
			S.push_back(line);
		}
		Matrix[id] = S;

		getline(fin, line);
	}

	// check edges
	for (int i = 0; i < Ids.size(); i ++) {
		for (int j = i + 1; j < Ids.size(); j ++) {
			check2(Ids[i], Ids[j], Matrix, Map);
		}
	}

	// find corners
	vector<int> Corners;
	for (auto it : Map) {
		int corner = 0;
		for (int i = 0; i < 4; i ++) {
			if (it.second[i].first == 0) {
				corner++;
			}
		}
		if (corner == 2) {
			Corners.push_back(it.first);
		}
	}

	// 4 possible corner positions :)
	pair<bool, vector<vector<int>>> picture = createPicture(Corners[0], Matrix, Map);
	
	vector<string> monsterPicture(sqrt(Matrix.size()) * (tileSize - 2), "");
	if (picture.first == true) {
		for (int i = 0; i < picture.second.size(); i++) {
			for (int j = 0; j < picture.second[i].size(); j++) {
				for (int k = 1; k < tileSize - 1; k++) {
					monsterPicture[i * (tileSize - 2) + k - 1] += Matrix[picture.second[i][j]][k].substr(1, tileSize - 2);
				}
			}
		}
	}

	vector<pair<int, int>> seaMonster;
	vector<string> seaMonsterString;
	seaMonsterString.push_back("                  # ");
	seaMonsterString.push_back("#    ##    ##    ###");
	seaMonsterString.push_back(" #  #  #  #  #  #   ");
	for (int i = 0; i < seaMonsterString.size(); i ++) {
		for (int j = 0; j < seaMonsterString[i].size(); j ++) {
			if (seaMonsterString[i][j] == '#') {
				seaMonster.push_back({ i, j });
			}
		}
	}

	for (int k = 0; k < 4; k ++) {
		rotate(monsterPicture);
		if (countMonsters(monsterPicture, seaMonster) > 0) {
			break;
		}
		flipX(monsterPicture);
		if (countMonsters(monsterPicture, seaMonster) > 0) {
			break;
		}
		flipX(monsterPicture);
		flipY(monsterPicture);
		if (countMonsters(monsterPicture, seaMonster) > 0) {
			break;
		}
		flipY(monsterPicture);
		flipX(monsterPicture);
		flipY(monsterPicture);
		if (countMonsters(monsterPicture, seaMonster) > 0) {
			break;
		}
		flipX(monsterPicture);
		flipY(monsterPicture);
	}

	int solution = 0;
	for (auto mp : monsterPicture) {
		for (auto character : mp) {
			if (character == '#') {
				solution++;
			}
		}
	}
	cout << solution << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}