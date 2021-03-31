#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
  SimpleVector(){
    data = nullptr;
    capacity = 0;
    v_size = 0;
  };

  SimpleVector(const SimpleVector& other)
  : data(new T[other.Capacity()]),
    capacity(other.Capacity()),
    v_size(other.Size())
  {
    std::copy(other.begin(), other.end(), data);
  }

  void operator=(const SimpleVector& other){
    if (v_size >= other.v_size){
      std::copy(other.begin(), other.end(), begin());
      v_size = other.v_size;
    } else {
      SimpleVector<T> tmp(other);
      std::swap(tmp.data, data);
      std::swap(tmp.v_size, v_size);
      std::swap(tmp.capacity, capacity);
    }
  }

  explicit SimpleVector(size_t size){
    data = new T[size];
    capacity = size;
    v_size = size;
  };
  ~SimpleVector(){
    if (capacity > 1){
      delete[] data;
    } else {
      delete data;
    }
  };

  T& operator[](size_t index){
    return data[index];
  };

  T* begin(){
    return data;
  };
  T* end(){
    return data + v_size;
  };

  const T* begin() const {
    return data;
  };
  const T* end() const {
    return data + v_size;
  };

  size_t Size() const{
    return v_size;
  };
  size_t Capacity() const{
    return capacity;
  };
  void PushBack(const T& value){
    if (data == nullptr){
      data = new T(value);
      capacity = 1;
    } else {
      if (v_size == capacity){
        ReAllocate(2*capacity);
      }
    }
    data[v_size] = value;
    v_size++;
  };

private:
  void ReAllocate(size_t new_capacity){
    T* newData = new T[2*capacity];
    if (capacity > 1){
      for(size_t i = 0; i < v_size; i++){
        newData[i] = data[i];
      }
      delete[] data;
    } else {
      *newData = *data;
      delete data;
    }
    capacity = new_capacity;
    data = newData;
  }

  T* data;
  size_t v_size, capacity;
};