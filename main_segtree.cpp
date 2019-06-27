#include <iostream>

#include "segtree.hpp"

int main(int argc, char** argv)
{
    auto root = std::make_unique<segtree>(0, 10);

    for(int i = 0; i < 10; i++) {
        root->set(i, i);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = 1; j < 11; j++) {
            std::cout << root->get_sum(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < 10; i++) {
        root->set(i, 2 * i);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = 1; j < 11; j++) {
            std::cout << root->get_sum(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
