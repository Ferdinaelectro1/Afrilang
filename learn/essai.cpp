#include "essai.h"

Lexer::Lexer(const std::string &input): stream(input), current_token(Lexeme{Token::INVALID,""})
{
    next_token();
}

void Lexer::next_token()
{
    char current_char;
    if(!(stream >> current_char))
    {
        current_token = {Token::END,""};
        return;
    }
    if(isdigit(current_char))
    {
        stream.putback(current_char);
        int value;
        stream >> value;
        current_token = {Token::NUMBER,std::to_string(value)};
    }
    else if (current_char == '+')
    {
        current_token = {Token::PLUS,"+"};
    }
    else if (current_char == '*')
    {
        current_token = {Token::ASTERISK,"*"};
    }
    else if (current_char == '(')
    {
        current_token = {Token::LPAREN,"("};
    }
    else if (current_char == ')')
    {
        current_token = {Token::RPAREN,")"};
    }
    else
    {
        current_token = {Token::INVALID,std::string(1,current_char)};
    }
}

Lexeme Lexer::get_current_token() const 
{
    return current_token;
}