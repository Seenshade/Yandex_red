#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
    : user_page_counts_(1001, 0),
      users(MAX_USER_COUNT_+1, 0) {}

  void Read(int user_id, int page_count) {
    if (users[user_id] == 0){
      users[user_id] = page_count;
      user_page_counts_[page_count]++;
      USER_COUNT_CURRENT++;
    } else {
      user_page_counts_[users[user_id]]--;
      users[user_id] = page_count;
      user_page_counts_[page_count]++;
    }
  }

  double Cheer(int user_id) const {
    if (users[user_id] == 0) {
      return 0;
    }
    if (USER_COUNT_CURRENT == 1) {
      return 1;
    }
    int sum = 0;
    for (int i = 1; i < users.at(user_id);i++){
      sum += user_page_counts_[i];
    }
    return (sum * 1.0 / (USER_COUNT_CURRENT-1));
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  int USER_COUNT_CURRENT = 0;

  vector<int> users;
  vector<int> user_page_counts_;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}