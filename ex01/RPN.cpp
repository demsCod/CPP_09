
#include "RPN.hpp"
#include <string>
#include <iostream>
RPN::RPN(std::string args)
{
    int begin = 0;
    std::stack<std::string>temp;
    while(1)
    {
        int end = args.find(' ');
        begin = 0;
        if (end == std::string::npos)
        {
            std::string token = args.substr(begin, args.size());
            temp.push(token);
            break;
        }
        std::string token = args.substr(begin, end);
        begin = end + 1;
        args = args.substr(begin, args.size());
        temp.push(token);
    }
    while(!temp.empty())
    {
        stock.push(temp.top());         //remettre a l'endroit
        temp.pop();
    }
}

RPN::~RPN()
{
}

 #include <sstream>
bool isValidNumber(std::string num)
{
    std::stringstream ss(num);
    int d;
    ss >> d;
    if(ss.fail())
        return false;
    if (d > 9)
        return false;
    return true;

}
void RPN::calculate()
{
    //std::cout <<"debug" << "\n";
    while(!stock.empty())
    {
        std::string token = stock.top();
        stock.pop();
        if (token == "+" || token == "-" || token == "/" || token == "*")
        {
            if(data.size() < 2)
            {
                std::cerr << "invalid rpn format" << std::endl;
                return ;
            }
            else
            {
                int a =  data.top();
                data.pop();
                int b = data.top();
                data.pop();
                if (token == "+" )
                    data.push(b + a);
                else if (token == "-")
                    data.push(b - a);
                else if (token == "/")
                {
                    if (a == 0)
                        throw std::runtime_error("Division by zero");
                    data.push(b / a);
                }
                else
                     data.push(b * a);
            }
        }
        else
        {
            if (!isValidNumber(token))
            {
                std::cerr << "Error invalid input ---->" << token << std::endl;
                return ;
            }
            else 
            {
                std::stringstream ss(token);
                int d;
                ss >> d;
                data.push(d);
            }
        }
    }
    if (data.size() != 1)
    {
        std::cerr << "Error invalid rpn format\n";
        return ;
    }
    std::cout << data.top() << std::endl;
}

int main (int ac, char **av)
{
 
try{
    RPN a(av[1]);
    a.calculate();
}
catch( std::exception& e)
{
    std::cerr << e.what() << std::endl ;
}
}