
#ifndef SEGTREE_SEGTREE_HPP
#define SEGTREE_SEGTREE_HPP

#include <memory>
#include <stdexcept>

class segtree
{
private:
    // [l, m), [m, r)
    int l, m, r;

    std::unique_ptr<segtree> left = nullptr;
    std::unique_ptr<segtree> right = nullptr;

protected:
    int sum = 0;

public:
    segtree(const int l, const int r) : l(l), r(r), m(l + (r - l + 1) / 2) { }

    void set(const int i, const int x) {
        if(i < l || i >= r) {
            throw std::invalid_argument(
                    "Index " + std::to_string(i) + " is out of tree's range:" +
                    " [" + std::to_string(l) + ", " + std::to_string(r) + ")"
            );
        }
        if(i == l && i + 1 == r) {
            sum = x;
        }
        else {
            if(i < m) {
                if(!left) {
                    left = std::make_unique<segtree>(l, m);
                }

                const int s_old = left->sum;

                left->set(i, x);

                sum += left->sum - s_old;
            }
            else if(i >= m) {
                if(!right) {
                    right = std::make_unique<segtree>(m, r);
                }

                const int s_old = right->sum;

                right->set(i, x);

                sum += right->sum - s_old;
            }
        }
    }

    int get_sum(const int a, const int b) const
    {
        if(a >= b) {
            return 0;
        }
        else if(a == l && b == r) {
            return sum;
        }
        else {
            int result = 0;

            if(a < m && left) {
                result += left->get_sum(a, std::min(m, b));
            }

            if(b >= m && right) {
                result += right->get_sum(std::max(a, m), b);
            }

            return result;
        }
    }
};

#endif //SEGTREE_SEGTREE_HPP
