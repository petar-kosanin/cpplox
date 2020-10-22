cmake_minimum_required(VERSION 3.14)


project(CPPLOX  VERSION 0.1.0 
                DESCRIPTION "cpp version on crafting interpreters lox"
                LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
