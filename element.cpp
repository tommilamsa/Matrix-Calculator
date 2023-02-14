/**
    \file element.cpp
    \brief Code for Element abstract class and TElement template class
*/

#include "element.h"
#include <sstream>

template<>
std::string TElement<int>::toString() const
{
    std::stringstream strm;
    strm << val;
    return strm.str();
}

template<>
std::string TElement<char>::toString() const
{
    std::stringstream strm;
    strm << val;
    return strm.str();
}

template<>
int TElement<int>::evaluate(const Valuation& v) const
{
    return val;
}

template<>
int TElement<char>::evaluate(const Valuation& v) const
{
    auto iter = v.find(val);

    if(iter != v.end())
    {
        return iter->second;
    }

    throw "Could not find variable";
}

template<>
TElement<int>& TElement<int>::operator+=(const TElement<int>& i)
{
    val = val + i.val;
    return *this;
}

template<>
TElement<int>& TElement<int>::operator-=(const TElement<int>& i)
{
    val = val - i.val;
    return *this;
}

template<>
TElement<int>& TElement<int>::operator*=(const TElement<int>& i)
{
    val = val * i.val;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Element& i)
{
    os << i.toString();
    return os;
}

bool operator==(const Element& i, const Element& j)
{
    if(i.toString() == j.toString())
        return true;
    else
        return false;
}

IntElement operator+(const IntElement& i, const IntElement& j)
{
    IntElement element{i};
    element+=j;
    return element;
}

IntElement operator-(const IntElement& i, const IntElement& j)
{
    IntElement element{i};
    element-=j;
    return element;
}

IntElement operator*(const IntElement& i, const IntElement& j)
{
    IntElement element{i};
    element*=j;
    return element;
}
