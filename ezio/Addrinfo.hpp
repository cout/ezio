#ifndef ezio__Addrinfo__hpp_
#define ezio__Addrinfo__hpp_

#include "Shared_Object.hpp"

#include <string>

#include <sys/types.h>

struct addrinfo;

namespace ezio
{

class Addrinfo
{
public:
  Addrinfo(
      std::string const & node,
      std::string const & service);

  static void finalize(struct addrinfo * addrinfo);

  struct addrinfo const * addrinfo() const { return addrinfo_.get(); }

private:
  Shared_Object<struct addrinfo *, Addrinfo> addrinfo_;
};

}

#endif // ezio__Addrinfo__hpp_
