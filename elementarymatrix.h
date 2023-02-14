/**
    \file elementarymatrix.h
    \brief Header for ElementarySquareMatrix class
*/

#ifndef ELEMENTARYMATRIX_H_INCLUDED
#define ELEMENTARYMATRIX_H_INCLUDED
#include "compositeelement.h"
#include "element.h"
#include "squarematrix.h"
#include <vector>
#include <sstream>

/**
    \class ElementarySquareMatrix
    \brief ElementarySquareMatrix template class (becomes ConcreteSquareMatrix with IntElement objects and SymbolicSquareMatrix with Element objects)
    \tparam T Type of Element-object
*/
template <typename T>
class ElementarySquareMatrix : public SquareMatrix
{
    private:
        unsigned int n;
        std::vector<std::vector<std::shared_ptr<T>>> elements;
    public:

        /**
            \brief Default constructor
        */
        ElementarySquareMatrix(): n(0){};

        /**
            \brief Parametric constructor
            \param str_m string to construct matrix from
            \throw std::invalid_argument if string is invalid
        */
        ElementarySquareMatrix(const std::string& str_m)
        {
                try
            {
                isSquareMatrix(str_m);
            }
            catch (bool error)
            {
                throw std::invalid_argument("String must be in format [[a11,...,a1n]...[an1,...ann]]");
            }
        }

