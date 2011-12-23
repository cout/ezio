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

void makecontext_helper()
{
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

namespace
{

static bool sr_invoked = false;

void sr_helper()
{
  sr_invoked = true;
}

} // namespace

TESTCASE(swapcontext__function_returns)
{
  char stack[1024];

  Context current;

  Context context(Context::makecontext(
          stack,
          sizeof(stack),
          sr_helper,
          &current));

  sr_invoked = false;

  EZIO_GETCONTEXT(current);

  context.swapcontext(current);
  ASSERT(sr_invoked);
}

namespace
{

static bool ss_invoked = false;
Context ss_helper_ctx;

void ss_helper()
{
  ss_invoked = true;

  Context context;
  ss_helper_ctx.swapcontext(context);
}

} // namespace

TESTCASE(swapcontext__function_swaps)
{
  char stack[1024];

  Context context(Context::makecontext(
          stack,
          sizeof(stack),
          ss_helper,
          &ss_helper_ctx));

  ss_invoked = false;

  if (!ss_invoked)
  {
    context.swapcontext(ss_helper_ctx);
  }

  ASSERT(ss_invoked);
}

