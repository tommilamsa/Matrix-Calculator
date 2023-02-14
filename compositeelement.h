/**
    \file compositeelement.h
    \brief Header for CompositeElement class
*/
#ifndef COMPOSITEELEMENT_H_INCLUDED
#define COMPOSITEELEMENT_H_INCLUDED
#include "element.h"
#include <functional>

/**
    \class CompositeElement
    \brief CompositeElement class
*/
class CompositeElement : public Element
{
    private:
        std::shared_ptr<Element> oprnd1;
        std::shared_ptr<Element> oprnd2;
        std::function<int(int,int)> op_fun;
        char op_ch;
    public:

        /**
            \brief Parametric constructor
            \param e1 Element object
            \param e2 Element object
            \param op Function object used for integer operations
            \param opc Character representing operation to perform
        */
        CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc);

        /**
            \brief Copy constructor
            \param e CompositeElement to copy
        */
        CompositeElement(const CompositeElement& e);

        /**
            \brief Assignment operator
            \param e CompositeElement to assign
            \return Assigned object
        */
        CompositeElement& operator=(const CompositeElement& e);

        /**
            \brief Destructor
        */
        virtual ~CompositeElement() = default;

        /**
            \brief Return a pointer to a copy of CompositeElement
            \return Pointer to copy
        */
        Element* clone() const override;

        /**
            \brief Makes string representation of CompositeElement
            \return The string representation
        */
        std::string toString() const override;

        /**
            \brief Evaluate variable
            \param v map where variable values are stored
            \return Result of evaluation
        */
        int evaluate(const Valuation& v) const override;
};

#endif // COMPOSITEELEMENT_H_INCLUDED
