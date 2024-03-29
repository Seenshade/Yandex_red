#include <string>
#include "profile.h"
#include "string_view"
#include "test_runner.h"
#include "list"

using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
  {
    cursor = editor.begin();
  }

  void Left(){
    if (cursor != editor.begin()){
      --cursor;
    }
  }

  void Right(){
    if (cursor != editor.end()){
      ++cursor;
    }
  }

  void Insert(char token){
    editor.insert(cursor, token);
  }

  void Cut(size_t tokens = 1){
    if (tokens == 0){
      buffer.clear();
    } else {
      buffer.reserve(tokens);
      while(tokens > 0 && cursor != editor.end()){
        auto to_remove = cursor++;
        buffer.push_back(*to_remove);
        editor.erase(to_remove);
        tokens--;
      }
    }
  }

  void Copy(size_t tokens = 1){
    if (tokens == 0){
      buffer.clear();
    } else {
      buffer.reserve(tokens);
      buffer.insert(buffer.begin() ,cursor, next(cursor, tokens));
    }
  }

  void Paste(){
    for(auto item : buffer){
      editor.insert(cursor,item);
    }

  }

  string GetText() const{
    return string(editor.begin(), editor.end());
  };

private:
  string buffer;
  list<char>::iterator cursor;
  list<char> editor;
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