#include <iostream>
#include <baseline/semi_slow.hpp>

#include "segtree_lazy.hpp"

template<typename Segtree>
void ept(const std::vector<int>& xs)
{
    Segtree tree(xs);

    std::cout << '\t' << tree.get(0, xs.size()) << std::endl;

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j <= xs.size(); j++) {
            std::cout << tree.get(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < xs.size(); i++) {
        tree.set(i, 2 * i);
    }

    std::cout << '\t' << tree.get(0, xs.size()) << std::endl;

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j <= xs.size(); j++) {
            std::cout << tree.get(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename Segtree>
void print_some(Segtree& tree)
{
    for(int i = 0; i < tree.size(); i++) {
        for(int j = i + 1; j <= tree.size(); j++) {
            std::cout << tree.get(i, j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<int> xs(9);

    for(int i = 0; i < xs.size(); i++) {
        xs[i] = i % 2 ? -1 : 1;
    }

//    xs = { 1, 2, 4, 7, 12, 20, 33, 54 };

//    ept<seg::baseline::semi_slow<int>>(xs);
//    ept<seg::segtree_semi<int>>(xs);
//    ept<seg::fenwick_tree<int>>(xs);

//    seg::segtree_lazy<int> hui(xs);

    seg::segtree_lazy<int> hui({ 0, 0, 0, 0, 0, 0, 0 });
//    seg::baseline::semi_slow<int> hui({ 0, 0, 0, 0, 0, 0, 0 });

    print_some(hui);

    hui[5] = 10;
    print_some(hui);

//    hui[5] = hui[5] - 10;
//
//    print_some(hui);
//
//    hui[5] += 7;
//
//    print_some(hui);
//
//    hui[5] *= 10;
//
//    print_some(hui);

    hui.add(0, 4, 7);
    print_some(hui);

    hui[{ 1, 6 }] += -3;
    print_some(hui);

    hui[{ 2, 5 }] += -5;
    print_some(hui);

    hui[{ 3, 5 }] = -11;
    print_some(hui);

    hui[{ 2, 5 }] += 11;
    print_some(hui);

    hui[{ 2, 5 }] += 0;
    print_some(hui);
}
