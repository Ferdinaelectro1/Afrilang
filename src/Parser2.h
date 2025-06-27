#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Token.h"

class Parser2
{
    public:
      Parser2();
      Parser2(std::vector<Token> tokens);
      void parse2();
      void parse2(std::vector<Token> tokens);
    
    private:
      std::vector<Token> m_tokens;
      Token m_current_tokens;
      int m_pos;
      std::unordered_map<std::string,double> variables; 
      std::string get_variable(std::string var_name);
      std::string calculator(std::string first_number,char operateur);
      void consume();
      void next_tokens();
      token_type get_next_token_type();
      bool isEnd();
      void parseAssignement(bool ignore);
      void parseStatments(bool ignore);
      std::string parseExpression();
      void parseAfficher(bool ignore);
      void parseIf(bool ignore);
      std::string parseTerm();
      std::string parseFactor();
      void parseIgnore();
      void print_error(std::string error);
      void print_error_without_quit(std::string error);
      void parseElse(bool ignore);
      bool conditionValide();
};