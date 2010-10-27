#ifndef ezio__File_Mode__hpp_
#define ezio__File_Mode__hpp_

#include <sys/types.h>

namespace ezio
{

class File_Mode
{
public:
  File_Mode(mode_t mode);

  mode_t value() const { return mode_; }

  operator mode_t() const { return mode_; }

  bool user_read() const;
  bool user_write() const;
  bool user_exec() const;

  bool group_read() const;
  bool group_write() const;
  bool group_exec() const;

  bool others_read() const;
  bool others_write() const;
  bool others_exec() const;

  bool socket() const;
  bool fifo() const;

  bool symlink() const;
  bool regfile() const;
  bool directory() const;

  bool blockdev() const;
  bool chardev() const;

  bool setuid() const;
  bool setgid() const;
  bool sticky() const;

private:
  mode_t mode_;
};

} // ezio

#endif // ezio__File_Mode__hpp_
