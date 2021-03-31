#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Reserve{
  string hotel_name;
  int room_count;
  int32_t client_id;
  int64_t time;
};

class HotelManager{
public:
  HotelManager() = default;

  //Находим отель, возвращаем количество клиентов этого отеля
  //поиск отеля:                 log(количество отелей)
  //количество клиентов отеля:   O(1)
  //Итого:                       log(количество отелей)
  uint32_t Clients(const string& hotel_name) {
    while (booking.size() > 1 && booking.front().time <= booking.back().time - 86400){ //проверка на выход брони из интерсующего интервала времени
      DeleteClient(booking.front()); //при добавлении брони с большим временем может долго работать, если наберется много брони с маленьким временем
    }
    auto it = hotels_info.find(hotel_name);
    return it != hotels_info.end() ? it->second.first.size() : 0;
  }

  //Находим отель в мапе, получаем мапу из клиентов -> кол-во комнат, суммируем комнаты каждого клиента
  //поиск отеля:                    O(log(количество отелей))
  //сумма комнат каждого клиента:   O(1)
  //Итого:                          O(log(количество отелей))
  int Rooms(const string& hotel_name) {
    while (booking.size() > 1 && booking.front().time <= booking.back().time - 86400){ //проверка на выход брони из интерсующего интервала времени
      DeleteClient(booking.front()); //при добавлении брони с большим временем может долго работать, если наберется много брони с маленьким временем
    }
    auto it = hotels_info.find(hotel_name);
    return it != hotels_info.end() ? it->second.second : 0;
  }

  //Добавляем бронь в очередь, находим отель в мапе, обновляем/добавляем информацию о количестве комнат клиента
  //Добавление в очередь: O(1)
  //Поиск отеля: O(log(количество отелей))
  //Удаление брони при добавлении: амортизированное O(log(кол-во отелей) + log(кол-во клиентов отеля))
  //Итого: амортизированное O(log(кол-во отелей) + log(кол-во клиентов отеля)) + O(log(кол-во отелей) + log(кол-во клиентов отеля))
  void AddClient(const Reserve& reserve){
    booking.push(reserve);
    auto& client_stats = hotels_info[reserve.hotel_name];
    client_stats.first.insert(reserve.client_id);
    client_stats.second += reserve.room_count;
  }

  //Находим отель, находим клиента.
  //Если кол-во комнат в удаляемой брони равно кол-ву комнат клиента в отеле, значит клиент покидает отель и его можно удалить
  //в противном случае уменьшаем количество комнат клиента и он по прежнему числится в отеле.
  //Поиск отеля:               O(log(кол-во отелей))
  //Удаление клиента:          O(log(кол-во отелей) + log(кол-во клиентов отеля))
  //Удаление брони из очереди: O(1)
  //Итого:                     O(log(кол-во отелей) + log(кол-во клиентов отеля))
  void DeleteClient(const Reserve& reserve){
    auto& client_stats = hotels_info[reserve.hotel_name];
    client_stats.first.erase(reserve.client_id);
    client_stats.second -= reserve.room_count;
    booking.pop();
  }

private:
  void CheckTime(const Reserve& reserve){
    while (booking.size() > 1 && booking.front().time <= reserve.time - 86400){ //проверка на выход брони из интерсующего интервала времени
      DeleteClient(booking.front()); //при добавлении брони с большим временем может долго работать, если наберется много брони с маленьким временем
    }
  }

  map<string, pair<set<int32_t>, int>> hotels_info; // (отель -> (клиенты , кол-во комнат))
  queue<Reserve> booking; // очередь брони
};



int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int Q;
  cin >> Q;
  HotelManager hm;
  for (int i = 0; i < Q; i++){
    string query, hotel_name;
    cin >> query;
    if (query == "BOOK"){
      int64_t time;
      int client_id;
      int32_t room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      hm.AddClient({hotel_name, room_count, client_id, time});
    } else if (query == "CLIENTS"){
      cin >> hotel_name;
      cout << hm.Clients(hotel_name) << "\n";
    } else if (query == "ROOMS"){
      cin >> hotel_name;
      cout << hm.Rooms(hotel_name) << "\n";
    } else {
      cout << "Wrong query.\n";
    }
  }
  return 0;
}
