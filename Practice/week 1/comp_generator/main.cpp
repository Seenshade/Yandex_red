#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <iomanip>

using namespace std;

#define SORT_BY(field)                                                                  \
  [](const AirlineTicket& lhs,const AirlineTicket& rhs){                                \
    return lhs.field < rhs.field;                                                       \
  }


bool operator<(const Date& lhs, const Date& rhs){
  if (lhs.year == rhs.year){
    if (lhs.month == rhs.month){
      return lhs.day < rhs.day;
    } else {
      return lhs.month < rhs.month;
    }
  } else {
    return lhs.year < rhs.year;
  }
}

bool operator==(const Date& lhs, const Date& rhs){
  if (lhs.year != rhs.year && lhs.month != rhs.month && lhs.day != rhs.day){
    return false;
  };
  return true;
}

ostream& operator<<(ostream& output, const Date& date){
  output << setfill('0') << setw(2) << date.day << "." << setw(2) << date.month << "." << date.year;
  return output;
}

bool operator<(const Time& lhs, const Time& rhs){
  if(lhs.hours == rhs.hours){
    return lhs.minutes < rhs.minutes;
  } else {
    return lhs.hours < rhs.hours;
  }
}

void TestSortBy() {
    vector<AirlineTicket> tixs = {
            {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
            {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
            {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
            {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
            {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));

    sort(begin(tixs), end(tixs), SORT_BY(departure_date));
    ASSERT_EQUAL(tixs.front().departure_date, (Date{2018, 2, 8}));
    ASSERT_EQUAL(tixs.back().departure_date, (Date{2018, 3, 5}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}