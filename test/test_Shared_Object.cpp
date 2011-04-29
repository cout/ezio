#include <ezio/Shared_Object.hpp>
#include <eztest/eztest.hpp>

using namespace ezio;

TESTSUITE(Shared_Object);

class CloseIsCalledHelper
  : public Shared_Object
{
public:
  CloseIsCalledHelper(int * i)
    : i_(i)
  {
  }

  virtual void close()
  {
    *i_ = 42;
  }

private:
  int * i_;
};

TESTCASE(close_is_called_when_no_more_refs)
{
  int i = 0;
  {
    CloseIsCalledHelper tmp(&i);
    Shared_Object copy(tmp);
  }
  ASSERT_EQUAL(42, i);
}

