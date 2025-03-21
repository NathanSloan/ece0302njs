#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(std::string s, int last)
{
  int first = 0;

  if ((first > last))
  {
    return -1;
  }

  char ch = s[last];
  // returns true if ch is a letter
  if (isalpha(ch))
  {
    return last;
  }
  else
  {
    if (isoperator(ch))
    {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1)
      {
        return endPost(s, lastEnd - 1);
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.length() - 1);

  return (firstChar == 0);
}

void convert(const std::string &postfix, std::string &prefix)
{
  if (!isPost(postfix) && prefix == "")
    throw std::invalid_argument("Invalid Postfix Expression");
  if (postfix.empty())
    return;
  if (isalpha(postfix[0]))
    prefix = prefix + postfix[0];
  else if (isoperator(postfix[0]))
    prefix = postfix[0] + prefix;
  else
    throw std::invalid_argument("Invalid Postfix Expression");

  convert(postfix.substr(1, postfix.length()), prefix);
}
