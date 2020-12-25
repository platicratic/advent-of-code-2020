#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

ifstream fin("input.in");

void readPlayerCards(queue<int> &player) {
	string line;
	getline(fin, line);
	getline(fin, line);
	while (line != "") {
		int card = stoi(line, size_t());
		player.push(card);
		getline(fin, line);
	}
}

void playBetivani(queue<int> &player1, queue<int> &player2) {
	while (!player1.empty() && !player2.empty()) {
		int card1 = player1.front(); player1.pop();
		int card2 = player2.front(); player2.pop();
		if (card1 > card2) {
			player1.push(card1);
			player1.push(card2);
		}
		else {
			player2.push(card2);
			player2.push(card1);
		}
	}
}

void writeSolution(queue<int> player) {
	long long sol = 0, size = player.size();
	while (size > 0) {
		sol = sol + size * player.front();
		player.pop();
		size --;
 	}
	cout << sol << '\n';
}

void solve1() {
	queue<int> Q1, Q2;

	readPlayerCards(Q1);
	readPlayerCards(Q2);
	
	playBetivani(Q1, Q2);
	
	writeSolution((Q1.size() > 0 ? Q1 : Q2));
}

void readPlayerCards(deque<int> &player) {
	string line;
	getline(fin, line);
	getline(fin, line);
	while (line != "") {
		int card = stoi(line, size_t());
		player.push_back(card);
		getline(fin, line);
	}
}

inline void round(deque<int> &player, int cardA, int cardB) {
	player.push_back(cardA);
	player.push_back(cardB);
}

inline string createHash(deque<int> &player1, deque<int> &player2) {
	string h = "";
	for (auto it : player1) h = h + to_string(it) + ',';
	h += "x";
	for (auto it : player2) h = h + to_string(it) + ',';
	return h;
}

bool playRecursiveCombat(deque<int> &player1, deque<int> &player2) {
	unordered_set<string> H;

	while (!player1.empty() && !player2.empty()) {
		string h = createHash(player1, player2);
		if (H.find(h) != H.end()) {
			return true;
		}
		H.insert(h);

		int card1 = player1.front();
		player1.pop_front();
		int card2 = player2.front(); 
		player2.pop_front();

		if (card1 <= player1.size() && card2 <= player2.size()) {
			deque<int> newPlayer1(player1.begin(), player1.begin() + card1);
			deque<int> newPlayer2(player2.begin(), player2.begin() + card2);
			
			(playRecursiveCombat(newPlayer1, newPlayer2) ? round(player1, card1, card2) : round(player2, card2, card1));
		}
		else {
			(card1 > card2 ? round(player1, card1, card2) : round(player2, card2, card1));
		}
	}
	return player2.empty();
}

void writeSolution(deque<int> &player) {
	long long sol = 0, size = player.size();
	while (size > 0) {
		sol = sol + size * player.front();
		player.pop_front();
		size--;
	}
	cout << sol << '\n';
}

void solve2() {
	deque<int> D1, D2;

	readPlayerCards(D1);
	readPlayerCards(D2);

	writeSolution((playRecursiveCombat(D1, D2) ? D1 : D2));
}

int main() {
	//solve1();
	solve2();
	return 0;
}