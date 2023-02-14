/**
    \file squarematrix.h
    \brief Header for SquareMatrix abstract class
*/

#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED
#include "element.h"

template <typename T>
class ElementarySquareMatrix;

/**
    \class SquareMatrix
    \brief SquareMatrix abstract class
*/
class SquareMatrix
{
    public:

        /**
            \brief Destructor
        */
        virtual ~SquareMatrix() = default;

        /**
            \brief Returns string representation of matrix
            \return The string representation
        */
        virtual std::string toString() const = 0;

        /**
            \brief Evaluate variables in SquareMatrix
            \param v map where variable values are stored
            \throw std::invalid_argument if evaluation cannot be done
            \return ConcreteSquareMatrix object
        */
        virtual ElementarySquareMatrix<IntElement> evaluate(const Valuation& v) const = 0;
};

#endif // SQUAREMATRIX_H_INCLUDED
