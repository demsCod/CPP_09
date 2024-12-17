#include "PmergeMe.hpp"
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm> // Pour std::sort
#include <cstdlib>   // Pour std::rand
#include <ctime>     // Pour std::time

// #include <time>
PmergeMe::PmergeMe() 
{
}

PmergeMe::~PmergeMe() 
{
}


#include <iostream>
#include <vector>
#include <sys/time.h>


std::vector<long long> jacobsthal_iterative(int n) {

    std::vector<long long> jacobsthal(n + 1);

    jacobsthal[0] = 0;
    if (n > 0) jacobsthal[1] = 1;

    for (int i = 2; i <= n; ++i) {
        jacobsthal[i] = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        //std::cout << jacobsthal[i] << "   ";
    }

    return jacobsthal;
}

std::deque<long long> jacobsthal_iterative_d(int n) {

    std::deque<long long> jacobsthal(n + 1);

    jacobsthal[0] = 0;
    if (n > 0) jacobsthal[1] = 1;

    for (int i = 2; i <= n; ++i) {
        jacobsthal[i] = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        //std::cout << jacobsthal[i] << "   ";
    }

    return jacobsthal;
}

std::vector<int> PmergeMe::sortVector(std::vector<int> &tab)
{
    std::vector<int> minima;
    std::vector<int> maxima;
    std::vector<int>::iterator it2;
    if (tab.size() == 1)
       return tab;
    for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        if (it  == tab.end())
            break;
        if (it + 1 == tab.end())
            minima.push_back(*it);
        else
        {
            it2 = it + 1;
            maxima.push_back(std::max(*it, *it2));
            minima.push_back(std::min(*it, *it2));
            it++;
        }
    }
    if (minima.size() == 1 ) {
		if (maxima.empty() == false)
        {
            minima.push_back(maxima[0]);
            tab = minima;
        }
	    return minima;
	}
    maxima = sortVector(maxima);
    std::vector<int>::iterator toInsert;
    long long lastIndex = -1;
    std::vector<long long>jacobtab = jacobsthal_iterative(3000000);
    long long  CurrentIndex;
    for (int i = 2; i < 30000000; i++)
    {
        CurrentIndex = jacobtab[i];
        if (CurrentIndex >= minima.size())
        {
         
            if (lastIndex >= minima.size())
            {
               break;
            }
            else
            {
                CurrentIndex = minima.size() - 1;
            }
        }
      
        for (long long  j = CurrentIndex; j > lastIndex ; j--)
        {
            if (minima.begin() + j  != minima.end())
            {
                toInsert = std::lower_bound(maxima.begin(), maxima.end(), *(minima.begin() + j));
                maxima.insert(toInsert, *(minima.begin() + j));
            }
        }
        lastIndex = jacobtab[i];
    }
    tab = maxima;
    return maxima; 
}

// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us


void PmergeMe::sort(std::vector<int> &v, std::deque<int> &d)
{
    struct timeval start, end;
    std::cout << "Before : ";
    for(std::vector<int>::iterator it =  v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";

	gettimeofday(&start, 0);
    sortVector(v);
    gettimeofday(&end, 0);
    std::cout << "After : ";
    for(std::vector<int>::iterator it =  v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
    long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;
    int vectortime = seconds + microseconds * 1e-6;
	gettimeofday(&start, 0);
    sortDeque(d);
    gettimeofday(&end, 0);
     seconds = end.tv_sec - start.tv_sec;
	 microseconds = end.tv_usec - start.tv_usec;
    int dequetime = seconds + microseconds * 1e-6;
    std::cout << "Time to process a range of " << v.size() << " elements with std::vectot : " << vectortime << " sec" << std::endl;
    std::cout << "Time to process a range of " << d.size() << " elements with std::deque : " << dequetime << " sec" << std::endl;
}


std::deque<int> PmergeMe::sortDeque(std::deque<int> &tab)
{
    std::deque<int> minima;
    std::deque<int> maxima;
    std::deque<int>::iterator it2;
    if (tab.size() == 1)
       return tab;
    for (std::deque<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        if (it  == tab.end())
            break;
        if (it + 1 == tab.end())
            minima.push_back(*it);
        else
        {
            it2 = it + 1;
            maxima.push_back(std::max(*it, *it2));
            minima.push_back(std::min(*it, *it2));
            it++;
        }
    }
    if (minima.size() == 1 ) {
		if (maxima.empty() == false)
        {
            minima.push_back(maxima[0]);
            tab = minima;
        }
	    return minima;
	}
    maxima = sortDeque(maxima);
    std::deque<int>::iterator toInsert;
    long long lastIndex = -1;
    std::deque<long long>jacobtab = jacobsthal_iterative_d(3000000);
    long long  CurrentIndex;
    for (int i = 2; i < 30000000; i++)
    {
        CurrentIndex = jacobtab[i];
        if (CurrentIndex >= minima.size())
        {
         
            if (lastIndex >= minima.size())
            {
               break;
            }
            else
            {
                CurrentIndex = minima.size() - 1;
            }
        }
      
        for (long long  j = CurrentIndex; j > lastIndex ; j--)
        {
            if (minima.begin() + j  != minima.end())
            {
                toInsert = std::lower_bound(maxima.begin(), maxima.end(), *(minima.begin() + j));
                maxima.insert(toInsert, *(minima.begin() + j));
            }
        }
        lastIndex = jacobtab[i];
    }
    tab = maxima;
    return maxima; 
}



int main() {
    // Initialisation d'un tableau avec 3000 nombres aléatoires
    
        std::vector<int> tab;
        std::deque<int> b;
        std::srand(std::time(nullptr));  // Initialisation du générateur de nombres aléatoires
        
        // Remplir le tableau avec 3000 nombres aléatoires entre 1 et 1000
        for (int i = 0; i < 3000; ++i) {
            int a =  std::rand() % 1000 + 1;
            tab.push_back(a);
            b.push_back(a);
        }
        PmergeMe z;
        z.sort(tab, b);
        

   
    
    return 0;
}
