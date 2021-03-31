#include "test_runner.h"

#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Table{
public:
  Table(size_t rows, size_t columns){
    if (rows == 0 || columns == 0){
      rows = 0;
      columns = 0;
    }
    table.resize(rows);
    for(auto& item : table){
      item.resize(columns);
    }
    _rows = rows;
    _columns = columns;
  }

  vector<T>& operator[](size_t index){
    return table[index];
  }

  vector<T> operator[](size_t index) const {
    return table[index];
  }

  void Resize(size_t rows, size_t columns){
    if (rows == 0 || columns == 0){
      rows = 0;
      columns = 0;
    }
    table.resize(rows);
    for (auto& item : table){
      item.resize(columns);
    }
    _rows = rows;
    _columns = columns;
  }

  pair<size_t, size_t> Size() const {
    return {_rows, _columns};
  }
private:
  vector<vector<T>> table;
  size_t _rows, _columns;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}