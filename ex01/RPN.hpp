#include <stack>
#include <string>
class RPN
{
private:
    std::stack<int> data;
    std::stack<std::string>stock;
public:
    RPN(std::string args);
    void calculate();
    ~RPN();
};


