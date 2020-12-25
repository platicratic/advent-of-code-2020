#include <iostream>
#include <string>
#include <vector>

using namespace std;

class List {
	public:
		List *next;
		int value;

		List(int number, List *next = NULL) {
			this->value = number;
			this->next = next;
		}

		void push_back(int number) {
			this->next = new List(number);
		}
};

List* findDestinationCup(List *currentCup, int label) {
	while (true) {
		label = (label == 1 ? 9 : label - 1);

		List *iteratorL = currentCup;
		do {
			if (iteratorL->value == label) {
				return iteratorL;
			}
			iteratorL = iteratorL->next;
		} 
		while (iteratorL != currentCup);
	}
}

List* findOne(List *cupOne) {
	while (true) {
		if (cupOne->value == 1) {
			return cupOne->next;
		}
		cupOne = cupOne->next;
	}
}

void solve1() {

	// read and create circular list
	string s;  getline(cin, s);

	List currentL(s[0] - '0');
	List *iteratorL = &currentL;

	for (char c : s.substr(1)) {
		iteratorL->push_back(c - '0');
		iteratorL = iteratorL->next;
	}
	iteratorL->next = &currentL;


	// crab moves

	List *currentCup = &currentL;
	for (int i = 0; i < 100; i ++) {
		// crab action 1
		List *threeBegin = currentCup->next, *threeEnd = currentCup->next->next->next;
		currentCup->next = threeEnd->next;

		// crab action 2
		int label = currentCup->value;
		List *destionationCup = findDestinationCup(currentCup, label);

		// crab action 3
		threeEnd->next = destionationCup->next;
		destionationCup->next = threeBegin;

		// crab action 4
		currentCup = currentCup->next;
	}

	List *cupOne = findOne(currentCup);
	
	while (cupOne->value != 1) {
		cout << cupOne->value;
		cupOne = cupOne->next;
	}
	cout << '\n';
}

List* findDestinationCup2(vector<List*> &destination, int label, List* threeBegin) {
	while (true) {
		label = (label == 1 ? 1000000 : label - 1);
		if (label != threeBegin->value && label != threeBegin->next->value && label != threeBegin->next->next->value) {
			return destination[label];
		}
	}
}

void solve2() {

	// read and create circular list
	string s; getline(cin, s);

	vector<List*> destination(1000001);

	List currentL(s[0] - '0');
	List *iteratorL = &currentL;
	destination[iteratorL->value] = iteratorL;

	for (char c : s.substr(1)) {
		iteratorL->push_back(c - '0');
		iteratorL = iteratorL->next;
		destination[iteratorL->value] = iteratorL;
	}
	for (int i = 10; i <= 1000000; i ++) {
		iteratorL->push_back(i);
		iteratorL = iteratorL->next;
		destination[iteratorL->value] = iteratorL;
	}
	iteratorL->next = &currentL;

	// crab moves

	List *currentCup = &currentL;
	for (int i = 0; i < 10000000; i++) {
		// crab action 1
		List *threeBegin = currentCup->next, *threeEnd = currentCup->next->next->next;
		currentCup->next = threeEnd->next;

		// crab action 2
		int label = currentCup->value;
		List *destionationCup = findDestinationCup2(destination, label, threeBegin);

		// crab action 3
		threeEnd->next = destionationCup->next;
		destionationCup->next = threeBegin;

		// crab action 4
		currentCup = currentCup->next;
	}

	List *cupOne = findOne(currentCup);
	cout << 1LL * cupOne->value * cupOne->next->value << '\n';
}

int main() {
	//solve1();
	solve2();
	return 0;
}
