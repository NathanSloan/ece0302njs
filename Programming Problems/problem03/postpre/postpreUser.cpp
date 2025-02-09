#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

#include "algebraic_expressions.hpp"

int main()
{
    std::string postfix = "13+2*";
    std::string prefix = "";

    try
    {
        convert(postfix, prefix);
        std::cout << prefix << std::endl;
    }
    catch (std::invalid_argument ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
};
