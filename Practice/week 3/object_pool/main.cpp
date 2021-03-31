#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
    if (!released.empty()){
      T* tmp_obj = released.front();
      allocated.insert(tmp_obj);
      released.pop();
      return tmp_obj;
    }
    T* tmp_obj = new T;
    objects_with_allocated_memory.push_back(tmp_obj);
    allocated.insert(tmp_obj);
    return tmp_obj;
  };

  T* TryAllocate(){
    if (!released.empty()){
      T* tmp_obj = released.front();
      allocated.insert(tmp_obj);
      released.pop();
      return tmp_obj;
    }
    return nullptr;
  };

  void Deallocate(T* object){
    auto it = allocated.find(object);
    if (it == allocated.end()){
      throw invalid_argument("element not found in set");
    }
    allocated.erase(it);
    released.push(*it);

  };

  ~ObjectPool(){
    allocated.clear();
    while(!released.empty()){
      released.pop();
    }
    for(auto& item : objects_with_allocated_memory){
      delete item;
    }
  };

private:
  multiset<T*> allocated;
  queue<T*> released;
  vector<T*> objects_with_allocated_memory;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}