#include "token.h"



std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << "{Type: " << token.type << " " 
        << "Lexeme: \"" << token.lexeme << "\" "
        << "Literal: "; 
    if ( token.literal.has_value() )
        std::visit(
                LiteralValueVisitor{out}, 
                // literal is optional of Literal,
                // value is variant, member variable of Literal
                token.literal.value().value);
    else
        out << "null ";
    out << "Line: " << token.line;
    out << "}\n";

    return out;
}
