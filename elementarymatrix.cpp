/**
    \file elementarymatrix.cpp
    \brief Code for ElementarySquareMatrix class functions
*/

#include "elementarymatrix.h"

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator+=(const ElementarySquareMatrix<IntElement>& m)
{
    try
    {
        if(n != m.n)
        {
            throw m;
        }
        else
        {
            for(unsigned int i = 0; i < n; i++)
            {
                unsigned int j = 0;
                for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++, j++)
                {
                    *elements[i][j] += *(*iter);
                }
            }
        }
    }
    catch(ElementarySquareMatrix<IntElement>& m)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }

    return *this;
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator-=(const ElementarySquareMatrix<IntElement>& m)
{
    try
    {
        if(n != m.n)
        {
            throw m;
        }
        else
        {
            for(unsigned int i = 0; i < n; i++)
            {
                unsigned int j = 0;
                for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++, j++)
                {
                    *elements[i][j] -= *(*iter);
                }
            }
        }
    }
    catch(ElementarySquareMatrix<IntElement>& m)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }

    return *this;
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator*=(const ElementarySquareMatrix<IntElement>& m)
{
    try
    {
        if(n != m.n)
        {
            throw m;
        }
        else
        {
            std::vector<std::vector<std::shared_ptr<IntElement>>> temp;
            std::vector<std::shared_ptr<IntElement>> vec;
            ConcreteSquareMatrix sq = m.transpose();
            IntElement elem(0);
            unsigned int i = 0;
            unsigned int j = 0;

            while(i < n)
            {
                temp.push_back(vec);
                i++;
            }

            for(i = 0; i < n; i++)
            {
                for(j = 0; j < n; j++)
                {
                    auto iter1 = elements[i].begin();
                    auto iter2 = sq.elements[j].begin();
                    for( ; iter1 != elements[i].end(); iter1++, iter2++)
                    {
                        elem += *(*iter1) * *(*iter2);
                    }
                    temp[i].push_back(std::shared_ptr<IntElement>(static_cast<IntElement*>(elem.clone())));
                    elem.setVal(0);
                }
            }
            elements = temp;
        }
    }
    catch(ElementarySquareMatrix<IntElement>& m)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    return *this;
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator+(const ElementarySquareMatrix<Element>& m)
{
    SymbolicSquareMatrix sq;
    std::vector<std::vector<std::shared_ptr<Element>>> elems;
    std::vector<std::shared_ptr<Element>> row;
    unsigned int i = 0;
    unsigned int j = 0;

    if(n != m.n)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    else
    {
        while(i < n)
        {
            elems.push_back(row);
            i++;
        }
        for(i = 0; i < n; i++)
        {
            j = 0;
            for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++, j++)
            {
                CompositeElement com_elem(*elements[i][j], *(*iter), std::plus<int>(), '+');
                elems[i].push_back(std::shared_ptr<Element>(static_cast<Element*>(com_elem.clone())));
            }
        }
        sq.setVector(elems);
        return sq;
    }
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator-(const ElementarySquareMatrix<Element>& m)
{
    SymbolicSquareMatrix sq;
    std::vector<std::vector<std::shared_ptr<Element>>> elems;
    std::vector<std::shared_ptr<Element>> row;
    unsigned int i = 0;
    unsigned int j = 0;

    if(n != m.n)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    else
    {
        while(i < n)
        {
            elems.push_back(row);
            i++;
        }
        for(i = 0; i < n; i++)
        {
            j = 0;
            for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++, j++)
            {
                CompositeElement com_elem(*elements[i][j], *(*iter), std::minus<int>(), '-');
                elems[i].push_back(std::shared_ptr<Element>(static_cast<Element*>(com_elem.clone())));
            }
        }
        sq.setVector(elems);
        return sq;
    }
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator*(const ElementarySquareMatrix<Element>& m)
{
    SymbolicSquareMatrix sq;
    SymbolicSquareMatrix test = m.transpose();
    std::vector<std::vector<std::shared_ptr<Element>>> elems;
    std::vector<std::shared_ptr<Element>> row;
    std::vector<std::shared_ptr<Element>> temp;
    unsigned int i = 0;
    unsigned int j = 0;

    if(n != m.n)
    {
        throw std::invalid_argument("Matrices are not the same size");
    }
    else
    {
        while(i < n)
        {
            elems.push_back(row);
            i++;
        }
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                auto iter1 = elements[i].begin();
                auto iter2 = test.elements[j].begin();
                for( ; iter1 != elements[i].end(); iter1++, iter2++)
                {
                    CompositeElement com_elem(*(*iter1), *(*iter2), std::multiplies<int>(), '*');
                    elems[i].push_back(std::shared_ptr<Element>(static_cast<Element*>(com_elem.clone())));
                }
            }
        }
    }
    sq.setVector(elems);
    return sq;
}

