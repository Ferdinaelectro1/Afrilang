cmake_minimum_required(VERSION 3.2)

project(My_compiler)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    Token.cpp
    lexer2.cpp
    Parser2.cpp
    #lexer.cpp
    #ASTNode.cpp
    #Parser.cpp
)