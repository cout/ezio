#include "Shared_Object.hpp"

#include <algorithm>

template<typename Data_T, typename Finalize_T>
ezio::Shared_Object<Data_T, Finalize_T>::
Shared_Object()
  : prev_(this)
  , next_(this)
  , data_()
{
}

template<typename Data_T, typename Finalize_T>
ezio::Shared_Object<Data_T, Finalize_T>::
Shared_Object(Data_T const & data)
  : prev_(this)
  , next_(this)
  , data_(data)
{
}

template<typename Data_T, typename Finalize_T>
ezio::Shared_Object<Data_T, Finalize_T>::
Shared_Object(
    Shared_Object const & shared_object)
  : prev_(shared_object.prev_)
  , next_(&shared_object)
  , data_(shared_object.data_)
{
  shared_object.prev_ = this;
}

template<typename Data_T, typename Finalize_T>
ezio::Shared_Object<Data_T, Finalize_T>::
~Shared_Object()
{
  prev_->next_ = next_;
  next_->prev_ = prev_;

  if (prev_ == this and next_ == this)
  {
    Finalize_T::finalize(data_);
  }
}

template<typename Data_T, typename Finalize_T>
ezio::Shared_Object<Data_T, Finalize_T> &
ezio::Shared_Object<Data_T, Finalize_T>::
operator=(
    Shared_Object const & rhs)
{
  Shared_Object tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename Data_T, typename Finalize_T>
void
ezio::Shared_Object<Data_T, Finalize_T>::
swap(
    Shared_Object & shared_object)
{
  std::swap(prev_, shared_object.prev_);
  std::swap(next_, shared_object.next_);
}

