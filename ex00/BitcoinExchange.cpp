#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include "BitcoinExchange.hpp"
#include <exception>
#include <algorithm>

#include <sstream>

BitcoinExchange::BitcoinExchange(std::string input)
{  
    std::string line;
    std::string S;
    float I;
    int pos;  
    std::fstream file;

    fs.open(input , std::fstream::in);
    if(!fs)
        throw std::exception();
    std::getline(fs, buffer);
    if (buffer.compare("date | value"))
        throw std::exception();
    file.open("data.csv" , std::fstream::in);
    if(!file)
        throw std::exception();
    while (std::getline(file, line))
    {
        pos = line.find(',');
        S = line.substr(0, pos);
        I = std::atof(line.substr(pos + 1).c_str());
        database[S] = I;
    }
   
}

int checkInput(std::string line)
{
    if (std::count(line.begin(), line.end(), '|') != 1 || line.find('|') != 11 || line.size() < 12)
        return 1;
    if(line.at(10) != ' ' || line.at(12) != ' ' || std::count(line.begin(), line.end(), '-') < 2 ||
             line.at(4) != '-' ||  line.at(7) != '-')
            return 1;
    std::string checkDate = line.substr(0, 10);
    checkDate.replace(4, 1, "1");
    checkDate.replace(7, 1, "1");
    std::stringstream ss(checkDate);
    long d;
    ss >> d;
    if(ss.fail() )
        return 1;
    return (0);
}

void BitcoinExchange::DisplayValue()
{
    while (std::getline(fs, buffer))
    {
        if (checkInput(buffer))
            std::cout << "Error: bad input  => "  << buffer << std::endl;
        else
        {
            std::cout << "Good input => "  << buffer << std::endl;

        }
    }
    
}

int main (int ac, char **av)
{
    if (ac == 2)
    {
        BitcoinExchange a(av[1]);
        a.DisplayValue();
        


    }
}