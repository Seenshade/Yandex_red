#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  list<int> athletes;
  vector<list<int>::iterator> athletes_refs(100000, athletes.end());
  int query;
  cin >> query;
  while(query > 0){
    int new_athlete, after_athlete;
    cin >> new_athlete >> after_athlete;
    if (athletes_refs[after_athlete] == athletes.end()){
      athletes.push_back(new_athlete);
      athletes_refs[new_athlete] = prev(athletes.end());
    } else {
      athletes.insert(athletes_refs[after_athlete], new_athlete);
      athletes_refs[new_athlete] = prev(athletes_refs[after_athlete]);
    }
    query--;
  }
  for(const auto& item : athletes){
    cout << item << "\n";
  }
  return 0;
}
