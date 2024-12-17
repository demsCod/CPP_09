#include "PmergeMe.hpp"
#include "sstream"
#include "exception"

Pmerge::Pmerge(char **av)
{
    int b;
    while (av)
    {
        std::stringstream a(*av);
        a >>  b;
        if (a.fail())
            throw std::exception();
        tab.push_back(b);
    }
}


    