template<>
bool ElementarySquareMatrix<IntElement>::isSquareMatrix(const std::string& s)
{
    std::vector<std::shared_ptr<IntElement>> row;
    std::istringstream strm(s);
    std::string line;
    std::string nums;
    unsigned int i = 0;
    unsigned int j = 0;
    n = 0;
    int number;
    char c;

    strm >> c;
    if(c != '[')
        throw false;
    strm >> c;
    if(c != '[')
        throw false;

    while(!strm.eof())
    {
        elements.push_back(row);
        j = 0;

        std::getline(strm, line, ']');
        if((line.find(',') == std::string::npos) && (line != ""))
        {
            try
            {
                number = std::stoi(line);
                std::shared_ptr<IntElement> elem_ptr(new IntElement(number));
                elements[i].push_back(elem_ptr);
            }
            catch(const std::invalid_argument& ia)
            {
                throw false;
            }
            j++;
        }
        else if (line.find(',') != std::string::npos)
        {
            std::istringstream line_temp(line);
            while(!line_temp.eof())
            {
                std::getline(line_temp, nums, ',');
                try
                {
                    number = std::stoi(nums);
                    std::shared_ptr<IntElement> elem_ptr(new IntElement(number));
                    elements[i].push_back(elem_ptr);
                }
                catch(const std::invalid_argument& ia)
                {
                    throw false;
                }
                j++;
            }
        }

        if (n == 0)
        {
            n = j;
            strm >> c;
            i++;
        }
        else if(n != j && line != "")
        {
            throw false;
        }
        else
        {
            strm >> c;
            if(n != 1)
            {
                i++;
            }

            if(strm.str().back() == ']')
            {
                if(i == n)
                {
                    strm >> c;
                    if(c != ']')
                    {
                        throw false;
                    }
                    else if(strm.eof())
                    {
                        return true;
                    }
                }
            }
        }
    }
    throw false;
}

template<>
bool ElementarySquareMatrix<Element>::isSquareMatrix(const std::string& s)
{
    std::vector<std::shared_ptr<Element>> row;
    std::istringstream strm(s);
    std::string line;
    std::string nums;
    unsigned int i = 0;
    unsigned int j = 0;
    n = 0;
    int number;
    char character;
    char c;

    strm >> c;
    if(c != '[')
        throw false;
    strm >> c;
    if(c != '[')
        throw false;

    while(!strm.eof())
    {
        elements.push_back(row);
        j = 0;

        std::getline(strm, line, ']');
        if((line.find(',') == std::string::npos) && (line != ""))
        {
            try
            {
                number = std::stoi(line);
                std::shared_ptr<Element> elem_ptr(new IntElement(number));
                elements[i].push_back(elem_ptr);
            }
            catch(const std::invalid_argument& ia)
            {
                try
                {
                    if(line.size() > 1)
                    {
                        throw false;
                    }

                    character = line[0];
                    if(std::isalpha(character) == false)
                    {
                        throw false;
                    }

                    std::shared_ptr<Element> var_ptr(new VariableElement(character));
                    elements[i].push_back(var_ptr);
                }
                catch(bool incorrect)
                {
                    throw false;
                }
            }
            j++;
        }
        else if (line.find(',') != std::string::npos)
        {
            std::istringstream line_temp(line);
            while(!line_temp.eof())
            {
                std::getline(line_temp, nums, ',');
                try
                {
                    number = std::stoi(nums);
                    std::shared_ptr<Element> elem_ptr(new IntElement(number));
                    elements[i].push_back(elem_ptr);
                }
                catch(const std::invalid_argument& ia)
                {
                    try
                    {
                        if(nums.size() > 1)
                        {
                            throw false;
                        }

                        character = nums[0];
                        if(std::isalpha(character) == false)
                        {
                            throw false;
                        }

                        std::shared_ptr<Element> var_ptr(new VariableElement(character));
                        elements[i].push_back(var_ptr);
                    }
                    catch(bool incorrect)
                    {
                        throw false;
                    }
                }
                j++;
            }
        }

        if (n == 0)
        {
            n = j;
            strm >> c;
            i++;
        }
        else if(n != j && line != "")
        {
            throw false;
        }
        else
        {
            strm >> c;
            if(n != 1)
            {
                i++;
            }

            if(strm.str().back() == ']')
            {
                if(i == n)
                {
                    strm >> c;
                    if(c != ']')
                    {
                        throw false;
                    }
                    else if(strm.eof())
                    {
                        return true;
                    }
                }
            }
        }
    }
    throw false;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::evaluate(const Valuation& v) const
{
    return *this;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Element>::evaluate(const Valuation& v) const
{
    ElementarySquareMatrix<IntElement> sq;
    unsigned int i = 0;
    int number;
    std::vector<std::vector<std::shared_ptr<IntElement>>> elems;
    std::vector<std::shared_ptr<IntElement>> row;

    while(i < n)
    {
        elems.push_back(row);
        i++;
    }
    i=0;

    for(auto iter1: this->elements)
    {
        for(auto iter2: iter1)
        {
            try
            {
                number = iter2->evaluate(v);
                std::shared_ptr<IntElement> elem_ptr(new IntElement(number));
                elems[i].push_back(elem_ptr);
            }
            catch(...)
            {
                throw std::invalid_argument("Could not do evaluation");
            }
        }
        i++;
    }

    sq.setVector(elems);
    return sq;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator+(const ElementarySquareMatrix<IntElement>& m)
{
    ConcreteSquareMatrix sq{*this};
    ConcreteSquareMatrix matrix{m};
    sq+=matrix;
    return sq;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator-(const ElementarySquareMatrix<IntElement>& m)
{
    ConcreteSquareMatrix sq{*this};
    ConcreteSquareMatrix matrix{m};
    sq-=matrix;
    return sq;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator*(const ElementarySquareMatrix<IntElement>& m)
{
    ConcreteSquareMatrix sq{*this};
    ConcreteSquareMatrix matrix{m};
    sq*=matrix;
    return sq;
}

std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<IntElement>& m)
{
    os << m.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<Element>& m)
{
    os << m.toString();
    return os;
}
