#include "test_runner.h"
#include <string>
#include <deque>
#include <map>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target){
    const string_view source_view = GetDictionaryPointer(source);
    const string_view target_view = GetDictionaryPointer(target);
    forward[source_view] = target_view;
    backward[target_view] = source_view;
  };

  string_view TranslateForward(string_view source) const{
    auto it = forward.find(source);
    if (it != forward.end()){
      return it->second;
    }
    return {};
  };

  string_view TranslateBackward(string_view target) const{
    auto it = backward.find(target);
    if (it != backward.end()){
      return it->second;
    }
    return {};
  };

private:
  string_view GetDictionaryPointer(string_view sv){
    for(const auto* map_ptr : {&forward, &backward}){
      auto it = map_ptr->find(sv);
      if (it != map_ptr->end()){
        return it->first;
      }
    }
    return string_base.emplace_back(sv);
  }

  deque<string> string_base;
  map<string_view, string_view> forward, backward;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}