
#ifndef SEGTREE_ELEM_HANDLE_HPP
#define SEGTREE_ELEM_HANDLE_HPP

namespace seg::util {

template<typename Parent>
class elem_handle
{
    using index_type = typename Parent::index_type;
    using value_type = typename Parent::value_type;

    Parent& parent;
    const index_type i;

public:
    __unused elem_handle(Parent& parent, const index_type i) : parent(parent), i(i) { }

    /**
     * The const version of operator[](index_type) may return either T or const T&, depending on the data structure.
     */
    using parent_el_type = decltype(const_cast<const Parent&>(parent)[index_type{}]);

    operator parent_el_type() const // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    {
        return const_cast<const Parent&>(parent)[i];
    }

    elem_handle& operator=(const value_type& value)
    {
        parent.set(i, value);

        return *this;
    }

    elem_handle& operator+=(const value_type& value)
    {
        return operator=(*this + value);
    }

    elem_handle& operator-=(const value_type& value)
    {
        return operator=(*this - value);
    }

    elem_handle& operator*=(const value_type& value)
    {
        return operator=(*this * value);
    }

    elem_handle& operator/=(const value_type& value)
    {
        return operator=(*this / value);
    }

    elem_handle& operator%=(const value_type& value)
    {
        return operator=(*this % value);
    }

    elem_handle& operator&=(const value_type& value)
    {
        return operator=(*this & value);
    }

    elem_handle& operator|=(const value_type& value)
    {
        return operator=(*this | value);
    }

    elem_handle& operator^=(const value_type& value)
    {
        return operator=(*this ^ value);
    }

    elem_handle& operator<<=(const value_type& value)
    {
        return operator=(*this << value);
    }

    elem_handle& operator>>=(const value_type& value)
    {
        return operator=(*this >> value);
    }
};

}

#endif //SEGTREE_ELEM_HANDLE_HPP
