#include "ezio/TCP_Server.hpp"
#include "ezio/Libev_Reactor.hpp"

#include <iostream>

namespace
{

using namespace ezio;

struct New_Connection_Callback
  : public Reactor::File_Callback
{

virtual void operator()(File & file)
{
  std::cout << "New connection" << std::endl;
  TCP_Server server(file);
  TCP_Socket sock(server.accept());
  std::cout << "Accepted connection" << std::endl;
}

};

} // namespace

int main()
{
  using namespace ezio;

  Libev_Reactor reactor;

  TCP_Server server(4242);

  New_Connection_Callback cb;

  void * key = reactor.io_add(
      server,
      cb,
      File_Event::READ);

  reactor.run();
}

