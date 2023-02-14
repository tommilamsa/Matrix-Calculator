/**
    \file element.h
    \brief Header for Element abstract class
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include <memory>
#include <string>
#include <ostream>
#include <map>

/**
    \brief Map object used for variable evaluation
*/
using Valuation = std::map<char,int>;

/**
    \class Element
    \brief Element abstract class
*/
class Element
{
    public:

        /**
            \brief Destructor
        */
        virtual ~Element() = default;

        /**
            \brief Return a pointer to a copy of Element
            \return Pointer
        */
        virtual Element* clone() const = 0;

        /**
            \brief Makes string representation of Element
            \return The string representation
        */
        virtual std::string toString() const = 0;

        /**
            \brief Evaluate variable
            \param v map where variable values are stored
            \return Result of evaluation
        */
        virtual int evaluate(const Valuation& v) const = 0;
};

/**
    \class TElement
    \brief Element template class, becomes IntElement with integer value and VariableElement with character value
    \tparam T Type of value for element
*/
template <typename T>
class TElement : public Element
{
    private:
        T val;
    public:

        /**
            \brief Default constructor
        */
        TElement(): val(0){};

        /**
            \brief Parametric constructor
            \param t value to store in object
        */
        TElement(T t): val(t){};

        /**
            \brief Destructor
        */
        virtual ~TElement() = default;

        /**
            \brief Function to get value from object
            \return Value of object
        */
        T getVal()
        {
            return val;
        };

        /**
            \brief Function to set a new value to object
            \param t new value to store in object
        */
        void setVal(T t)
        {
            val = t;
        };

        /**
            \brief Return the pointer to a copy of TElement
            \return Pointer to copy
        */
        Element* clone() const override
        {
            return new TElement<T>(val);
        };

        /**
            \brief Makes string representation of TElement
            \return The string representation
        */
        std::string toString() const override;

        /**
            \brief Evaluate value
            \param v map where variable values are stored
            \return Result of evaluation
        */
        int evaluate(const Valuation& v) const override;

        /**
            \brief Operator for value addition
            \param i value to add
            \return Result of addition
        */
        TElement<T>& operator+=(const TElement<T>& i);

        /**
            \brief Operator for value subtraction
            \param i value to subtract
            \return Result of subtraction
        */
        TElement<T>& operator-=(const TElement<T>& i);

        /**
            \brief Operator for value multiplication
            \param i value to multiply with
            \return Result of multiplication
        */
        TElement<T>& operator*=(const TElement<T>& i);
};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

/**
    \brief Output operator
    \param os stream to print in
    \param i reference to Element object
*/
std::ostream& operator<<(std::ostream& os, const Element& i);

/**
    \brief Operator to compare to elements
    \param i first element to compare
    \param j second element to compare
    \return true if elements the same
    \return false if elements not the same
*/
bool operator==(const Element& i, const Element& j);

/**
    \brief Operator for integer addition
    \param i first member of product
    \param j second member of product
    \return Result of addition
*/
IntElement operator+(const IntElement& i, const IntElement& j);

/**
    \brief Operator for integer subtraction
    \param i first member of product
    \param j second member of product
    \return Result of subtraction
*/
IntElement operator-(const IntElement& i, const IntElement& j);

/**
    \brief Operator for integer multiplication
    \param i first member of product
    \param j second member of product
    \return Result of multiplication
*/
IntElement operator*(const IntElement& i, const IntElement& j);

#endif // ELEMENT_H_INCLUDED
