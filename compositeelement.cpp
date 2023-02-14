/**
    \file compositeelement.cpp
    \brief Code for CompositeElement class
*/

#include "compositeelement.h"
#include <sstream>

CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc)
{
    oprnd1 = std::shared_ptr<Element>(static_cast<Element*>(e1.clone()));
    oprnd2 = std::shared_ptr<Element>(static_cast<Element*>(e2.clone()));
    op_fun = op;

    if(opc == '+' || opc == '-' || opc == '*')
    {
        op_ch = opc;
    }
    else
    {
        throw std::invalid_argument("Symbol must be +, - or *");
    }
}

CompositeElement::CompositeElement(const CompositeElement& e)
{
    oprnd1 = e.oprnd1;
    oprnd2 = e.oprnd2;
    op_fun = e.op_fun;
    op_ch = e.op_ch;
}

CompositeElement& CompositeElement::operator=(const CompositeElement& e)
{
    oprnd1 = e.oprnd1;
    oprnd2 = e.oprnd2;
    op_fun = e.op_fun;
    op_ch = e.op_ch;

    return *this;
}

Element* CompositeElement::clone() const
{
    return new CompositeElement(*this);
}

std::string CompositeElement::toString() const
{
    std::stringstream strm;
    strm << '(' << *oprnd1 << op_ch << *oprnd2 << ')';
    return strm.str();
}

int CompositeElement::evaluate(const Valuation& v) const
{
    return op_fun(oprnd1->evaluate(v), oprnd2->evaluate(v));
}
