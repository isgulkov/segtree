#include <iostream>

#include "stack_semi.hpp"

int main(int argc, char** argv)
{
    const std::vector<int> xs = { 10, 8, 9, 6, 7, 3, 4, 5, 2, 0, 1 };

    seg::stack_sum<int> stack;

    for(int x : xs) {
        stack.push(x);

        std::cout << stack.top() << " " << stack.min() << std::endl;
    }

    std::cout << std::endl;

    do {
        std::cout << stack.top() << " " << stack.min() << std::endl;
        stack.pop();
    } while(!stack.empty());
}
