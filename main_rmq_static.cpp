#include <iostream>

#include "range_query.hpp"

int main(int argc, char** argv)
{
    const std::vector<int> xs = { 3, 3, 5, 0, 0, 3, 1, 4 };

    seg::rmq_fast<int> xs_min(xs);

    for(int l = 1; l <= xs_min.size(); l++) {
        for(int i = 0; i <= xs_min.size() - l; i++) {
            std::cout << xs_min.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }

    seg::rmq_fast<int, std::greater<>> xs_max(xs);

    for(int l = 1; l <= xs_max.size(); l++) {
        for(int i = 0; i <= xs_max.size() - l; i++) {
            std::cout << xs_max.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }

    seg::rmq_fast<int> ept({});
}
