#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class HotelManager {
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {  // Суммарно: O(log(Q))
    current_time_ = time; // O(1)
    hotels_[hotel_name].Book({time, client_id, room_count}); // O(log(Q))
  }
  int ComputeClientCount(const string& hotel_name) {  // Суммарно: O(log(Q) + log(C))
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_); // Суммарно: O(log(Q)+log(C))
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) { // Суммарно: O(log(C))
      last_bookings_.push(booking); // O(1)
      room_count_ += booking.room_count;  // O(1)
      ++client_booking_counts_[booking.client_id];  // O(log(C))
    }
    int ComputeClientCount(int64_t current_time) {  // Суммарно: O(log(C))
      RemoveOldBookings(current_time);  // O(log(C))
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {  // Суммарно: O(log(C))
      RemoveOldBookings(current_time);  // O(log(C))
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() { // Суммарно: O(log(C))
      const Booking& booking = last_bookings_.front();  // O(1)
      room_count_ -= booking.room_count;  // O(1)
      const auto client_stat_it =
        client_booking_counts_.find(booking.client_id); // O(log(C))
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it); // O(log(C))
      }
      last_bookings_.pop(); // O(1)
    }
    void RemoveOldBookings(int64_t current_time) {  // Суммарно: O(log(C))
      while (
        !last_bookings_.empty()
        && last_bookings_.front().time
           <= current_time - TIME_WINDOW_SIZE
        ) {
        PopBooking(); //O(log(C))
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      int client_id, room_count;
      cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);  // Суммарно: O(log(C))
    } else {
      string hotel_name;
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.ComputeClientCount(hotel_name) << "\n"; // Суммарно: O(log(L))
      } else if (query_type == "ROOMS") {
        cout << manager.ComputeRoomCount(hotel_name) << "\n"; // Суммарно: O(log(L))
      }
    }
  }

  return 0;
}
