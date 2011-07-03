#include <ezio/Context.hpp>
#include <eztest/eztest.hpp>

#include <iostream>

using namespace ezio;

TESTSUITE(Context);

TESTCASE(getcontext)
{
  Context context;
  EZIO_GETCONTEXT(context);
}

#include <ucontext.h>

TESTCASE(setcontext)
{
  int i = 0;

  Context context;
  EZIO_GETCONTEXT(context);

  ++i;

  if (i == 1)
  {
    context.setcontext();
  }

  ASSERT_EQUAL(2, i);
}

