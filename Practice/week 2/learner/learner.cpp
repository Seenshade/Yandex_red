#include "learner.h"

#include <string>
#include <vector>

using namespace std;

int Learner::Learn(const vector<string> &words) {
  int last_size = uniq_dict.size();
  for (const auto& word : words) {
    uniq_dict.insert(word);
  }
  return uniq_dict.size() - last_size;
}
vector<string> Learner::KnownWords() {
  for(const auto& word : uniq_dict){
    dict.push_back(word);
  }
  return dict;
}