#include <iostream>
#include <iomanip>

#include "baseline/rq_mode_slow.hpp"
#include "rq_mode_compact.hpp"

int main(int argc, char** argv)
{
    const std::vector<int> xs = { 3, 3, 5, 0, 0, 1, 3, 1, 4, 1, 1 };
//    const std::vector<int> xs = { 1, 0, 0, 1, 1, 1, 1 };
//    const std::vector<int> xs = { 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };

    seg::baseline::rq_mode_slow<int> ms(xs);

    for(int i = 0; i < ms.size(); i++) {
        for(int j = i + 1; j <= ms.size(); j++) {
            const auto v = ms.get(i, j);

            std::cout << std::setw(3) << (v ? std::to_string(v.value()) : "___") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    seg::rq_mode_compact<int> mf(xs);

    for(int i = 0; i < mf.size(); i++) {
        for(int j = i + 1; j <= mf.size(); j++) {
            const auto v = mf.get(i, j);

            std::cout << std::setw(3) << (v ? std::to_string(v.value()) : "___") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
