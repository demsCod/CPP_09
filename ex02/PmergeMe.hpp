#pragma once
#include <vector>
#include <deque>
class PmergeMe
{

    private :
        std::vector<int>vec; 
        std::deque<int>deq; 
    public :
        PmergeMe();
        PmergeMe(char **av);
        std::vector<int> sortVector(std::vector<int> &tab);
        std::deque<int> sortDeque(std::deque<int> &tab);
        void sort(std::vector<int> &v, std::deque<int> &d);
        void sortNumber();
        ~PmergeMe();
};