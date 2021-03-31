#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <future>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
    for(const auto& [key, value] : other.word_frequences){
      word_frequences[key] += value;
    }
  };
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats stats;
  string_view sv(line);
  while(sv.size() != 0){
    size_t f_pos = sv.find(" ");
    auto it = key_words.find(string(sv.substr(0, f_pos)));
    if (it != key_words.end()){
      stats.word_frequences[*it]++;
    }
    if (f_pos == sv.npos){
      break;
    }
    sv.remove_prefix(f_pos+1);
  }
  return stats;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  Stats stats;
  vector<future<Stats>> futures;
  string tmp;
  for (string line; getline(input, line); ) {
    tmp += ' ' + line;
  }
  tmp.erase(tmp.size(), 1);
  for (auto it = key_words.begin(); it != key_words.end(); )
  for (size_t i = 0; i < tmp.length(); i+=tmp.length()*0.25+1) {
    futures.push_back(async(ExploreLine, ref(key_words), tmp.substr(i, tmp.length()/4)));
  }
  for(auto& items : futures){
    stats += items.get();
  }
  return stats;
}

void TestBasicSingleThread() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWordsSingleThread(key_words, ss);
  const map<string, int> expected = {
          {"yangle", 6},
          {"rocks", 2},
          {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestBasicSingleThread);
}