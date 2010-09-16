#ifndef ezio__Addrinfo__hpp_
#define ezio__Addrinfo__hpp_

#include "Shared_Object.hpp"

#include <string>

#include <sys/types.h>

struct addrinfo;

namespace ezio
{

class Addrinfo
  : public Shared_Object
{
public:
  Addrinfo(
      std::string const & node,
      std::string const & service);

  virtual void close();

  struct addrinfo const * addrinfo() const { return addrinfo_; }

private:
  struct addrinfo * addrinfo_;
};

}

#endif // ezio__Addrinfo__hpp_
