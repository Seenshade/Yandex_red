#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

#define VALUE(index)                                            \
  if (index+1 <= front_vector.size()){                          \
  return front_vector[front_vector.size() - (index+1)];         \
  } else {                                                      \
  return back_vector[index - front_vector.size()];              \
  }

using namespace std;

template<typename T>
class Deque{
public:
  Deque(){};
  bool Empty() const {
    return front_vector.empty() && back_vector.empty();
  }
  size_t Size() const {
    return front_vector.size()+back_vector.size();
  }
  T& operator[](size_t index){
    VALUE(index)
  }
  const T& operator[](size_t index) const {
    VALUE(index)
  }
  T& At(size_t index){
    if (index >= Size()){
      throw out_of_range("out of range");
    } else {
      VALUE(index)
    }
  }
  const T& At(size_t index) const {
    if (index >= Size()){
      throw out_of_range("out of range");
    } else {
      VALUE(index)
    }
  }
  T& Front(){
    if (front_vector.empty()){
      return back_vector.front();
    }
    return front_vector.back();
  }
  const T& Front() const {
    if (front_vector.empty()){
      return back_vector.front();
    }
    return front_vector.back();
  }
  T& Back(){
    if (back_vector.empty()){
      return front_vector.front();
    }
    return back_vector.back();
  }
  const T& Back() const {
    if (back_vector.empty()){
      return front_vector.front();
    }
    return back_vector.back();
  }
  void PushFront(T value){
    front_vector.push_back(value);
  }
  void PushBack(T value){
    back_vector.push_back(value);
  }

private:
  vector<T> front_vector,back_vector;
};

template<typename T>
ostream& operator<<(ostream& os, const Deque<T>& d){
  bool first = true;
  for (size_t i = 0; i < d.Size();i++){
    if (!first){
      os << ",";
    }
    first = false;
    os << d[i];
  }
  return os;
}

int main() {
  Deque<int> deque_i;
  //cout << deque_i << "\n";
  try {
    cout << "deque.At(47) = " << deque_i.At(47);
  } catch (out_of_range e) {
    cout << "Error: " << e.what() << "\n";
  }
  try {
    cout << "deque.At(3) = " <<deque_i.At(3) << "\n";
  } catch (out_of_range e) {
    cout << "Error: " << e.what() << "\n";
  }
  try {
    cout << "deque.At(0) = " <<deque_i.At(0) << "\n";
  } catch (out_of_range e) {
    cout << "Error: " << e.what() << "\n";
  }
  try {
    cout << "deque.At(1) = " <<deque_i.At(1) << "\n";
  } catch (out_of_range e) {
    cout << "Error: " << e.what() << "\n";
  }
  try {
    cout << "deque.At(6) = " <<deque_i.At(6) << "\n";
  } catch (out_of_range e) {
    cout << "Error: " << e.what() << "\n";
  }
  cout << "deque<int>\n";
  for(std::size_t i = 0; i < 10;i++){
    deque_i.PushFront(i);
  }
  cout << "deque size: " << deque_i.Size() << "\n";
  cout << "deque[0] = " << deque_i[0] << "\n";
  cout << "deque[1] = " << deque_i[1] << "\n";
  cout << "deque.At(0) = " << deque_i.At(0) << "\n";
  cout << "deque.At(1) = " << deque_i.At(1) << "\n";
  cout << "deque size: " << deque_i.Size() << "\n";
  try {
    cout << "deque[15] = " << deque_i.At(15) << "\n";
  } catch (out_of_range e) {
    cout << "exception was received from method At(). Error: " << e.what() << "\n";
  }
  cout << deque_i << "\n";
  cout << "deque.Front() =  " << deque_i.Front() << "\n";
  cout << "deque Back() =  " << deque_i.Back() << "\n";
  cout << "deque.At(9) = " << deque_i.At(9) << "\n";
  try {
    cout << "deque.At(10) = " << deque_i.At(10) << "\n";
  } catch (out_of_range e) {
    cout << "exception was received from method At(). Error: " << e.what() << "\n";
  }

  return 0;
}
