#ifndef ezio__Regex__hpp_
#define ezio__Regex__hpp_

#include "Exception.hpp"
#include "Not_Copyable.hpp"

#include <string>

#include <sys/types.h>
#include <regex.h>

namespace ezio
{

class Regex
  : private Not_Copyable
{
public:
  Regex(char const * regex);

  Regex(std::string const & regex);

  ~Regex();

  class Match
  {
  public:
    Match(size_t nmatch);
    ~Match();

    size_t nmatch() const { return nmatch_; }
    regmatch_t * regmatch() { return regmatch_; }

    void str(char const * str) { str_ = str; }
    std::string str(size_t n) const;

  private:
    char const * str_;
    size_t nmatch_;
    regmatch_t * regmatch_;
  };

  class Error
    : public Exception
  {
  public:
    Error(int code, regex_t * reg);

  private:
    static std::string error_msg(int code, regex_t * reg);
  };

  bool match(char const * str, Match * match = 0);

  bool match(std::string const & str, Match * match = 0);

  regex_t * reg() { return &reg_; }

private:
  regex_t reg_;
};

} // ezio

#endif // ezio__Regex__hpp_
