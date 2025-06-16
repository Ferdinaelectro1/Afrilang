#ifndef __RUN_FILE_H__
#define __RUN_FILE_H__
#include <string>
#include <fstream>
#include <algorithm>
#include "lexer2.h"
#include "Parser2.h"
#include "Token.h"

void run_file(const std::string file_name)
{
    const int file_size = file_name.size();
    if(!(file_name[file_size - 1] == 'r' && file_name[file_size - 2] == 'f' && file_name[file_size - 3] == 'a' && file_name[file_size - 4] == '.'))
    {
        std::cerr << "Erreur : Fichier non reconnu. L'extention doit être '.afr'"<< std::endl;
        return;
    }
    std::ifstream file;
    file.open(file_name);
    if(!file)
    {
        std::cerr << "Erreur lors de l'ouverture du fichier : '"<<file_name<<"'"<<std::endl;
        return;
    }

    std::string line_code = "";
    Parser2 parser;
    while (std::getline(file,line_code))
    {  
        Lexer2 lexer(line_code);
        parser.parse2(lexer.generate_tokens()); 
    }
    file.close();
}

#endif