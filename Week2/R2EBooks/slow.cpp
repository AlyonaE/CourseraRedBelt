#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
//#include "test_runner.h"
//#include "old_slow.h"


using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : _users_on_page(MAX_PAGES_COUNT_  + 1, set<int>()) {}

  void Read(int user_id, int page_count) {
    //если такого user'a ещё нет, его надо добавить
      if (_users.find(user_id) == _users.end()) {
          _users[user_id] = page_count; //logQ
          _users_on_page[page_count].insert(user_id);//logQ
      }
      else {
          int prev_page = _users.at(user_id);
          _users[user_id] = page_count;
          auto it = _users_on_page[prev_page].find(user_id);
          _users_on_page[prev_page].erase(it);
          _users_on_page[page_count].insert(user_id); //logQ
      }
  }

  double Cheer(int user_id) const {
    if (_users.find(user_id) == _users.end()) {
      return 0.0;
    }
    int page = _users.at(user_id);
    int user_count = _users.size() - 1; //except self
    if (user_count == 0) {
        return 1.0;
    }
    int cur_users;
    if (page > _MIDDLE_OF_PAGES) {
        cur_users = -1;
        for (int i = page; i < MAX_PAGES_COUNT_; i++) {
            cur_users += _users_on_page[i].size();
            if (cur_users >= user_count) {
                break;
            }
        }
        return (1 - (1.0 * cur_users) / (user_count));
    }
    else {
        cur_users = 0;
        for (int i = page - 1; i >= 0; i--) {
            cur_users += _users_on_page[i].size();
            if (cur_users >= user_count) {
                break;
            }
        }
        return 1.0 * cur_users / user_count;
    }
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_PAGES_COUNT_ = 1001;
  static const int _MIDDLE_OF_PAGES = 500;

  vector<set<int>> _users_on_page;
  map<int, int> _users;

};

//void TestonlyOneUser()
//{
//    {
//        ReadingManager manager;
//        manager.Read(4, 5);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0);
//        manager.Read(4, 6);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0);
//        manager.Read(4, 100);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0);
//        ASSERT_EQUAL(manager.Cheer(3), 0.0);
//        ASSERT_EQUAL(manager.Cheer(5), 0.0);
//    }
//
//}
//void TestCheer()
//{
//    {
//        ReadingManager manager;
//        manager.Read(1, 1);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0);
//        ASSERT_EQUAL(manager.Cheer(2), 0);
//    }
//
//}
//void TestBetterThanThird() {
//    {// better than third
//        ReadingManager manager;
//        manager.Read(1, 1);
//        manager.Read(2, 2);
//        manager.Read(3, 3);
//        ASSERT_EQUAL(manager.Cheer(2), 0.5);
//        manager.Read(4, 4);
//        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
//    }
//
//}
//
//void TestRandomCompareOld() {
//    ReadingManager manager;
//    ReadingManagerOld manager_old;
//    map<int, int> pages_increase;
//    srand(14);
//
//    int query_count = 100;
//    for (int i = 0; i < query_count; i++) {
//        int query_type = rand() % 2;
//        int user_id;
//        do {
//            user_id = rand() % 10;
//        } while ((pages_increase.find(user_id) != pages_increase.end()) && (pages_increase.at(user_id) >= 999));
//            
//        if (query_type == 0) { //READ
//            int page = rand() % 100;
//            int new_page = min(pages_increase[user_id] + page, 1000);           
//            pages_increase[user_id] = new_page;
//            cout << i << ": Read " << user_id << " " << pages_increase[user_id] << endl;
//            manager.Read(user_id, new_page);
//            manager_old.Read(user_id, new_page);
//        }
//        else {
//            cout << i << ": Cheer " << user_id << endl;
//            ASSERT_EQUAL(manager.Cheer(user_id), manager_old.Cheer(user_id));
//        }
//    }
//}

int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //TestRunner tr;
  //RUN_TEST(tr, TestonlyOneUser);
  //RUN_TEST(tr, TestCheer);
  //RUN_TEST(tr, TestBetterThanThird);
  //RUN_TEST(tr, TestRandomCompareOld);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}