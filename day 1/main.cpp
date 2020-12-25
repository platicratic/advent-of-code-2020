// Part Two

#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

vector<int> V;

void read() {
    int number;
    while (fin >> number) {
        V.push_back(number);
    }
}

void solve() {
    for (int i = 0; i < V.size(); i ++) {
        for (int j = i + 1; j < V.size(); j ++) {
            for (int k = j + 1; k < V.size(); k ++) {
                if (V[i] + V[j] + V[k] == 2020) {
                    fout << V[i] * V[j] * V[k];
                    return;
                }
            }
        }
    }
}

int main()
{
    read();
    solve();
    return 0;
}
