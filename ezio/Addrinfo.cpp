#include "Addrinfo.hpp"
#include "exceptions/Getaddrinfo_Exception.hpp"

#include <netdb.h>

ezio::Addrinfo::
Addrinfo(
    std::string const & node,
    std::string const & service)
{
  int s = ::getaddrinfo(node.c_str(), service.c_str(), 0, &addrinfo_.get());
  if (s != 0)
  {
    throw Getaddrinfo_Exception(s);
  }
}

void
ezio::Addrinfo::
finalize(struct addrinfo * addrinfo)
{
  ::freeaddrinfo(addrinfo);
}

