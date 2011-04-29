#include <ezio/Shared_Object.hpp>
#include <eztest/eztest.hpp>

#include <iostream>

using namespace ezio;

TESTSUITE(Shared_Object);

class CloseIsCalledHelper
  : private Shared_Object<int *, CloseIsCalledHelper>
{
public:
  CloseIsCalledHelper(int * i)
    : Shared_Object<int *, CloseIsCalledHelper>(i)
  {
  }

  static void finalize(int * i)
  {
    std::cout << "close" << std::endl;
    *i = 42;
  }
};

TESTCASE(close_is_called_when_no_more_refs)
{
  int i = 0;
  {
    CloseIsCalledHelper tmp(&i);
    CloseIsCalledHelper copy(tmp);
  }
  ASSERT_EQUAL(42, i);
}

