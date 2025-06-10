#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "Token.h"

class Lexer2
{
    public:
      Lexer2(std::string code);
      std::vector<Token> generate_tokens();

    private:
      void print_error(std::string error);
      std::string tokenize_chaine(char caractere);
      bool ischaine(char caractere);
      std::vector<Token> m_tokens;
      std::string m_code;
      bool isChaine;
};