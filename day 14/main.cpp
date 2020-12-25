#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

std::ifstream fin("input.in");

long long calculateResult(long long value, std::string &mask) {
	long long bit = 1;
	for (int i = mask.size() - 1; i >= 0; i --) {
		if (mask[i] == '0') {
			value &= ((1LL << 36) - 1 - bit);
		} 
		else if (mask[i] == '1') {
			value |= bit;
		}
		bit *= 2;
	}
	return value;
}

void solve1() {
	std::map<int, long long> M;
	std::string line, mask;
	while (std::getline(fin, line)) {
		if (line[1] == 'a') {
			mask = line.substr(7);
		}
		else {
			long long key, value;
			std::stringstream ss(line);
			std::getline(ss, line, '[');
			ss >> key;
			std::getline(ss, line, '=');
			ss >> value;
			M[key] = calculateResult(value, mask);
		}
	}
	long long sol = 0;
	for (auto it : M) {
		sol += it.second;
	}
	std::cout << sol << '\n';
}

std::string calculateAddress(long long key, std::string &mask) {
	std::string address = "";
	for (int i = mask.size() - 1; i >= 0; i --) {
		if (mask[i] == '0') {
			address += (key % 2 == 0 ? '0' : '1');
		}
		else {
			address += mask[i];
		}
		key /= 2;
	}
	return address;
}

void addAddresses(std::string &address, int i, long long bit, long long key, long long &value, std::map<long long, long long> &M) {
	if (i < 36) {
		if (address[i] == '0') {
			addAddresses(address, i + 1, bit * 2, key, value, M);
		}
		else if (address[i] == '1') {
			addAddresses(address, i + 1, bit * 2, key + bit, value, M);
		}
		else {
			addAddresses(address, i + 1, bit * 2, key, value, M);
			addAddresses(address, i + 1, bit * 2, key + bit, value, M);
		}
	}
	else {
		M[key] = value;
	}
}

void solve2() {
	std::map<long long, long long> M;
	std::string line, mask;
	while (std::getline(fin, line)) {
		if (line[1] == 'a') {
			mask = line.substr(7);
		}
		else {
			long long key, value;
			std::stringstream ss(line);
			std::getline(ss, line, '[');
			ss >> key;
			std::getline(ss, line, '=');
			ss >> value;
			std::string address = calculateAddress(key, mask);
			addAddresses(address, 0, 1, 0, value, M);
		}
	}

	long long sol = 0;
	for (auto it : M) {
		sol += it.second;
	}
	std::cout << sol << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}