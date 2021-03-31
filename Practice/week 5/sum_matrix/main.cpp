#include "test_runner.h"

#include <future>
#include <numeric>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
          : first(begin)
          , last(end)
          , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template<typename Matr>
int64_t SumThread(const Matr& matrix){
  int64_t sum = 0;
  for(const auto& row : matrix){
    for(auto item : row){
      sum += item;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  int64_t res = 0;
  size_t strings_for_thread = matrix.size() * 0.25;
  vector<future<int64_t>> futures;
  for (const auto& page : Paginate(matrix, strings_for_thread)) {
    futures.push_back(async([&page] { return SumThread(page); }));
  }
  for (auto &item : futures) {
    res += item.get();
  }
  return res;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
          {1, 2, 3, 4},
          {5, 6, 7, 8},
          {9, 10, 11, 12},
          {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestCalculateMatrixSum2() {
  const vector<vector<int>> matrix = {
          {1, 2, 3, 4},
          {5, 6, 7, 8},
          {9, 10, 11, 12},
          {13, 14, 15, 16},
          {17, 18, 19, 20},
          {21, 22, 23, 24},
          {25, 26, 27, 28},
          {29, 30, 31, 32}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 528);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
  RUN_TEST(tr, TestCalculateMatrixSum2);
  return 0;
}