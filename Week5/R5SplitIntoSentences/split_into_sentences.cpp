#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> result;
    Sentence<Token> sentence;
    auto it = tokens.begin();
    while (it != tokens.end()) {
        //in the end of sentence might be several punctuations 
        if (it->IsEndSentencePunctuation()) {
            do {
                sentence.push_back(move(*it));
                it++;
            } while ((it != tokens.end()) && it->IsEndSentencePunctuation());
            result.push_back(move(sentence));
        }
        if (it != tokens.end()) {
            sentence.push_back(move(*it));
            it++;
        }

    }
    if (!sentence.empty()) {
        result.push_back(move(sentence));
    }

    return result;
}


struct TestToken {
    //TestToken(const string& s) : data(s) {};
    //TestToken(const string& s, const bool& is) : data(s), is_end_sentence_punctuation(is) {};
    //TestToken(const TestToken& other): data(other.data), is_end_sentence_punctuation(other.is_end_sentence_punctuation) {
    //    cout << "Copy cnst" << endl;
    //}

    //TestToken(TestToken&& other) : data(move(other.data)), is_end_sentence_punctuation(move(other.is_end_sentence_punctuation)) {
    //    cout << "Move cnst" << endl;
    //};

    //void operator=(const TestToken& other) {
    //    this->data = other.data;
    //    this->is_end_sentence_punctuation = other.is_end_sentence_punctuation;
    //    cout << "Copy assighnment" << endl;
    //}
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}


// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
