#include <iostream>

#include "baseline/semi_slow.hpp"
#include "segtree_semi.hpp"
#include "fenwick_tree.hpp"

template<typename Segtree>
void ept(const std::vector<int>& xs)
{
    Segtree tree(xs);

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 11; j++) {
            std::cout << tree.get(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < 10; i++) {
        tree.set(i, 2 * i);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 11; j++) {
            std::cout << tree.get(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<int> xs(10);

    for(int i = 0; i < 10; i++) {
        xs[i] = i;
    }

    ept<seg::baseline::semi_slow<int>>(xs);
    ept<seg::segtree_semi<int>>(xs);
    ept<seg::fenwick_tree<int>>(xs);
}
