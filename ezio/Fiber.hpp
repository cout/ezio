#ifndef ezio__Fiber__hpp_
#define ezio__Fiber__hpp_

#include "Context.hpp"

namespace ezio
{

// A user-level thread class
class Fiber
{
public:
  Fiber(
      void (*func)(void),
      size_t stack_size,
      char * stack = 0);

  virtual ~Fiber();

  void schedule();

  Context const & context() { return context_; }

private:
  size_t stack_size_;
  char * stack_;
  bool free_stack_;
  Context context_;
};

}; // namespace ezio

#endif // ezio__Fiber__hpp_
