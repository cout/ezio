#ifndef ezio__Shared_Object__hpp_
#define ezio__Shared_Object__hpp_

namespace ezio
{

class Shared_Object
{
public:
  Shared_Object();
  Shared_Object(Shared_Object const & shared_object);
  virtual ~Shared_Object();

  virtual void close() { }

  Shared_Object & operator=(Shared_Object const & rhs);

  void swap(Shared_Object & shared_object);

private:
  mutable Shared_Object const * prev_;
  mutable Shared_Object const * next_;
};

}

#endif // ezio__Shared_Object__hpp_
