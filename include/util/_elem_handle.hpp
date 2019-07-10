
#ifndef SEGTREE__ELEM_HANDLE_HPP
#define SEGTREE__ELEM_HANDLE_HPP

namespace seg::util {

template<typename Parent, typename T>
class _elem_handle
{
    Parent& parent;
    size_t i;

    using elem_handle = _elem_handle<Parent, T>;

public:
    _elem_handle(Parent& parent, const size_t i) : parent(parent), i(i) { }

    operator const T&() const // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    {
        return const_cast<const Parent&>(parent)[i];
    }

    elem_handle& operator=(const T& value)
    {
        parent.set(i, value);

        return *this;
    }

    elem_handle& operator+=(const T& value)
    {
        return operator=(*this + value);
    }

    elem_handle& operator-=(const T& value)
    {
        return operator=(*this - value);
    }

    elem_handle& operator*=(const T& value)
    {
        return operator=(*this * value);
    }

    elem_handle& operator/=(const T& value)
    {
        return operator=(*this / value);
    }

    elem_handle& operator%=(const T& value)
    {
        return operator=(*this % value);
    }

    elem_handle& operator&=(const T& value)
    {
        return operator=(*this & value);
    }

    elem_handle& operator|=(const T& value)
    {
        return operator=(*this | value);
    }

    elem_handle& operator^=(const T& value)
    {
        return operator=(*this ^ value);
    }

    elem_handle& operator<<=(const T& value)
    {
        return operator=(*this << value);
    }

    elem_handle& operator>>=(const T& value)
    {
        return operator=(*this >> value);
    }
};

}

#endif //SEGTREE__ELEM_HANDLE_HPP
