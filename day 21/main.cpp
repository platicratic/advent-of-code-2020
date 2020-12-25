#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("input.in");

bool f(pair<string, int> a, pair<string, int> b) {
	return a.second > b.second;
}

void solve() {
	// Declaration
	map<string, map<string, int>> M;
	string line;
	multiset<string> Ingredients;
	vector<pair<string, string>> S;
	
	// Read
	while (getline(fin, line)) {
		vector<string> Ing;
		stringstream part1(line.substr(0, line.find('(')));
		string ingredient, allergen;

		while (getline(part1, ingredient, ' ')) {
			Ing.push_back(ingredient);
			Ingredients.insert(ingredient);
		}

		stringstream part2(line.substr(line.find("contains ") + 9, line.size() - (line.find("contains ") + 10)));
		while (getline(part2, allergen, ',')) {
			for (auto it : Ing) {
				if (M[allergen][it]) {
					M[allergen][it] ++;
				}
				else {
					M[allergen][it] = 1;
				}
			}
			part2.get();
		}
	}

	// Solve
	while (M.size() > 0) {
		string elimAllergen = "";
		string elimIngredient = "";
		for (auto m : M) {
			vector<pair<string, int>> V(m.second.begin(), m.second.end());
			sort(V.begin(), V.end(), f);
			if (V.size() == 1 || (V.size() > 1 && V[0].second != V[1].second)) {
				elimAllergen = m.first;
				elimIngredient = V[0].first;
				break;
			}
		}
		M.erase(elimAllergen);
		for (auto &m : M) {
			m.second.erase(elimIngredient);
		}
		Ingredients.erase(elimIngredient);

		// Solve 2
		S.push_back({ elimAllergen, elimIngredient });
	}

	// Write
	// Solve 1
	cout << Ingredients.size() << '\n';

	// Solve 2
	sort(S.begin(), S.end());
	for (auto it : S) {
		cout << it.second << ',';
	}
}

int main() {
	solve();
	return 0;
}
