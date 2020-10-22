add_executable(cpplox 
    main.cpp 
    lox.cpp
    token.cpp
    tokentype.cpp)

target_compile_options(cpplox PRIVATE -Wall -Wextra -pedantic )
