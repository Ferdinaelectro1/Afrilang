#include "lexer2.h"
#include "Parser2.h"
#include "Token.h"

int main(void)
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
/*     std::vector<Token> tokens;
    Lexer2 lexer("af f ich er(\"Mon ie ur\") et toi");
    tokens = lexer.generate_tokens();   */
    return 0;
}