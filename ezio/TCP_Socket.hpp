#ifndef ezio__TCP_Socket__hpp_
#define ezio__TCP_Socket__hpp_

#include "Socket.hpp"

#include <string>

namespace ezio
{

class Addrinfo;

class TCP_Socket
  : public Socket
{
public:
  static TCP_Socket connect(
      std::string const & node,
      std::string const & service);

  static TCP_Socket connect(
      std::string const & node,
      int port);

  static TCP_Socket connect(
      Addrinfo const & addrinfo);
};

}

#endif // ezio__TCP_Socket__hpp_

