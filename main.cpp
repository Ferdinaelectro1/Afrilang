#include "src/lexer2.h"
#include "src/Parser2.h"
#include "src/Token.h"
#include "src/run_file.h"

int main(int argc, char *argv[])
{
    std::string code;
    Parser2 parser;
    if(argc == 1)
    {
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
    else if(argc == 2)
    {
        run_file(argv[1]);
    }  
    else
    {
        std::cerr << "Format d'entrée : './Afrilang' ou './Afrilang fileName'"<<std::endl;
    }
/*     std::vector<Token> tokens;
    Lexer2 lexer("af f ich er(\"Mon ie ur\") et toi");
    tokens = lexer.generate_tokens();   */
    return 0;
}