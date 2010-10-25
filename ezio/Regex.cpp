#include "Regex.hpp"

std::string 
ezio::Regex::Error::
error_msg(int code, regex_t * reg)
{
  size_t bytes = regerror(code, reg, 0, 0);
  std::string msg;
  msg.resize(bytes + 1);
  regerror(code, reg, &msg[0], bytes);
  return msg;
}

ezio::Regex::Error::
Error(int code, regex_t * reg)
  : Exception(error_msg(code, reg))
{
}

ezio::Regex::
Regex(char const * regex)
{
  // TODO: support flags
  int result = regcomp(&reg_, regex, REG_EXTENDED);

  if (result != 0)
  {
    throw Error(result, &reg_);
  }
}

ezio::Regex::
Regex(std::string const & regex)
{
  // TODO: support flags
  int result = regcomp(&reg_, regex.c_str(), REG_EXTENDED);

  if (result != 0)
  {
    throw Error(result, &reg_);
  }
}

ezio::Regex::
~Regex()
{
  regfree(&reg_);
}

bool
ezio::Regex::
match(char const * str, Match * match)
{
  match->str(str);

  int nmatch = match ? match->nmatch() : 0;
  regmatch_t * regmatch = match ? match->regmatch() : 0;

  int result = regexec(&reg_, str, nmatch, regmatch, 0); // TODO: support eflags

  return result == 0;
}

bool
ezio::Regex::
match(std::string const & str, Match * match)
{
  return this->match(str.c_str(), match);
}

ezio::Regex::Match::
Match(size_t nmatch)
  : str_(0)
  , nmatch_(nmatch)
  , regmatch_(new regmatch_t[nmatch])
{
}

ezio::Regex::Match::
~Match()
{
  delete[] regmatch_;
}

std::string
ezio::Regex::Match::
str(size_t n) const
{
  // TODO: detect out-of-bounds?
  regmatch_t * regmatch(&regmatch_[n-1]);
  return std::string(str_ + regmatch->rm_so, str_ + regmatch->rm_eo);
}

