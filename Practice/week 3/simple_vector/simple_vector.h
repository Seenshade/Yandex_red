#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector(){
    data = nullptr;
    capacity = 0;
    v_size = 0;
  };
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