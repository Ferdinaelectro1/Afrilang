#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Token.h"

class Parser
{
    public:
      Parser();
      Parser(std::vector<Token> tokens);
      void parse();
      void parse(std::vector<Token> tokens);
    
    private:
      std::vector<Token> m_tokens;
      Token m_current_tokens;
      int m_pos;
      std::unordered_map<std::string,double> variables; 
      void avance();
      void next_tokens();
      void parse_litteral();
      void parse_operation();
      void parse_print();
      void parse_number();
      void parse_variable();
};