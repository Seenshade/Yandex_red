#pragma once

#include <string>
#include <vector>
#include "set"

using namespace std;

class Learner {
private:
  vector<string> dict;
  set<string> uniq_dict;
public:
  int Learn(const vector<string>& words);
  vector<string> KnownWords();
};