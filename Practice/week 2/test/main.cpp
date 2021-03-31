#include <iostream>
#include <future>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  vector<future<void>> f;
  for (int i = 0; i < 10; ++i) {
    f.push_back(async([&v, i] { v.push_back(i); }));
  }
}