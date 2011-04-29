#include "Shared_Object.hpp"

#include <algorithm>

ezio::Shared_Object::
Shared_Object()
  : prev_(this)
  , next_(this)
{
}

ezio::Shared_Object::
~Shared_Object()
{
  prev_->next_ = next_;
  next_->prev_ = prev_;

  if (prev_ == next_)
  {
    // We can't call close directly, because it's a virtual function and
    // we're in the destructor.  So we construct a temporary copy on the
    // stack and call close() on it.
    // The temporary object's destructor won't try to call close,
    // because tmp.prev_ != tmp.next_ (since once we make the temporary
    // there will be two copies).
    Shared_Object tmp(*this);
    tmp.close();
  }
}

ezio::Shared_Object &
ezio::Shared_Object::
operator=(
    Shared_Object const & rhs)
{
  Shared_Object tmp(rhs);
  swap(tmp);
  return *this;
}

void
ezio::Shared_Object::
swap(
    Shared_Object & shared_object)
{
  std::swap(prev_, shared_object.prev_);
  std::swap(next_, shared_object.next_);
}

ezio::Shared_Object::
Shared_Object(
    Shared_Object const & shared_object)
{
  prev_ = shared_object.prev_;
  next_ = &shared_object;
  shared_object.prev_ = this;
}

