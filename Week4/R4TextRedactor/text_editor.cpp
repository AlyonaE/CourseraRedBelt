#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
     Editor() {
         _data = {};
         _coursor = _data.begin();
  }
     void Left() {
         if (_coursor != _data.begin()) {
             _coursor--;
         }
  }
     void Right() {
         if (_coursor != _data.end()) {
             _coursor++;
         }
  }
     void Insert(char token) {
         _data.insert(_coursor, token);
         if (_coursor != _data.end()) {
             next(_coursor);
         }
         else {
             _coursor = _data.end();
         }


  }
     void Cut(size_t tokens = 1) {
         auto it = _copyToBuffer(tokens);
         _data.erase(_coursor, it);
         _coursor = it;
  }
     void Copy(size_t tokens = 1) {
         auto it = _copyToBuffer(tokens);
         _coursor = it;
  }
     void Paste() {
         auto buf_it = _buffer.begin();
         while (buf_it != _buffer.end()) {
             Insert(*buf_it++);
         }
  }
     string GetText() const {
         string res(_data.begin(), _data.end());
         return res;
  }
private:
    list<char> _data;
    list<char>::iterator _coursor;
    list<char> _buffer;

    list<char>::iterator _copyToBuffer(size_t tokens) {
        _buffer.clear();
        auto it = _coursor;
        size_t i = 0;
        while (i < tokens) {
            if (it == _data.end()) {
                break;
            }
            _buffer.push_back(*it);
            it++;
            i++;
        }
        return it;
    }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}