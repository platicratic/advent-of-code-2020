// Part Two

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("input.in");

int calc(char lowerChar, char higherChar, int lower, int higher, std::string line) {
    int i = 0;
    while (lower < higher && i < 7) {
        int middle = (lower + higher) / 2;
        if (line[i] == lowerChar) {
            higher = middle;
        } else if (line[i] == higherChar) {
            lower = middle + 1;
        }
        i ++;
    }
    if (lower != higher) cout << "something wrong";
    return lower;
}

void solve() {
    std::string line;
    std::vector<bool> F(1024, false);

    while(getline(fin, line)) {
        int seatId = calc('F', 'B', 0, 127, line.substr(0, 7)) * 8 + calc('L', 'R', 0, 7, line.substr(7, 3));
        F[seatId] = true;
    }

    for (int i = 0; i < 1024; i ++) {
        if (F[i] == false) {
            cout << i << '\n';
        }
    }
}

int main()
{
    solve();
    return 0;
}
