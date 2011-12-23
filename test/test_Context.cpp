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

namespace
{

static bool invoked = false;

void makecontext_helper()
{
  invoked = true;
}

} // namespace

TESTCASE(makecontext)
{
  char stack[1024];

  Context context(Context::makecontext(
          stack,
          sizeof(stack),
          makecontext_helper));
}

TESTCASE(swapcontext)
{
  char stack[1024];

  Context context(Context::makecontext(
          stack,
          sizeof(stack),
          makecontext_helper));

  invoked = false;

  Context current;
  EZIO_GETCONTEXT(current);

  current.swapcontext(context);
}

