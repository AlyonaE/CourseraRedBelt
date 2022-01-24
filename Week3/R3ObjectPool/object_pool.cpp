#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		if (!_free_objects.empty()) {
			T* loc = _free_objects.front();
			_existing_objects.insert(loc);
			_free_objects.pop_front();
			return loc;
		}
		else {
			T* loc = new T;
			_existing_objects.insert(loc);
			return loc;
		}
  }
	T* TryAllocate() {
		if (_free_objects.empty()) {
			return nullptr;
		}
		else {
			return Allocate();
		}
  }

	void Deallocate(T* object) {
		if (_existing_objects.find(object) == _existing_objects.end()) {
			throw invalid_argument("Object does not exist");
		}
		else {
			_free_objects.push_back(object);
			_existing_objects.erase(object);
		}
  }

	~ObjectPool() {
		for (auto& item : _free_objects) {
			delete item;
		}
		for (auto& item : _existing_objects) {
			delete item;
		}
  }

private:
	deque<T*> _free_objects;
	set<T*> _existing_objects;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
