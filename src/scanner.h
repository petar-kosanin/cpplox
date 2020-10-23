#ifndef CPPLOX_SCANNER
#define CPPLOX_SCANNER 5

#include <string>
#include <vector>


#include "token.h"
#include "lox.h"


class Scanner
{
public:
    Scanner(const std::string& source)
        : source(source)
    {
    }


    std::vector<Token> tokenize()
    {
        while ( !isAtEnd() )
        {
            start = current;
            scanToken();
        }

        tokens.push_back({TokenType::ENDOFFILE, "", std::nullopt, line});
        return tokens;
    }

private:

    void scanToken() {
        char c = advance();
        switch (c) 
        {
            case '(': addToken( TokenType::LEFT_PAREN );    break;
            case ')': addToken( TokenType::RIGHT_PAREN );   break;
            case '{': addToken( TokenType::LEFT_BRACE );    break;
            case '}': addToken( TokenType::RIGHT_BRACE );   break;
            case ',': addToken( TokenType::COMMA );         break;
            case '.': addToken( TokenType::DOT );           break;
            case '-': addToken( TokenType::MINUS );         break;
            case '+': addToken( TokenType::PLUS );          break;
            case ';': addToken( TokenType::SEMICOLON );     break;
            case '*': addToken( TokenType::STAR );          break; 
            case '!':
                addToken(
                    advanceIfMatch('=') ? TokenType::BANG_EQUAL : TokenType::BANG );
                break;
            case '=':
                addToken(
                    advanceIfMatch('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL );
                break;
            case '>':
                addToken(
                    advanceIfMatch('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER );
                break;
            case '<':
                addToken(
                    advanceIfMatch('=') ? TokenType::LESS_EQUAL : TokenType::LESS );
                break;
            case '\n':
                ++line;
                break;
            // ignore whitespaces
            case ' ':
            case '\t':
            case '\r':
                break;
            case '/':
                // if it's a comment
                if ( advanceIfMatch('/') )
                {
                    // eat whole line
                    
                    while ( peek() != '\n' && !isAtEnd() ) advance();
                } else
                    addToken( TokenType::SLASH );
                break;
            case '"':
                matchString();
                break;
            default: 
                if ( isDigit( c ) )
                {
                    number();
                } else 
                {
                    loxInstance.error(line, "Unrecognized character");
                }
        }
    }

    bool isDigit(char c) const
    {
        return c >= '0' && c <= '9';
    }

    void number()
    {
        while ( isDigit( peek() ) && !isAtEnd() ) advance();

        if ( peek() == '.' && isDigit( peekNext() ) ) 
            advance();

        while ( isDigit( peek() ) && !isAtEnd() ) advance();

        double value = std::stod( source.substr( start, current - start ) );
        Literal literal{value};
        addToken(TokenType::NUMBER, literal);
    }

    char peekNext() const
    {
        if ( current + 1 >= source.length() ) return '\0';
        return source.at( current + 1 );
    }

    void matchString()
    {
        while ( peek() != '"' && !isAtEnd() )
        {
            if ( source.at( current ) == '\n' ) ++line;
            advance();
        }

        if ( isAtEnd() )
            loxInstance.error(line, "Unterminated string");

        advance();
        std::string lexeme = source.substr( start + 1, current - start - 2);
        Literal l{lexeme};
        addToken(TokenType::STRING, l);
    }

    // lookahead - returns current unconsumed character
    char peek() const
    {
        if ( isAtEnd() ) return '\0';
        return source.at( current ); 
    }


    bool advanceIfMatch(char expected)
    {
        if ( isAtEnd() ) return false;
        if ( source.at( current ) != expected ) return false;

        current++;
        return true;
    }


    // add token with empty literal 
    // eg, we don't need + literal, but need Integers and Strings
    void addToken(TokenType type)
    {
        addToken(type, {});
    }

    void addToken(TokenType type, std::optional<Literal> literal)
    {
        std::string text = source.substr( start, current - start );
        tokens.push_back( { type, text, literal, line } );
    }


    char advance()
    {
        return source.at(current++);
    }


    bool isAtEnd() const
    {
        return current >= source.length();
    }
private:
    const std::string source;
    std::vector<Token> tokens = std::vector<Token>();
    Lox& loxInstance = Lox::instance();

    unsigned int start = 0;
    unsigned int current = 0;
    unsigned int line = 0;

};

#endif
