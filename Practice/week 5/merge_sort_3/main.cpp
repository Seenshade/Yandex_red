#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
  if (range_end - range_begin < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin),
                            make_move_iterator(range_end));
  MergeSort(make_move_iterator(elements.begin()), make_move_iterator(elements.begin() + elements.size() / 3));
  MergeSort(make_move_iterator(elements.begin() + elements.size() / 3 + 1), make_move_iterator(elements.begin() + elements.size() * 2 / 3));
  MergeSort(make_move_iterator(elements.begin() + elements.size() * 2 / 3 + 1), make_move_iterator(elements.begin() + elements.size()));
  vector<RandomIt> tmp(elements.size() * 2 / 3);
  merge(make_move_iterator(elements.begin()), make_move_iterator(elements.begin() + elements.size() / 3),
        make_move_iterator(elements.begin() + elements.size() / 3 + 1), make_move_iterator(elements.begin() + elements.size() * 2 / 3),
        back_inserter(tmp));
  merge(tmp.begin(), tmp.end(),
        make_move_iterator(elements.begin() + elements.size() * 2 / 3 + 1),  make_move_iterator(elements.begin() + elements.size()),
        back_inserter(elements));
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
