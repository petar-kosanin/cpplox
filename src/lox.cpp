#include "lox.h"
#include "scanner.h"



void Lox::runFile(const std::string& path)
{
    auto data = readFile(path);
    run( data );

    if ( hadError ) std::exit( 65 );
}

void Lox::run(std::string& source)
{
    auto scanner = std::make_unique<Scanner>(source);
    auto tokens = scanner->tokenize();

    for ( const Token& token : tokens )
    {
        std::cout << token;
    }
}

void Lox::runREPL()
{
    std::string input;
    std::string line;
    while ( true )
    {
        std::cout << "cpplox> ";
        if ( std::getline(std::cin, line) ) 
            run( line );

        hadError = false;
    }
}

std::string Lox::readFile(const std::string& path)
{
    std::ifstream file(path);
    assert( file );

    std::string data;
    std::string buffer;
    while ( std::getline(file, buffer) )
        data.append( buffer );

    return data;
}


void Lox::error(int line, const std::string& message)
{
    report( line, "", message );
}

void Lox::report(
        int line, 
        const std::string& where, 
        const std::string& message)
{
    std::cerr   << "[line " 
                << "] Error " 
                << where << " " 
                << message << "\n";
    hadError = true;
}
