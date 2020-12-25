// Part Two

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("input.in");

void add(int F[], int &sol, int nrOfPersons) {
    for (int i = 0; i < 26; i ++) {
        if (F[i] == nrOfPersons) {
            sol ++;
        }
    }
}

void solve() {
    string line;
    int F[26];
    memset(F, 0, 26 * 4);
    int sol = 0, currentNumberOfPersons = 0;
    while (getline(fin, line)) {
        if (line.size() < 1) {
            add(F, sol, currentNumberOfPersons);
            memset(F, 0, 26 * 4);
            currentNumberOfPersons = 0;
        } else {
            for (char chr : line) {
                F[chr - 'a'] += 1;
            }
            currentNumberOfPersons += 1;
        }
    }
    add(F, sol, currentNumberOfPersons);
    cout << sol << '\n';
}

int main()
{
    solve();
    return 0;
}
