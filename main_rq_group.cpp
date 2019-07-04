#include <iostream>

#include "rq_group.hpp"

int main(int argc, char** argv)
{
//    std::vector<int> xs = { 10, 5, 7, 3, 5, 9, 6, 9, 2, 4 };

    std::vector<int> xs;

    for(int i = 1; i <= 10; i++) {
        xs.push_back(i);
    }

    seg::rq_group sum(xs);

    for(int l = 1; l <= sum.size(); l++) {
        for(int i = 0; i <= sum.size() - l; i++) {
            std::cout << sum.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }

    std::vector<float> ys;

    for(int i = 1; i <= 10; i++) {
        ys.push_back(i);
    }

    seg::rq_group<float, seg::fx::multiplication<float>> prod(ys);

    for(int l = 1; l <= prod.size(); l++) {
        for(int i = 0; i <= prod.size() - l; i++) {
            std::cout << prod.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }
}
