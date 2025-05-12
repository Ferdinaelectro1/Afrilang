#include "Parser.h"

Parser::Parser(std::vector<Token> tokens):m_tokens(std::move(tokens)) {
    m_pos = 0;
}

Parser::Parser()
{
    m_pos = 0;
}

void Parser::next_tokens()
{
    m_current_tokens = m_tokens[m_pos];
    m_pos++;
}

void Parser::parse_print()
{
    next_tokens();
    if(m_current_tokens.get_type() == token_type::PARENT_GAUCHE)
    {
        next_tokens();
        if(m_current_tokens.get_type() == token_type::GUILLEMENT)
        {
            next_tokens();
            std::string chaine = m_current_tokens.get_value() ;
            next_tokens();
            if(m_current_tokens.get_type() == token_type::GUILLEMENT)
            {
                //std::cout << "passer m_pos = "<<m_pos<<" et token_size = "<<m_tokens.size()<<"\n ";
                next_tokens();
                if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
                {
                    next_tokens();
                    std::cout << chaine << std::endl;
                }
                else
                {
                    std::cerr <<"Manque de ) à la fin"<<std::endl;
                    m_pos = m_tokens.size();
                }
            }
            else
            {
                std::cerr <<"Manque de \" à la fin après \""<<chaine<<"\""<<std::endl;
                m_pos = m_tokens.size();
                return;
            }
        }
        else if(m_current_tokens.get_type() == token_type::LITERAL)
        {
            if(variables.find(m_current_tokens.get_value()) != variables.end())
            {
                double value = variables[m_current_tokens.get_value()];
                next_tokens();
                if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
                {
                    std::cout << value <<std::endl;
                    next_tokens();
                }
                else
                {
                    std::cerr << "Manque de ) à la fin "<<std::endl;
                    m_pos = m_tokens.size();
                    return;
                }
            }
            else
            {
                std::cerr <<"Variable \""<<m_current_tokens.get_value() << "\" non reconnu"<<std::endl;
                m_pos = m_tokens.size();
                return;
            }
        }
        else
        {
            std::cerr << "Erreur manque de \" au début  "<<std::endl;
            m_pos = m_tokens.size();
            return;
        }
    }
    else
    {
        std::cerr <<"Erreur manque de ( au début"<<std::endl;
        m_pos = m_tokens.size();
        return;
    }
}

void Parser::parse_variable()
{
    std::string var_name = m_current_tokens.get_value();
    next_tokens();
    if(m_current_tokens.get_type() == token_type::EGAL)
    {
        next_tokens();
        if(m_current_tokens.get_type() == token_type::NUMBER)
        {
            double nub1 = std::stod(m_current_tokens.get_value());
            variables[var_name] = nub1;
            next_tokens();
            if(m_current_tokens.get_type() == token_type::PLUS)
            {
                next_tokens();
                if(m_current_tokens.get_type() == token_type::NUMBER)
                {
                    nub1 = nub1 + std::stod(m_current_tokens.get_value());
                    variables[var_name] = nub1;
                    next_tokens();
                }
                else
                {
                    std::cerr << "Valeur après le + non reconnu"<<std::endl;
                    m_pos = m_tokens.size();
                    return;
                }
            }
            else if(m_current_tokens.get_type() == token_type::MOINS)
            {
                next_tokens();
                if(m_current_tokens.get_type() == token_type::NUMBER)
                {
                    nub1 = nub1 - std::stod(m_current_tokens.get_value());
                    variables[var_name] = nub1;
                    next_tokens();
                }
                else
                {
                    std::cerr << "Valeur après le - non reconnu"<<std::endl;
                    m_pos = m_tokens.size();
                    return;
                }
            }
            else
            {
                m_pos = m_tokens.size();
                return;
            }
        }
        else
        {
            std::cerr <<"Valeur non reconnu"<<std::endl;
            m_pos = m_tokens.size();
            return;
        }
    }
    else
    {
        std::cerr << "Manque de symbole d'affectation \"=\" après \""<<var_name<<"\""<<std::endl;
        m_pos = m_tokens.size();
        return;
    }
}


void Parser::parse()
{
    while(m_pos < m_tokens.size())
    {
        if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() == "afficher")
        {
            parse_print();
        }
        else if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() == "quit")
        {
            break;
        }
        else if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() != "afficher")
        {
            parse_variable();
        }
    }
}

void Parser::parse(std::vector<Token> tokens)
{
    m_tokens = tokens;
    m_pos = 0;
    next_tokens();
    parse();
}