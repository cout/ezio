#ifndef sock__hpp_
#define sock__hpp_

#include <string>
#include <stdexcept>

#include <sys/types.h>

class Exception
  : public std::exception
{
};

class Runtime_Error
  : public Exception
{
public:
  Runtime_Error(
      std::string const & msg);

  char const * what() const throw();

private:
  std::string const & msg_;
};

class Connection_Failure
  : public Runtime_Error
{
public:
  Connection_Failure(
      std::string const & msg);
};

class System_Exception
  : public Exception
{
public:
  System_Exception(int errno);

  virtual char const * what() const throw();

private:
  int errno_;
};

class Getaddrinfo_Exception
  : public Exception
{
public:
  Getaddrinfo_Exception(int errno);

  virtual char const * what() const throw();

private:
  int errno_;
};

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

class File
  : public Shared_Object
{
public:
  File();

  virtual void close();

  int fd() const { return fd_; }

  void fdopen(int fd);

private:
  int fd_;
};

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

class TCPSocket
  : public Socket
{
public:
  static TCPSocket connect(
      std::string const & node,
      std::string const & service);

  static TCPSocket connect(
      std::string const & node,
      int port);

  static TCPSocket connect(
      Addrinfo const & addrinfo);
};

class UDPSocket
  : public Socket
{
public:
};

#endif // sock__hpp_
