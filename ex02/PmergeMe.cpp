#include "PmergeMe.hpp"
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm> // Pour std::sort
#include <cstdlib>   // Pour std::rand
#include <ctime>     // Pour std::time
#include <sstream>

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
               break;
            else
                CurrentIndex = minima.size() - 1;
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


void PmergeMe::sortNumber()
{
    struct timeval start, end;
    std::cout << "Before : ";
    for(std::vector<int>::iterator it =  vec.begin(); it != vec.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
	gettimeofday(&start, 0);
    sortVector(vec);
    gettimeofday(&end, 0);
    std::cout << "After : ";
    for(std::vector<int>::iterator it =  vec.begin(); it != vec.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
    long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;
    int vectortime = seconds + microseconds * 1e-6;
	gettimeofday(&start, 0);
    sortDeque(deq);
    gettimeofday(&end, 0);
     seconds = end.tv_sec - start.tv_sec;
	 microseconds = end.tv_usec - start.tv_usec;
    int dequetime = seconds + microseconds * 1e-6;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vectortime << " sec" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << dequetime << " sec" << std::endl;
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
               break;
            else
                CurrentIndex = minima.size() - 1;
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
PmergeMe::PmergeMe(char **av)
{
    int temp;
   
    while(*av)
    {
        std::stringstream a(*av);
        a >> temp;
        if (a.fail())
            throw std::runtime_error("Wrong Number");
        vec.push_back(temp);
        deq.push_back(temp);
        av++;
    }
}


int main(int ac, char **av) {
    // Initialisation d'un tableau avec 3000 nombres aléatoires
    
        /*std::vector<int> tab;
        std::deque<int> b;
        std::srand(std::time(nullptr));  // Initialisation du générateur de nombres aléatoires
        
        // Remplir le tableau avec 3000 nombres aléatoires entre 1 et 1000
        for (int i = 0; i < 3000; ++i) {
            int a =  std::rand() % 1000 + 1;
            tab.push_back(a);
            b.push_back(a);
        }
        PmergeMe z;
        z.sort(tab, b);*/
    try
    {
        if (ac < 2)
            throw std::runtime_error("Not enought args");
        PmergeMe a(av + 1);
        a.sortNumber();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
