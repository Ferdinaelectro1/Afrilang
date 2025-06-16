#include "src/lexer2.h"
#include "src/Parser2.h"
#include "src/Token.h"
#include "src/run_file.h"
#include "src/run_console.h"

int main(int argc, char *argv[])
{
    std::string code;
    Parser2 parser;
    if(argc == 1)
    {
        run_console();
    }
    else if(argc == 2)
    {
        run_file(argv[1]);
    }  
    else
    {
        std::cerr << "Format d'entrée : './Afrilang' ou './Afrilang fileName'"<<std::endl;
    }
    return 0;
}