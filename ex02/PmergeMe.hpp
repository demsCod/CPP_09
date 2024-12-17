#pragma once
#include <vector>
#include <deque>
class PmergeMe
{
     
    public :
        PmergeMe();
        std::vector<int> sortVector(std::vector<int> &tab);
        std::deque<int> sortDeque(std::deque<int> &tab);
        void sort(std::vector<int> &v, std::deque<int> &d);
        ~PmergeMe();
};