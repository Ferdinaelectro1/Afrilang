cmake_minimum_required(VERSION 3.2)

project(My_compiler)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    src/Token.cpp
    src/lexer2.cpp
    src/Parser2.cpp
    #lexer.cpp
    #ASTNode.cpp
    #Parser.cpp
)