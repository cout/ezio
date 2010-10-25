#ifndef ezio__Not_Copyable__hpp_
#define ezio__Not_Copyable__hpp_

namespace ezio
{

class Not_Copyable
{
protected:
  Not_Copyable() { }

private:
  Not_Copyable(Not_Copyable const &);
  Not_Copyable & operator=(Not_Copyable const &);
};

}

#endif // ezio__Not_Copyable__hpp_
