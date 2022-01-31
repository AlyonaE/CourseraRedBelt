#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
void makeGroups(vector<String>& strings, map<String, vector<int>>& groups) {
	for (int i = 0; i < strings.size(); i++) {
		String locString = strings[i];
		sort(locString.begin(), locString.end());
		locString.erase(unique(locString.begin(), locString.end()), locString.end());
		groups[move(locString)].push_back(i);
	}
}

template <typename String>
vector<Group<String>> getGroupString(vector<String>& strings, map<String, vector<int>>& groups) {
	vector<Group<String>> result;
	for (auto& item : groups) {
		Group<String> loc;
		for (auto& value : item.second) {
			loc.push_back(move(strings[value]));
		}
		result.push_back(move(loc));
	}
	return result;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  // использовав не более 1 копирования каждого символа
	//сформировать map, где ключи - набор символов из слова в алфавитном порядке
	map<String, vector<int>> groups;
	//O(nk)
	makeGroups(strings, groups);
	return getGroupString(strings, groups);	
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}
