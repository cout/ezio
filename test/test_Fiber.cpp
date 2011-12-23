#include <ezio/Fiber.hpp>
#include <eztest/eztest.hpp>

using namespace ezio;

TESTSUITE(Fiber);

namespace
{

void create_helper()
{
}

} // namespace

TESTCASE(create)
{
  Fiber fiber(
      create_helper,
      1024);
}

namespace
{

static bool scheduled = false;

void schedule_helper()
{
  scheduled = true;
}

} // namespace

TESTCASE(schedule)
{
  Fiber fiber(
      schedule_helper,
      16384);

  scheduled = false;
  fiber.schedule();
  ASSERT(scheduled);
}

