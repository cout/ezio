#ifndef ezio__Shared_Object__hpp_
#define ezio__Shared_Object__hpp_

namespace ezio
{

template<typename Data_T, typename Finalize_T>
class Shared_Object
{
public:
  Shared_Object();
  Shared_Object(Data_T const & data);
  Shared_Object(Shared_Object const & shared_object);

  virtual ~Shared_Object();

  Shared_Object & operator=(Shared_Object const & rhs);

  void swap(Shared_Object & shared_object);

  Data_T const & get() const { return data_; }
  Data_T & get() { return data_; }

  void set(Data_T const & data) { data_ = data; }

private:
  mutable Shared_Object const * prev_;
  mutable Shared_Object const * next_;
  Data_T data_;
};

} // ezio

#include "Shared_Object.ipp"

#endif // ezio__Shared_Object__hpp_
