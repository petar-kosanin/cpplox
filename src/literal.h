#ifndef CPPLOX_LITERAL
#define CPPLOX_LITERAL 4

#include <variant>
#include <string>
#include <iostream>

struct LiteralValueVisitor
{
    std::ostream& out;

    LiteralValueVisitor(std::ostream& out)
        : out(out)
    {
    }

    void operator()(const std::string& value)
    {
        out << value;
    }
    
    void operator()(double value)
    {
        out << value;
    }

    void operator()(bool value)
    {
        out << value;
    }
};

struct Literal
{
    std::variant<
                 std::string
                , double
                , bool
                > value;

};

#endif
