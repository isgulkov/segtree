#include <iostream>

#include "baseline/rq_mode_slow.hpp"

int main(int argc, char** argv)
{
    const std::vector<int> xs = { 3, 3, 5, 0, 0, 1, 3, 1, 4 };

    seg::baseline::rq_mode_slow<int> ms(xs);

    for(int i = 0; i < ms.size(); i++) {
        for(int j = i + 1; j <= ms.size(); j++) {
            const auto v = ms.get(i, j);

            std::cout << (v ? std::to_string(v.value()) : "_") << " ";
        }
        std::cout << std::endl;
    }
}
