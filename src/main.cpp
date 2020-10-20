#include <iostream>

#include "lox.h"


int main(int argc, const char* argv[])
{
    if ( argc > 2 )
    {
        std::cout << "Usage: ./cpplox <script>" << std::endl;
        std::exit( 64 );
    } else if ( argc == 2 )
    {
        runFile();
    } else 
        runREPL();
        int x;
        
}
