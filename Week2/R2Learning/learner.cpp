#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "profile.h"
#include <set>

using namespace std;

class Learner {
 private:
  set<string> dict_set;

 public:
  int Learn(const vector<string>& words) {
      int old_size = dict_set.size();
      dict_set.insert(words.begin(), words.end());
      return dict_set.size() - old_size;
  }

  vector<string> KnownWords() {
      vector<string> result;
      copy(dict_set.begin(), dict_set.end(), back_inserter(result));
      return result;
  }
};


//int main() {
//    Learner learner;
//    vector<string> base_values;
//    for (size_t i = 0; i < 1000; i++) {
//        int item = 1000 - i;
//        base_values.push_back(to_string(item));
//    }
//    vector<string> new_portion_all_in;
//    for (size_t i = 0; i < 50; i++) {
//        int item = rand() % 1000;
//        new_portion_all_in.push_back(to_string(item));
//    }
//    {
//        LOG_DURATION("BASE")
//        cout << "1:  Learn "<< learner.Learn(base_values) << " new words" << endl;
//        cout << "1: There are " << learner.KnownWords().size() << " known words" << endl;
//    }
//    {
//        LOG_DURATION("ALL_IN_LEARN")
//        cout << "2: Learn " << learner.Learn(new_portion_all_in) << " new words" << endl;
//    }
//    {
//        LOG_DURATION("ALL_IN_KNOWN_WORDS")
//        cout << "2: There are " << learner.KnownWords().size() << " known words" << endl;
//    }
//    vector<string> new_portion_rand;
//    for (size_t i = 0; i < 50; i++) {
//        int item = rand() % 2000;
//        new_portion_all_in.push_back(to_string(item));
//    }
//    {
//        LOG_DURATION("RAND_LEARN")
//        cout << "3: Learn " << learner.Learn(new_portion_all_in) << " new words" << endl;
//    }
//    {
//        LOG_DURATION("RAND_KNOWN_WORDS")
//        cout << "3: There are " << learner.KnownWords().size() << " known words" << endl;
//    }
//
//}