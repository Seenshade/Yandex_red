#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output, 5, "red belt");
      ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

  tr.RunTest([] {
      ostringstream output;
      for(int i = 0; i < 6; i+=2){
        PRINT_VALUES(output, i, i+1);
      }
      ASSERT_EQUAL(output.str(), "0\n1\n2\n3\n4\n5\n");
  }, "2nd test");

  tr.RunTest([] {
      ostringstream output;
      int a=2,b=3;
      if(false)PRINT_VALUES(output,a,b);
      ASSERT_EQUAL(output.str(), "");
  }, "3rd test");

  tr.RunTest([] {
      ostringstream output;
      int a=2,b=3;
      if(true)PRINT_VALUES(output,a,b);
      ASSERT_EQUAL(output.str(), "2\n3\n");
  }, "4 test");

  tr.RunTest([] {
      ostringstream output;
      int a=2,b=3;
      if(false)
        PRINT_VALUES(output,a,b);
      else
      PRINT_VALUES(output,a,b);
      ASSERT_EQUAL(output.str(), "2\n3\n");
  }, "5 test");
}
