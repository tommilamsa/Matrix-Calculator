/**
    \file main.cpp
    \brief Main-function and tests for IntElement, VariableElement, CompositeElement, ConcreteSquareMatrix and SymbolicSquareMatrix classes
*/

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "elementarymatrix.h"
#include <stack>
#include <iostream>

TEST_CASE("IntElement constructor tests", "[value]")
{
    IntElement e1;
    CHECK(e1.getVal() == 0);
    IntElement e2(15);
    CHECK(e2.getVal() == 15);
    e1.setVal(21);
    CHECK(e1.getVal() == 21);
}

TEST_CASE("IntElement operator tests", "[value]")
{
    IntElement e1(21);
    IntElement e2(15);
    e1+=e2;
    CHECK(e1.getVal() == 36);
    e1-=e2;
    CHECK(e1.getVal() == 21);
    e1*=e2;
    CHECK(e1.getVal() == 315);
    IntElement e3 = e1 + e2;
    CHECK(e3.getVal() == 330);
    IntElement e4 = e3 - e1;
    CHECK(e4.getVal() == 15);
    bool test = (e2 == e4);
    CHECK(test);
    test = (e3 == e4);
    CHECK_FALSE(test);
    IntElement e5 = e3 * e4;
    CHECK(e5.getVal() == 4950);
    CHECK(e5.toString() == "4950");
    Valuation v;
    int i = e5.evaluate(v);
    CHECK(i == 4950);
}

TEST_CASE("VariableElement constructor tests", "[character]")
{
    VariableElement v1('y');
    CHECK(v1.toString() == "y");
    v1.setVal('z');
    CHECK(v1.toString() == "z");
    char test = v1.getVal();
    CHECK(test == 'z');
}

TEST_CASE("VariableElement operator tests", "[character]")
{
    VariableElement v1('x');
    VariableElement v2('x');
    bool test = (v1 == v2);
    CHECK(test);
    v1.setVal('y');
    test = (v1 == v2);
    CHECK_FALSE(test);
    Valuation v;
    v['x'] = 10;
    v['y'] = 4;
    int i = v1.evaluate(v);
    int j = v2.evaluate(v);
    CHECK(i == 4);
    CHECK(j == 10);
}

TEST_CASE("CompositeElement constructor tests", "[value]")
{
    IntElement e1(20);
    VariableElement e2('x');
    CompositeElement elem(e1, e2, std::plus<int>(), '+');
    CHECK(elem.toString() == "(20+x)");
    CompositeElement copy_elem(elem);
    CHECK(copy_elem.toString() == "(20+x)");
    CHECK_THROWS(CompositeElement(e1, e2, std::plus<int>(), 'a'));
}

TEST_CASE("CompositeElement operator tests", "[value]")
{
    IntElement e1(20);
    VariableElement e2('x');
    Valuation v;
    v['x'] = 15;
    CompositeElement elem1(e1, e2, std::plus<int>(), '+');
    CompositeElement copy_elem(e1, e2, std::minus<int>(), '-');
    CHECK(elem1.toString() == "(20+x)");
    CHECK(copy_elem.toString() == "(20-x)");
    copy_elem = elem1;
    CHECK(copy_elem.toString() == "(20+x)");
    int test = elem1.evaluate(v);
    CHECK(test == 35);
    CompositeElement elem2(e1, e2, std::minus<int>(), '-');
    test = elem2.evaluate(v);
    CHECK(test == 5);
    CompositeElement elem3(e1, e2, std::multiplies<int>(), '*');
    test = elem3.evaluate(v);
    CHECK(test == 300);
}

TEST_CASE("Element comparison tests", "[value]")
{
    IntElement e1(10);
    VariableElement e2('x');
    CompositeElement e3(e1, e2, std::plus<int>(), '+');
    bool test = (e1 == e2);
    CHECK_FALSE(test);
    test = (e1 == e3);
    CHECK_FALSE(test);
    test = (e2 == e3);
    CHECK_FALSE(test);
}

