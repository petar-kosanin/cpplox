#include <iostream>

#include "lox.h"
#include "token.h"


int main(int argc, const char* argv[])
{

    Lox& lox = Lox::instance();
    if ( argc > 2 )
    {
        std::cout << "Usage: ./cpplox <script>" << std::endl;
        std::exit( 64 );
    } else if ( argc == 2 )
    {
        lox.runFile( argv[1] );
    } else 
        lox.runREPL(); 
}
