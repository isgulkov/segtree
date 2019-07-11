
#ifndef SEGTREE__ELEM_HANDLE_HPP
#define SEGTREE__ELEM_HANDLE_HPP

namespace seg::util {

template<typename Parent, typename T>
class _elem_handle
{
    Parent& parent;
    size_t i;

    /**
     * TODO: get the T out of the Parent one way or another:
     *  - Parent::value_type
     *  - seg::hz_traits<Parent>::value_type
     *  (here and other places, like the tests)
     */

public:
    _elem_handle(Parent& parent, const size_t i) : parent(parent), i(i) { }

    /**
     * The const version of operator[](size_t) may return either T or const T&, depending on the data structure.
     */
    using parent_el_type = decltype(const_cast<const Parent&>(parent)[size_t{}]);

    operator parent_el_type() const // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    {
        return const_cast<const Parent&>(parent)[i];
    }

    _elem_handle& operator=(const T& value)
    {
        parent.set(i, value);

        return *this;
    }

    _elem_handle& operator+=(const T& value)
    {
        return operator=(*this + value);
    }

    _elem_handle& operator-=(const T& value)
    {
        return operator=(*this - value);
    }

    _elem_handle& operator*=(const T& value)
    {
        return operator=(*this * value);
    }

    _elem_handle& operator/=(const T& value)
    {
        return operator=(*this / value);
    }

    _elem_handle& operator%=(const T& value)
    {
        return operator=(*this % value);
    }

    _elem_handle& operator&=(const T& value)
    {
        return operator=(*this & value);
    }

    _elem_handle& operator|=(const T& value)
    {
        return operator=(*this | value);
    }

    _elem_handle& operator^=(const T& value)
    {
        return operator=(*this ^ value);
    }

    _elem_handle& operator<<=(const T& value)
    {
        return operator=(*this << value);
    }

    _elem_handle& operator>>=(const T& value)
    {
        return operator=(*this >> value);
    }
};

}

#endif //SEGTREE__ELEM_HANDLE_HPP
