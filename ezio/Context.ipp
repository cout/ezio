template<typename T>
ezio::Context
ezio::Context::
makecontext(
    char * stack,
    size_t stack_size,
    void (*func)(void),
    T const & arg,
    Context * link)
{
  Context context;
  EZIO_GETCONTEXT(context);

  context.ctx_.uc_stack.ss_sp = stack;
  context.ctx_.uc_stack.ss_size = stack_size;
  context.ctx_.uc_link = link ? &link->ctx_ : 0; // TODO: ensure that the other context sticks around

  ::makecontext(&context.ctx_, func, 1, arg);

  // TODO: is it valid to copy a ucontext_t like this?
  return context;
}

