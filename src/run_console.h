#ifndef __RUN_CONSOLE__
#define __RUN_CONSOLE__
#include <iostream>
#include <string>
#include "Parser2.h"
#include "lexer2.h"

void run_console()
{
    std::string code;
    Parser2 parser;
    system("clear");
    std::cout << "" << std::endl;
    std::cout <<"Bienvenue dans Afrilang. Veuillez saisir vos lignes de code."<<std::endl;
    std::cout << "" << std::endl;
    while (code != "quit")
    {
        std::cout << ">> ";
        std::getline(std::cin,code);
        Lexer2 lexer(code);
        parser.parse2(lexer.generate_tokens());
    }
}

#endif