#ifndef ezio__TCP_Server__hpp_
#define ezio__TCP_Server__hpp_

#include "TCP_Socket.hpp"

namespace ezio
{

class TCP_Server
  : public TCP_Socket
{
public:
  static int const DEFAULT_BACKLOG=5;

  TCP_Server(
      std::string const & node,
      std::string const & service,
      int backlog=DEFAULT_BACKLOG);

  TCP_Server(
      std::string const & node,
      int port,
      int backlog=DEFAULT_BACKLOG);

  TCP_Server(
      std::string const & service,
      int backlog=DEFAULT_BACKLOG);

  TCP_Server(
      int port,
      int backlog=DEFAULT_BACKLOG);

  TCP_Server(
      Addrinfo const & addrinfo,
      int backlog=DEFAULT_BACKLOG);

  void bind(
      Addrinfo const & addrinfo);

  void listen(int backlog=DEFAULT_BACKLOG);

  TCP_Socket accept();
};

} // ezio

#endif // ezio__TCP_Server__hpp_
