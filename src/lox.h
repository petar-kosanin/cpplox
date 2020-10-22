#ifndef CPPLOX_LOX
#define CPPLOX_LOX 1

#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <memory>

#include "token.h"



class Lox 
{
public:
    // #TODO move to private ?
    bool hadError = false;


    Lox(const Lox& other) = delete;
    void operator=(const Lox& other) = delete;


    // Lox is a singleton class
    static Lox& instance()
    {
        static Lox instance;
        return instance;
    }

    // read data from file and run interpreter on its data
    void runFile(const std::string& path);


    // enter (loop (print (eval (read) ))) mode 
    void runREPL();

    
    void error(int line, const std::string& message);

private:
    // Lox is a singleton, hiding its constructor
    Lox() = default;


    std::string readFile(const std::string& path);


    void run(std::string& source);


    void report(
            int line, 
            const std::string& where, 
            const std::string& message);
};


#endif