TEST_CASE("Concrete square matrix constructor tests", "[string]")
{
    ConcreteSquareMatrix sq1;
    CHECK(sq1.toString() == "[]");
    ConcreteSquareMatrix sq2("[[13,4,7][2,51,12][11,30,9]]");
    CHECK(sq2.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    ConcreteSquareMatrix sq3(sq2);
    bool test = (sq2 == sq3);
    CHECK(test);
    ConcreteSquareMatrix sq4(std::move(sq2));
    CHECK(sq4.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    CHECK(sq2.toString() == "[]");
}

TEST_CASE("Concrete square matrix operator tests", "[string]")
{
    ConcreteSquareMatrix sq1;
    ConcreteSquareMatrix sq2("[[13,4,7][2,51,12][11,30,9]]");
    sq1 = std::move(sq2);
    CHECK(sq1.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    CHECK(sq2.toString() == "[]");
    sq2 = sq1;
    CHECK(sq2.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    CHECK(sq1.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    ConcreteSquareMatrix sq3 = sq1.transpose();
    CHECK(sq3.toString() == "[[13,2,11][4,51,30][7,12,9]]");
    sq2+=sq3;
    CHECK(sq2.toString() == "[[26,6,18][6,102,42][18,42,18]]");
    sq2-=sq3;
    CHECK(sq2.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    sq2*=sq3;
    CHECK(sq2.toString() == "[[234,314,326][314,2749,1660][326,1660,1102]]");
    ConcreteSquareMatrix sq4 = sq1 + sq3;
    CHECK(sq4.toString() == "[[26,6,18][6,102,42][18,42,18]]");
    ConcreteSquareMatrix sq5 = sq4 - sq3;
    CHECK(sq5.toString() == "[[13,4,7][2,51,12][11,30,9]]");
    ConcreteSquareMatrix sq6 = sq4 * sq5;
    CHECK(sq6.toString() == "[[548,950,416][744,6486,1644][516,2754,792]]");
}

TEST_CASE("Concrete square matrix throw tests", "[string]")
{
    ConcreteSquareMatrix sq1;
    CHECK_THROWS(ConcreteSquareMatrix("[1,2,3][4,5,6][7,8,9]]"));
    CHECK_THROWS(ConcreteSquareMatrix("1,2,3][4,5,6][7,8,9]"));
    CHECK_THROWS(ConcreteSquareMatrix("[1,2,3][a,b,c][7,8,9]]"));
    CHECK_THROWS(ConcreteSquareMatrix("[[1,2][3,4,5][6,7,8]]"));
    CHECK_THROWS(ConcreteSquareMatrix("[[1,2,3][3,4,5][6,7,8"));
    CHECK_THROWS(ConcreteSquareMatrix("[[1,2][2,1]"));
    CHECK_NOTHROW(ConcreteSquareMatrix("[[-1,2,3][4,5,6][7,8,9]]"));
    CHECK_NOTHROW(ConcreteSquareMatrix("[[1]]"));
    ConcreteSquareMatrix sq2("[[1,2,3][4,5,6][7,8,9]]");
    CHECK_THROWS(sq1+=sq2);
    CHECK_THROWS(sq1-=sq2);
    CHECK_THROWS(sq1*=sq2);
    bool test = (sq1 == sq2);
    CHECK_FALSE(test);
}

TEST_CASE("Symbolic square matrix constructor tests", "[string]")
{
    SymbolicSquareMatrix sq1;
    CHECK(sq1.toString() == "[]");
    SymbolicSquareMatrix sq2("[[10,x][y,5]]");
    CHECK(sq2.toString() == "[[10,x][y,5]]");
    SymbolicSquareMatrix sq3(sq2);
    bool test = (sq2 == sq3);
    CHECK(test);
    SymbolicSquareMatrix sq4(std::move(sq2));
    CHECK(sq4.toString() == "[[10,x][y,5]]");
    CHECK(sq2.toString() == "[]");
}

TEST_CASE("Symbolic square matrix operator tests", "[string]")
{
    SymbolicSquareMatrix sq1;
    Valuation v;
    SymbolicSquareMatrix sq2("[[10,x,y][3,15,2][20,z,2]]");
    v['x'] = 13;
    v['y'] = 4;
    v['z'] = 30;
    sq1 = std::move(sq2);
    CHECK(sq1.toString() == "[[10,x,y][3,15,2][20,z,2]]");
    CHECK(sq2.toString() == "[]");
    sq2 = sq1;
    CHECK(sq2.toString() == "[[10,x,y][3,15,2][20,z,2]]");
    CHECK(sq1.toString() == "[[10,x,y][3,15,2][20,z,2]]");
    SymbolicSquareMatrix sq3 = sq1.transpose();
    CHECK(sq3.toString() == "[[10,3,20][x,15,z][y,2,2]]");
    bool test = (sq1 == sq3);
    CHECK_FALSE(test);
    ConcreteSquareMatrix m1 = sq1.evaluate(v);
    CHECK(m1.toString() == "[[10,13,4][3,15,2][20,30,2]]");
    SymbolicSquareMatrix sq4 = sq1 + sq2;
    ConcreteSquareMatrix m2 = sq4.evaluate(v);
    CHECK(m2.toString() == "[[20,26,8][6,30,4][40,60,4]]");
    SymbolicSquareMatrix sq5 = sq1 - sq3;
    ConcreteSquareMatrix m3 = sq5.evaluate(v);
    CHECK(m3.toString() == "[[0,10,-16][-10,0,-28][16,28,0]]");
    //SymbolicSquareMatrix sq6 = sq1 * sq2;
    //ConcreteSquareMatrix m4 = sq6.evaluate(v);
    //CHECK(m4.toString() == "[[219,445,74][115,324,46][330,770,144]]");
}

TEST_CASE("Symbolic matrix throw tests", "[string]")
{
    CHECK_THROWS(SymbolicSquareMatrix("[1,2,3][4,5,6][7,8,9]]"));
    CHECK_THROWS(SymbolicSquareMatrix("1,2,3][4,5,6][7,8,9]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[1,2][3,4,5][6,7,8]]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[1,2,3][3,4,5][6,7,8"));
    CHECK_THROWS(SymbolicSquareMatrix("[[1,2][2,1]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[1,ab][2,3]]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[1,%,2][3,4,5][6,7,8]]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[xy]]"));
    CHECK_THROWS(SymbolicSquareMatrix("[[?]]"));
    CHECK_NOTHROW(SymbolicSquareMatrix("[[-1,2,3][4,5,6][7,8,9]]"));
    CHECK_NOTHROW(SymbolicSquareMatrix("[[1]]"));
    CHECK_NOTHROW(SymbolicSquareMatrix("[[x]]"));
    SymbolicSquareMatrix sq("[[x,20][30,40]]");
    Valuation v;
    CHECK_THROWS(sq.evaluate(v));
    SymbolicSquareMatrix m("[[20,30,40][10,15,5][4,3,2]]");
    CHECK_THROWS(sq + m);
    CHECK_THROWS(sq - m);
    //CHECK_THROWS(sq * m);
}

int main(int argc, char** argv)
{
    int result = Catch::Session().run( argc, argv );
    SymbolicSquareMatrix m1;
    SymbolicSquareMatrix m2;
    std::string input;
    std::stack<std::shared_ptr<SquareMatrix>> matrices;
    Valuation v;
    char c1 = ' ';
    char c2 = ' ';
    int number = 0;
    std::stringstream strm;

    while(true)
    {
        strm.clear();
        strm.str("");
        std::cout << "Give an input" << std::endl;
        std::cin >> input;

        if(input == "quit")
            return result;

        strm << input;
        strm >> c1;
        strm >> c2;
        if(c2 == '=')
        {
            strm >> number;
            if(strm.fail())
            {
                std::cout << "You must give an integer value to the character" << std::endl;
                continue;
            }

            if(strm.rdbuf()->in_avail() == 0)
            {
                v[c1] = number;
                std::cout << "Gave character " << c1 << " the value of " << number << std::endl;
                c2 = ' ';
            }
        }
        else
        {
            if(!input.empty())
                c1 = input[0];

            if(c1 == '+')
            {
                if(matrices.empty())
                {
                    std::cout << "Stack is empty" << std::endl;
                    continue;
                }
                auto temp = matrices.top();
                try
                {
                    m1 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m1 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                matrices.pop();
                if(matrices.empty() == true)
                {
                    std::cout << "Stack only has one matrix" << std::endl;
                    matrices.push(temp);
                    continue;
                }

                try
                {
                    m2 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m2 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                SymbolicSquareMatrix res = m1 + m2;
                std::shared_ptr<SquareMatrix> res_ptr = std::make_shared<SymbolicSquareMatrix>(res);
                matrices.push(res_ptr);
                std::cout << "Added result of addition: " << res_ptr->toString() << " to the stack" << std::endl;
            }
            else if(c1 == '-')
            {
                if(matrices.empty())
                {
                    std::cout << "Stack is empty" << std::endl;
                    continue;
                }
                auto temp = matrices.top();
                try
                {
                    m1 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m1 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                matrices.pop();
                if(matrices.empty() == true)
                {
                    std::cout << "Stack only has one matrix" << std::endl;
                    matrices.push(temp);
                    continue;
                }

                try
                {
                    m2 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m2 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                SymbolicSquareMatrix res = m1 - m2;
                std::shared_ptr<SquareMatrix> res_ptr = std::make_shared<SymbolicSquareMatrix>(res);
                matrices.push(res_ptr);
                std::cout << "Added result of subtraction: " << res_ptr->toString() << " to the stack" << std::endl;
            }
            else if(c1 == '*')
            {
                if(matrices.empty() == true)
                {
                    std::cout << "Stack is empty" << std::endl;
                    continue;
                }
                auto temp = matrices.top();
                try
                {
                    m1 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m1 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                matrices.pop();
                if(matrices.empty() == true)
                {
                    std::cout << "Stack only has one matrix" << std::endl;
                    matrices.push(temp);
                    continue;
                }

                try
                {
                    m2 = SymbolicSquareMatrix(matrices.top()->toString());
                }
                catch(std::invalid_argument ia)
                {
                    try
                    {
                        m2 = SymbolicSquareMatrix(matrices.top()->evaluate(v).toString());
                    }
                    catch(std::invalid_argument ia)
                    {
                        std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                    }
                }
                SymbolicSquareMatrix res = m1 * m2;
                std::shared_ptr<SquareMatrix> res_ptr = std::make_shared<SymbolicSquareMatrix>(res);
                matrices.push(res_ptr);
                std::cout << "Added result of multiplication: " << res_ptr->toString() << " to the stack" << std::endl;
            }
            else if(c1 == '=')
            {
                try
                {
                    std::cout << matrices.top()->evaluate(v) << std::endl;
                }
                catch(std::invalid_argument ia)
                {
                    std::cout << "Couldn't do evaluation, please declare values to variables" << std::endl;
                }
            }
            else
            {
                try
                {
                    SymbolicSquareMatrix matrix(input);
                    std::shared_ptr<SquareMatrix> matrix_ptr = std::make_shared<SymbolicSquareMatrix>(matrix);
                    matrices.push(matrix_ptr);
                    std::cout << "Added matrix to stack" << std::endl;
                }
                catch(std::invalid_argument ia)
                {
                    std::cout << "Invalid input" << std::endl;
                }
            }
        }
    }
}
