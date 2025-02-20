#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

#include "algebraic_expressions.hpp"

int main()
{
    std::string postfix = "+*AB/CD";
    std::string prefix = "";

    convert(postfix, prefix);

    std::cout << "prefix: " << prefix << std::endl;

    return 1;
};
