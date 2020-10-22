#ifndef CPPLOX_TOKEN
#define CPPLOX_TOKEN

#include <string>
#include <optional>
#include <variant>

#include "tokentype.h"
#include "literal.h"


struct Token
{

    Token(TokenType type, 
            const std::string& lexeme, 
            std::optional<Literal> literal,
            int line)
        : type(type)
        , lexeme(lexeme)
        , literal(literal)
        , line(line)
    {}

    TokenType type;
    std::string lexeme;
    std::optional<Literal> literal;
    int line;
};


std::ostream& operator<<(std::ostream& out, const Token& token);

#endif


