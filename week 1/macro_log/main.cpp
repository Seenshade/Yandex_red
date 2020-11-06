#include "test_runner.h"

#include <string>
#include <sstream>

using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void Log(const string& message){
    if (log_file && log_line){
      os << __FILE__ << ":" << __LINE__ << " " << message << "\n";
    } else if(log_file && !log_line){
      os << __FILE__ << " " << message << "\n";
    } else if(!log_file && log_line){
      os << "Line " << __LINE__ << " " << message << "\n";
    } else {
      os << message << "\n";
    }
  }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) \
  logger.Log(message);

void TestLog() {

#line 1 "main.cpp"
  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}