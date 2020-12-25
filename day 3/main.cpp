// Part Two

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream fin("input.in");

const int MOD = 31;
vector<string> V;

void read() {
    std::string line;
    while (getline(fin, line)) {
        V.push_back(line);
    }
}

long solve(int iInc, int jInc) {
    int i = 0, j = 0;
    long sol = 0;
    while (i < V.size() - 1) {
        i += iInc;
        j = (j + jInc) % MOD;
        if (V[i][j] == '#') {
            sol ++;
        }
    }
    return sol;
}

int main()
{
    read();
    cout << 1LL * solve(1, 1) * solve(1, 3) * solve(1, 5) * solve(1, 7) * solve(2, 1);
    return 0;
}
