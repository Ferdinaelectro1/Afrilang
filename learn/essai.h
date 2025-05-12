#pragma once
/*
Grammaire bnf
<expr>   ::= <term> ('+' <term> )*
<term>   ::= <factor>('*' <factor>)*
<factor> ::= <number> | '(' <expr> ')'
*/

/*Tokenizer*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum class Token {
    NUMBER,
    PLUS,
    ASTERISK,
    LPAREN,
    RPAREN,
    END,
    INVALID
};

struct Lexeme
{
    Token type;
    std::string value;
};

class Lexer
{
    public:
      Lexer(const std::string &input);
      void next_token();
      Lexeme get_current_token() const ;

    private:
      std::istringstream stream;
      Lexeme current_token;
};
