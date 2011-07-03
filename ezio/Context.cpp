#include "Context.hpp"

#include "exceptions/System_Exception.hpp"

ezio::Context::
Context()
{
}

ezio::Context
ezio::Context::
makecontext(
    Context & link,
    char * stack,
    size_t stack_size,
    void (*func)(void))
{
  Context context;
  EZIO_GETCONTEXT(context);

  context.ctx_.uc_stack.ss_sp = stack;
  context.ctx_.uc_stack.ss_size = stack_size;
  context.ctx_.uc_link = &link.ctx_; // TODO: ensure that the other context sticks around

  ::makecontext(&context.ctx_, func, 0);

  // TODO: is it valid to copy a ucontext_t like this?
  return context;
}

void
ezio::Context::
swapcontext(Context & save)
{
  if (::swapcontext(&save.ctx_, &ctx_) < 0)
  {
    throw System_Exception("swapcontext");
  }
}

void
ezio::Context::
setcontext()
{
  if (::setcontext(&ctx_) < 0)
  {
    throw System_Exception("swapcontext");
  }
}

