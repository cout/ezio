#include "Addrinfo.hpp"

#include <netdb.h>

Addrinfo::
Addrinfo(
    std::string const & node,
    std::string const & service)
{
  int s = ::getaddrinfo(node.c_str(), service.c_str(), 0, &addrinfo_);
  if (s != 0)
  {
    throw Getaddrinfo_Exception(s);
  }
}

void
Addrinfo::
close()
{
  ::freeaddrinfo(addrinfo_);
}

