#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

int main() {
	int count;
	std::cin >> count;
	std::list<int> sportsmen;
	std::vector<std::list<int>::iterator> pointers(100001, sportsmen.end());
	for (size_t i = 0; i < count; i++) {
		int num, prev_num;
		std::cin >> num >> prev_num;
		if (pointers[prev_num] == sportsmen.end()) {
			sportsmen.push_back(num);
			pointers[num] = prev(sportsmen.end());
		}
		else {
			sportsmen.insert(pointers[prev_num], num);
			pointers[num] = prev(pointers[prev_num]);
		}
	}

	for (auto item : sportsmen) {
		std::cout << item << "\n";
	}
	return 0;
}