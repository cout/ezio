#ifndef ezio__Context__hpp_
#define ezio__Context__hpp_

#include <ucontext.h>

#include "exceptions/System_Exception.hpp"

// Need to use a macro because if we return from the function in which
// getcontext is called, the context becomes invalidated.
#define EZIO_GETCONTEXT(ctx) \
  Context::check_getcontext( \
      ctx, \
      ::getcontext(&ctx.context()))

namespace ezio
{

class Context
{
public:
  Context();

  Context(ucontext_t context)
    : ctx_(context)
  {
  }

  static Context & check_getcontext(
      Context & context,
      int getcontext_result);

  // Create a new context.
  //
  // stack - pointer to stack space for this context
  //
  // stack_size - size of the stack space
  //
  // func - function to invoke for this context
  //
  // link - context which will be resumed when this context terminates
  // (i.e. when func returns; can be null)
  static Context makecontext(
      char * stack,
      size_t stack_size,
      void (*func)(void),
      Context * link = 0);

  template<typename Arg1_T>
  static Context makecontext(
      char * stack,
      size_t stack_size,
      void (*func)(void),
      Arg1_T const & arg1,
      Context * link = 0);

  void swapcontext(Context & save);

  void setcontext();

  ucontext_t & context() { return ctx_; }
  ucontext_t const & context() const { return ctx_; }

private:
  ucontext_t ctx_;
};

} // ezio

#include "Context.ipp"

#endif // ezio__Context__hpp_
