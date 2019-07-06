#include <iostream>

#include "baseline/rq_mode_slow.hpp"

int main(int argc, char** argv)
{
    const std::vector<int> xs = { 3, 3, 5, 0, 0, 1, 3, 1, 4 };

    seg::baseline::rq_mode_slow<int> m_slow(xs);

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j < xs.size(); j++) {
            std::cout << m_slow.get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
