#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "Token.h"

class Lexer
{
    public:
      Lexer(std::string code);
      std::vector<Token> generate_tokens();

    private:
      void print_error(std::string error);
      std::vector<Token> m_tokens;
      std::string m_code;
};