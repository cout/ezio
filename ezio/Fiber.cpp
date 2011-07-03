#include "Fiber.hpp"

ezio::Fiber::
Fiber(
      void (*func)(void),
      size_t stack_size,
      char * stack)
  : stack_size_(stack_size)
  , stack_(stack ? stack : new char[stack_size])
  , free_stack_(stack ? false : true)
  , context_(Context::makecontext(
          stack_,
          stack_size_,
          func,
          0)) // TODO: define a successor?
{
}

ezio::Fiber::
~Fiber()
{
  if (free_stack_)
  {
    delete[] stack_;
  }
}

void
ezio::Fiber::
schedule()
{
  Context context;
  context_.swapcontext(context);
}

