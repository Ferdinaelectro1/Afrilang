#include "Token.h"

Token::Token(token_type type, std::string value) : m_type(type),m_value(value) {}

std::string Token::get_value()
{
    return m_value;
}

token_type Token::get_type()
{
    return m_type;
}

void Token::set_token(const Token& token)
{
    m_type = token.m_type;
    m_value = token.m_value;
}

void Token::set_token(token_type type, std::string value)
{
    m_type = type;
    m_value = value;
}