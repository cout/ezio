#ifndef ezio__Streambuf__hpp_
#define ezio__Streambuf__hpp_

#include "File.hpp"

#include <streambuf>
#include <vector>

namespace ezio
{

class Streambuf
  : public std::streambuf
{
public:
  Streambuf(File file);

  File & file() { return file_; }
  File const & file() const { return file_; }
 
protected:
  int overflow(int c);
  int underflow();
  Streambuf * setbuf(char * buf, std::streamsize len);
  int sync();

private:
  File file_;

  static size_t const WRITE_BUFFER_SIZE = 16384;
  typedef std::vector<char> Write_Buffer;
  Write_Buffer write_buffer_;
};

} // namespace ezio

#endif // ezio__Streambuf__hpp_
