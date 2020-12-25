#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

ifstream fin("input.in");

int colors = 0;
map<string, int> M;
vector<vector<pair<int, int>>> V(1000, vector<pair<int, int>>(0));

void addBag(string bag) {
    if (!M[bag]) {
        M[bag] = ++colors;
    }
}

void addEdge(string i, string j, int k) {
    V[M[i]].push_back({M[j], k});
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
        while (true) {
            if ((int)line.find(" no ") > -1) break;
            line.erase(0, 1);
            int innerBagNumber = stoi(line.substr(0, line.find(" ")), size_t());
            innerBag = line.substr(line.find(" ") + 1, line.find("bag") - 3);
            addBag(innerBag);
            addEdge(outerBag, innerBag, innerBagNumber);
            if ((int)line.find(",") > -1) {
                line.erase(0, line.find(",") + 1);
            } else {
                break;
            }
        }
    }
}

int solve(pair<int, int> node) {
    int currentNumberOfBags = 1;
    for (int i = 0; i < V[node.first].size(); i ++) {
        currentNumberOfBags = currentNumberOfBags + solve(V[node.first][i]);
    }
    return node.second * currentNumberOfBags;
}

int main()
{
    read();
    cout << solve({M["shiny gold"], 1}) - 1 << '\n';
    return 0;
}
