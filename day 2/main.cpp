// Part Two

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int verifyPassword(int lower, int upper, char letter, std::string password) {
    /* int nr = 0;
    for (int i = 0; i < password.size(); i ++) {
        if (password[i] == letter) {
            nr ++;
        }
    } */
    return ((password[lower - 1] == letter) ^ (password[upper - 1] == letter));
}

void solve()
{
    std::string line;
    int valid = 0;

    while (std::getline(fin, line, '\n')) {
        std::stringstream ss(line);
        std::string token;

        int lower, upper;
        ss >> lower;
        ss.get();
        ss >> upper;
        ss.get();

        char letter;
        ss.get(letter);
        ss.get();
        ss.get();

        std::string password;
        ss >> password;

        valid += verifyPassword(lower, upper, letter, password);
    }
    fout << valid;
}

int main()
{
    solve();
    return 0;
}