        /**
            \brief Copy constructor
            \param m matrix to copy
        */
        ElementarySquareMatrix(const ElementarySquareMatrix<T>& m)
        {
            std::vector<std::shared_ptr<T>> row;
            n = m.n;

            for(unsigned int i = 0; i < n; i++)
            {
                elements.push_back(row);
                for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++)
                {
                    elements[i].push_back(std::shared_ptr<T>(static_cast<T*>((*(*iter)).clone())));
                }
            }
        }

        /**
            \brief Move constructor
            \param m matrix to move
        */
        ElementarySquareMatrix(ElementarySquareMatrix<T>&& m)
        {
            n = m.n;
            elements = std::move(m.elements);
            m.n = 0;
        }

        /**
            \brief Assignment operator
            \param m matrix to assign
            \return Assigned matrix
        */
        ElementarySquareMatrix<T>& operator=(const ElementarySquareMatrix<T>& m)
        {
            if(*this == m)
            {
                return *this;
            }

            std::vector<std::shared_ptr<T>> row;
            elements.clear();
            n = m.n;

            for(unsigned int i = 0; i < n; i++)
            {
                elements.push_back(row);
                for(auto iter = m.elements[i].begin(); iter != m.elements[i].end(); iter++)
                {
                    elements[i].push_back(std::shared_ptr<T>(static_cast<T*>((*(*iter)).clone())));
                }
            }
            return *this;
        }

        /**
            \brief Move assignment operator
            \param m matrix to move
            \return Moved matrix
        */
        ElementarySquareMatrix<T>& operator=(ElementarySquareMatrix<T>&& m)
        {
            if(*this == m)
            {
                return *this;
            }

            elements = std::move(m.elements);
            n = m.n;
            m.n = 0;
            return *this;
        }

        /**
            \brief Function to get transpose of matrix
            \return Transposed matrix
        */
        ElementarySquareMatrix<T> transpose() const
        {
            std::vector<std::vector<std::shared_ptr<T>>> trans_elements;
            std::vector<std::shared_ptr<T>> row;
            ElementarySquareMatrix<T> sq;
            unsigned int i = 0;

            while (i < n)
            {
                trans_elements.push_back(row);
                i++;
            }

            for(auto iter1: this->elements)
            {
                i = 0;
                for(auto iter2: iter1)
                {
                    trans_elements[i].push_back(std::shared_ptr<T>(static_cast<T*>((iter2->clone()))));
                    i++;
                }
            }

            sq.setVector(trans_elements);
            return sq;
        }

        /**
            \brief Function to set new vector to matrix
            \param elems new vector to set
        */
        void setVector(std::vector<std::vector<std::shared_ptr<T>>> elems)
        {
            elements = elems;
            n = elements.size();
        }

        /**
            \brief Operator to compare two matrices
            \param m matrix to compare with
            \return true if matrices are same
            \return false if matrices are not same
        */
        bool operator==(const ElementarySquareMatrix<T>& m) const
        {
            std::string matrix1 = toString();
            std::string matrix2 = m.toString();
            if(matrix1 == matrix2)
                return true;
            else
                return false;
        }

        /**
            \brief Function to print square matrix
            \param os stream to print in
        */
        void print(std::ostream& os)
        {
            os << toString();
        }

        /**
            \brief Makes a string representation of ElementarySquareMatrix
            \return The string representation
        */
        std::string toString() const override
        {
            std::stringstream strm;

            strm << "[";
            for(auto iter1 = elements.begin(); iter1 != elements.end(); iter1++)
            {
                strm << "[";
                for(auto iter2 = iter1->begin(); iter2 != iter1->end(); iter2++)
                {
                    strm << (*iter2)->toString();
                    if(iter2+1 != iter1->end())
                    {
                        strm << ",";
                    }
                }
                strm << "]";
            }
            strm << "]";
            return strm.str();
        }

        /**
            \brief Destructor
        */
        virtual ~ElementarySquareMatrix() = default;

        /**
            \brief Operator for ConcreteSquareMatrix addition
            \param m ConcreteSquareMatrix to add
            \throw std::invalid_argument if matrices are not the same size
            \return Result of addition
        */
        ElementarySquareMatrix<T>& operator+=(const ElementarySquareMatrix<T>& m);

        /**
            \brief Operator for ConcreteSquareMatrix subtraction
            \param m ConcreteSquareMatrix to subtract
            \throw std::invalid_argument if matrices are not the same size
            \return Result of subtraction
        */
        ElementarySquareMatrix<T>& operator-=(const ElementarySquareMatrix<T>& m);

        /**
            \brief Operator for ConcreteSquareMatrix multiplication
            \param m ConcreteSquareMatrix to multiply with
            \throw std::invalid_argument if matrices are not the same size
            \return Result of multiplication
        */
        ElementarySquareMatrix<T>& operator*=(const ElementarySquareMatrix<T>& m);

        /**
            \brief Operator for ElementarySquareMatrix addition
            \param m ElementarySquareMatrix to add
            \throw std::invalid_argument if matrices are not the same size
            \return Result of addition
        */
        ElementarySquareMatrix<T> operator+(const ElementarySquareMatrix<T>& m);

        /**
            \brief Operator for ElementarySquareMatrix subtraction
            \param m ElementarySquareMatrix to subtract
            \throw std::invalid_argument if matrices are not the same size
            \return Result of subtraction
        */
        ElementarySquareMatrix<T> operator-(const ElementarySquareMatrix<T>& m);

        /**
            \brief Operator for ElementarySquareMatrix multiplication
            \param m ElementarySquareMatrix to multiply with
            \throw std::invalid_argument if matrices are not the same size
            \return Result of multiplication
        */
        /* Note: Multiplication for SymbolicSquareMatrix does not work properly*/
        ElementarySquareMatrix<T> operator*(const ElementarySquareMatrix<T>& m);

        /**
            \brief Function to check if string is a square matrix
            \param s string to check
            \throw false if string is not a square matrix
            \return true if string is a square matrix
        */
        bool isSquareMatrix(const std::string& s);

        /**
            \brief Evaluate variables in SymbolicSquareMatrix
            \param v map where variable values are stored
            \throw std::invalid_argument if evaluation cannot be done
            \return ConcreteSquareMatrix object
        */
        ElementarySquareMatrix<IntElement> evaluate(const Valuation& v) const;

};

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

/**
    \brief Output operator
    \param os stream to output in
    \param m reference to ElementarySquareMatrix object
*/
std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<IntElement>& m);

/**
    \brief Output operator
    \param os stream to output in
    \param m reference to ElementarySquareMatrix object
*/
std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<Element>& m);



#endif // ELEMENTARYMATRIX_H_INCLUDED
