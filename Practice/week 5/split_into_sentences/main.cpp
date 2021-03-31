#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = vector<Token>;

struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }

  bool operator==(const TestToken &other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  // Напишите реализацию функции, не копируя объекты типа Token
  vector<Sentence<Token>> res;
  Sentence<Token> sentence;
  bool end_find = false;
  size_t count = 0;
  for (Token &item : tokens) {
    count++;
    if (end_find && !item.IsEndSentencePunctuation()){
      res.push_back(move(sentence));
      sentence.push_back(move(item));
      end_find = false;
      continue;
    } else if(!end_find && item.IsEndSentencePunctuation()){
      end_find = true;
    }
    sentence.push_back(move(item));
  }
  if (!sentence.empty()){
    res.push_back(move(sentence));
  }
  return res;
}


ostream &operator<<(ostream &stream, const TestToken &token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!"}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true},
                                          {"!", true},
                                          {"Without"},
                                          {"copies"},
                                          {".", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"},   {"into"},   {"sentences"}, {"!", true}, {"!", true}},
                                  {{"Without"}, {"copies"}, {".", true}},
                                })
  );

  ASSERT_EQUAL(

    SplitIntoSentences(vector<TestToken>({{"Split", true}, {"into", true}, {"sentences", true}, {"!"}})),

    vector<Sentence<TestToken>>({

                                  {{"Split", true}, {"into", true}, {"sentences", true},},

                                  {{"!"}}

                                })

  );
}



void TestNoCopyableSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!"}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true},
                                          {"!", true},
                                          {"Without"},
                                          {"copies"},
                                          {".", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"},   {"into"},   {"sentences"}, {"!", true}, {"!", true}},
                                  {{"Without"}, {"copies"}, {".", true}},
                                })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
