#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

ifstream fin("input.in");

int colors = 0, sol = 0;
map<string, int> M;
vector<vector<int>> V(1000, vector<int>(0));
vector<bool> F;

void addBag(string bag) {
    if (!M[bag]) {
        M[bag] = ++colors;
    }
}

void addEdge(string outerBag, string innerBag) {
    V[M[innerBag]].push_back(M[outerBag]);
}

void read() {
    string line;
    while(getline(fin, line)) {
        int pos;
        string innerBag, outerBag;
        pos = line.find("contain");
        outerBag = line.substr(0, pos - 6);
        addBag(outerBag);
        line.erase(0, pos + 7);
        cout << outerBag << ":";
        while (true) {
            if ((int)line.find(" no ") > -1) break;
            line.erase(0, 1);
            innerBag = line.substr(line.find(" ") + 1, line.find("bag") - 3);
            addBag(innerBag);
            addEdge(outerBag, innerBag);
            cout << innerBag << ',';
            if ((int)line.find(",") > -1) {
                line.erase(0, line.find(",") + 1);
            } else {
                break;
            }
        }
        cout << '\n';
    }
}

void solve(int node) {
    F[node] = true;
    sol ++;
    for (int i = 0; i < V[node].size(); i ++) {
        if (!F[V[node][i]]) {
            solve(V[node][i]);
        }
    }
}

int main()
{
    read();
    F = vector<bool>(colors + 1, false);
    solve(M["shiny gold"]);
    cout << sol - 1 << '\n';
    return 0;
}
