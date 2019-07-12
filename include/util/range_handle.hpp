
#ifndef SEGTREE_RANGE_HANDLE_HPP
#define SEGTREE_RANGE_HANDLE_HPP

namespace seg::util {

template<typename Parent>
class range_handle
{
    using index_type = typename Parent::index_type;
    using value_type = typename Parent::value_type;

    Parent& parent;
    const index_type i_begin, i_end;

public:
    range_handle(Parent& parent, const index_type i_begin, const index_type i_end) : parent(parent),
                                                                                    i_begin(i_begin), i_end(i_end) { }


    range_handle& operator=(const value_type& x)
    {
        parent.set(i_begin, i_end, x);

        return *this;
    }

    range_handle& operator+=(const value_type& x)
    {
        parent.add(i_begin, i_end, x);

        return *this;
    }

    // TODO: Expose operator-= if the parent's Semi is actually a group.
};

}

#endif //SEGTREE_RANGE_HANDLE_HPP
