// Part Two

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <functional>

using namespace std;

ifstream fin("input.in");

inline bool checkMe(std::string value, int length, int a, int b) {
    if (value.size() == length) {
        int number = std::stoi(value, std::size_t());
        if (a <= number && number <= b) {
            return true;
        }
    }
    return false;
}

inline int check1(std::string value) {
    return (checkMe(value, 4, 1920, 2002) ? 1 : 0);
}

inline int check2(std::string value) {
    return (checkMe(value, 4, 2010, 2020) ? 2 : 0);
}

inline int check4(std::string value) {
    return (checkMe(value, 4, 2020, 2030) ? 4 : 0);
}

inline int check8(std::string value) {
    if (value.size() > 3) {
        int left, right;
        if (value[value.size() - 2] == 'c' && value[value.size() - 1] == 'm') {
            left = 150;
            right = 193;
        } else if (value[value.size() - 2] == 'i' && value[value.size() - 1] == 'n') {
            left = 59;
            right = 76;
        } else {
            return 0;
        }
        value.erase(value.size() - 2);
        int height = std::stoi(value, std::size_t());
        if (left <= height && height <= right) {
            return 8;
        }
    }
    return 0;
}

inline int check16(std::string value) {
    if (value.size() == 7 && value[0] == '#') {
        for (int i = 1; i < 7; i ++) {
            if (!(('0' <= value[i] && value[i] <= '9') || ('a' <= value[i] && value[i] <= 'f'))) {
               return 0;
            }
        }
    } else {
        return 0;
    }
    return 16;
}

inline int check32(std::string value) {
    return (value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth" ? 32 : 0);
}

inline int check64(std::string value) {
    if (value.size() == 9) {
        for (int i = 0; i < 9; i ++) {
            if (!('0' <= value[i] && value[i] <= '9')) {
                return 0;
            }
        }
    } else {
        return 0;
    }
    return 64;
}

inline int check128(std::string value) {
    return 0;
}

std::map<std::string, std::function<int (std::string)>> M = {
    { "byr", check1 },
    { "iyr", check2 },
    { "eyr", check4 },
    { "hgt", check8 },
    { "hcl", check16 },
    { "ecl", check32 },
    { "pid", check64 },
    { "cid", check128 }
};

void solve() {
    std::string line, key, value;
    int sol = 0, nr = 0;

    while (getline(fin, line)) {
        std::stringstream ss(line);
        if (line.size() == 0) {
            if (nr == 127) {
                sol ++;
            }
            nr = 0;
        } else {
            while (getline(ss, key, ':') && getline(ss, value, ' ')) {
                nr += M[key](value);
            }
        }
    }

    cout << sol << '\n';
}

int main()
{
    solve();
    return 0;
}
