#include <iostream>
#include <fstream>
#include <string>

std::ifstream fin("input.in");


/* Part 1 */

long long eval(std::string &, int &);

long long priorities(std::string &line, int &pos) {
	long long number = 0;
	if (line[pos] == '(') {
		pos ++;
		number = eval(line, pos);
		pos ++;
	}
	else {
		while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9') {
			number = number * 10 + line[pos] - '0';
			pos ++;
		}
		pos ++;
	}
	return number;
}

long long eval(std::string &line, int &pos) {
	long long number = priorities(line, pos);
	while (pos < line.size() && (line[pos] == '*' || line[pos] == '+')) {
		if (line[pos] == '+') {
			pos += 2;
			number += priorities(line, pos);
		}
		else if (line[pos] == '*') {
			pos += 2;
			number *= priorities(line, pos);
		}
	}
	return number;
}

void solve1() {
	long long sol = 0;
	std::string line;
	while (std::getline(fin, line)) {
		int pos = 0;
		sol += eval(line, pos);
	}
	std::cout << sol << '\n';
}

/* Part 2 */

long long multiplication(std::string &, int &);

long long parenthesesOrNumber(std::string &line, int &pos) {
	long long number = 0;
	if (line[pos] == '(') {
		pos++;
		number = multiplication(line, pos);
		pos++;
	}
	else {
		while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9') {
			number = number * 10 + line[pos] - '0';
			pos++;
		}
		pos++;
	}
	return number;
}

long long addition(std::string &line, int &pos) {
	long long number = parenthesesOrNumber(line, pos);
	while (pos < line.size() && line[pos] == '+') {
		pos += 2;
		number += parenthesesOrNumber(line, pos);
	}
	return number;
}

long long multiplication(std::string &line, int &pos) {
	long long number = addition(line, pos);
	while (pos < line.size() && line[pos] == '*') {
		pos += 2;
		number *= addition(line, pos);
	}
	return number;
}

void solve2() {
	long long sol = 0;
	std::string line;
	while (std::getline(fin, line)) {
		int pos = 0;
		sol += multiplication(line, pos);
	}
	std::cout << sol << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}