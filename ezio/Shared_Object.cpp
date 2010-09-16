#include "Shared_Object.hpp"

Shared_Object::
Shared_Object()
  : prev_(this)
  , next_(this)
{
}

Shared_Object::
~Shared_Object()
{
  prev_->next_ = next_;
  next_->prev_ = prev_;

  if (prev_ == next_)
  {
    close();
  }
}

Shared_Object &
Shared_Object::
operator=(
    Shared_Object const & rhs)
{
  Shared_Object tmp(rhs);
  swap(tmp);
  return *this;
}

void
Shared_Object::
swap(
    Shared_Object & shared_object)
{
  std::swap(prev_, shared_object.prev_);
  std::swap(next_, shared_object.next_);
}

Shared_Object::
Shared_Object(
    Shared_Object const & shared_object)
{
  prev_ = shared_object.prev_;
  next_ = &shared_object;
  shared_object.prev_ = this;
}
