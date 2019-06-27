#include <iostream>

#include "rmq_fast.hpp"
#include "rmq_compact.hpp"

/**
 * Range queries:
 * - `rmq_fast`: O(1) query, O(nlogn) space, no update
 * - `rmq_compact`: O(logn) query, O(n) space, O(logn) single update, O(logn) range update (TODO)
 * - `rmq_cartesian`: O(1) query, O(n) space
 * - `rq_group`: O(1) query, O(n) space, O(1) single update -- for group (invertible) operators
 * - `rq_mode`: ...
 * - `rq_median`: ...
 *
 * TODO: use `const T&` instead of T wherever possible depending on a tag
 */

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

    seg::rmq_fast<int, std::greater<>> xs_max(xs.begin(), xs.end());

    for(int l = 1; l <= xs_max.size(); l++) {
        for(int i = 0; i <= xs_max.size() - l; i++) {
            std::cout << xs_max.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }

    seg::rmq_fast<int> ys_min({ 10, 5, 7, 3, 5, 9, 6, 9, 2, 4 });

    for(int l = 1; l <= ys_min.size(); l++) {
        for(int i = 0; i <= ys_min.size() - l; i++) {
            std::cout << ys_min.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }

    seg::rmq_fast<int> ept({});

    seg::rmq_compact<int> zs_min({ 10, 5, 7, 3, 5, 9, 6, 9, 2, 4 });

    for(int l = 1; l <= zs_min.size(); l++) {
        for(int i = 0; i <= zs_min.size() - l; i++) {
            std::cout << zs_min.get(i, i + l) << " ";
        }
        std::cout << std::endl;
    }
}
