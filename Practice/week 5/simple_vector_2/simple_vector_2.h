#pragma once

#include <cstdlib>
#include <algorithm>

template<typename T>
class SimpleVector {
public:
  SimpleVector() = default;

  explicit SimpleVector(size_t size) {
    data = new T[size];
    capacity = size;
    v_size = size;
  };

  ~SimpleVector() {
    if (capacity > 1) {
      delete[] data;
    } else {
      delete data;
    }
  };

  T &operator[](size_t index) {
    return data[index];
  };

  T *begin() {
    return data;
  };

  T *end() {
    return data + v_size;
  };

  size_t Size() const {
    return v_size;
  };

  size_t Capacity() const {
    return capacity;
  };

  void PushBack(T value) {
    ExpandIfNeeded();
    data[v_size++] = std::move(value);
  }

private:
  void ExpandIfNeeded() {
    if (v_size >= capacity) {
      auto new_cap = capacity == 0 ? 1 : 2 * capacity;
      auto new_data = new T[new_cap];
      std::move(begin(), end(), new_data);
      delete[] data;
      data = new_data;
      capacity = new_cap;
    }
  }

  T *data = nullptr;
  size_t v_size = 0;
  size_t capacity = 0;
};