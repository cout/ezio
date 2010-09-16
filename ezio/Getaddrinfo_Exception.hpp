#ifndef ezio__Getaddrinfo_Exception__hpp_
#define ezio__Getaddrinfo_Exception__hpp_

namespace ezio
{

class Getaddrinfo_Exception
  : public Exception
{
public:
  Getaddrinfo_Exception(int errno);

  virtual char const * what() const throw();

private:
  int errno_;
};

} // ezio

#endif // ezio__Getaddrinfo_Exception__hpp_
