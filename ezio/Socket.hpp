#ifndef ezio__Socket__hpp_
#define ezio__Socket__hpp_

#include "File.hpp"

#include <string>

namespace ezio
{

class Addrinfo;

class Socket
  : public File
{
public:
  void connect(
      std::string const & node,
      std::string const & service);

  void connect(
      std::string const & node,
      int port);

  void connect(
      Addrinfo const & addrinfo);
};

}

#endif // ezio__Socket__hpp_

