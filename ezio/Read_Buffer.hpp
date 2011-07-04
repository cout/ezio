#ifndef ezio__Read_Buffer__hpp_
#define ezio__Read_Buffer__hpp_

namespace ezio
{

class Read_Buffer
{
public:
  static size_t const READ_SIZE = 16384;
  typedef std::vector<char> buffer_type;
  typedef buffer_type::value_type value_type;
  typedef buffer_type::iterator iterator;
  typedef buffer_type::const_iterator const_iterator;

  Read_Buffer();

  size_t fill_from(int fd);

  size_t size();

  value_type operator[](size_t idx);

  const_iterator begin() const;
  const_iterator end() const;

  bool find(size_t begin_idx, size_t end_idx, char delim, size_t * found_idx)

  void erase(size_t begin_idx, size_t end_idx)

private:
  // TODO: not the most efficient way to do I/O (in terms of # of memory
  // allocations), but very simple
  buffer_type buf_;
  size_t size_;
};

} // namespace ezio

#endif // ezio__Read_Buffer__hpp_
