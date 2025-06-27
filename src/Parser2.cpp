#include "Parser2.h"

Parser2::Parser2(std::vector<Token> tokens):m_tokens(std::move(tokens)) {
    m_pos = 0;
}

Parser2::Parser2()
{
    m_pos = 0;
}

void Parser2::next_tokens()
{
    m_current_tokens = m_tokens[m_pos];
    m_pos++;
}

std::string Parser2::get_variable(std::string var_name)
{
    if(variables.find(var_name) != variables.end())
      return std::to_string(variables[var_name]);
    else
       print_error("Erreur : Variables '"+var_name+"' non reconnu");
       return "";
}

void Parser2::print_error(std::string error)
{
    if(!(error == ""))
      std::cerr << error << std::endl;
    m_pos = m_tokens.size();
}

void Parser2::print_error_without_quit(std::string error)
{
    if(!(error == ""))
      std::cerr << error << std::endl; 
}

token_type Parser2::get_next_token_type()
{
    m_pos;
    token_type type = m_tokens[m_pos].get_type();
    return type;
}

bool Parser2::isEnd()
{
    if(m_tokens[m_pos].get_type() == token_type::FIN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Parser2::parse2(std::vector<Token> tokens)
{
    m_tokens = tokens;
    m_pos = 0;
    while (m_pos < m_tokens.size())
    {
        parseStatments(0);
    }
}

void Parser2::parseIgnore()
{
    do
    {
        next_tokens();
    }
    while (m_current_tokens.get_type() != token_type::ACCOLADE_DROITE);
}

bool Parser2::conditionValide()
{
    int left = 0;
    int right = 0;
    bool condition = false;
    left = std::stoi(parseFactor());
    next_tokens();
    std::string operateur = m_current_tokens.get_value();
    next_tokens();
    right = std::stoi(parseFactor());
    //std::cout << "right = " << right << std::endl;
    switch (operateur[0])
    {
        case '<':
            condition = left < right;
            break;
        case '>':
            condition = left > right;
            break;

        default:
            print_error("Erreur : opérateur non reconnu : '"+operateur);
            break;
    }
    return condition;
}

void Parser2::parseStatments(bool ignore)
{
    next_tokens();
    //Debut du parsage du programmme
    if(m_current_tokens.get_value() == "quit")
    {
        m_pos = m_tokens.size();
    }
    if(m_current_tokens.get_type() == token_type::FIN)
    {
        return;
    } 
    //debut pour les instructions
    if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() == "afficher")
    {
        parseAfficher(ignore);
    }
    else if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() == "if")
    {
        parseIf(ignore);
    }
    else if(m_current_tokens.get_type() == LITERAL)
    {
        parseAssignement(ignore);
    }
    else
    {
        print_error("Erreur : "+m_current_tokens.get_value()+" non reconnu (ligne invalide)");
        return;
    }
}

void Parser2::parseAfficher(bool ignore)
{
    if(!ignore)
    {
        next_tokens();
        if(m_current_tokens.get_type() == token_type::PARENT_GAUCHE)
        {
            next_tokens();
            if(m_current_tokens.get_type() == token_type::GUILLEMENT)
            {
                next_tokens();
                std::string chaine = m_current_tokens.get_value();
                next_tokens();
                if(m_current_tokens.get_type() == token_type::GUILLEMENT)
                {
                    next_tokens();
                    if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
                    {
                        std::cout << chaine << std::endl;
                    }
                    else
                    {
                        print_error("Erreur : Manque de ')' à la fin ");
                        return;
                    }
                }
                else
                {
                    print_error("Erreur : Manque de '\"' après "+chaine);
                    return;
                }
            }
            else if(m_current_tokens.get_type() == token_type::LITERAL)
            {
                if(variables.find(m_current_tokens.get_value()) != variables.end())
                {
                    std::string var_value = get_variable(m_current_tokens.get_value());
                    next_tokens();
                    if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
                    {
                        std::cout << var_value << std::endl;
                    }
                    else
                    {
                        print_error("Manque de ')' à la fin ");
                    }
                }
                else
                {
                    print_error("Erreur : Variable '"+m_current_tokens.get_value()+"' à afficher non reconnu");
                }
            }
            else if (m_current_tokens.get_type() == token_type::NUMBER)
            {
                std::string number = parseFactor(); 
                next_tokens();
                //std::cout << "passer" << std::endl;
                if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
                {
                    if(number != "")
                    std::cout << number << std::endl;
                }
                else
                {
                    print_error("Manque de ')' après "+number);
                }
            }
            else
            {
                print_error("Erreur : Élément après \"(\" inconnu ");
                return;
            }
        }
        else
        {
            print_error("Erreur : manque de '(' au début de \"afficher\" ");
            return;
        }
    }
    else
    {
        parseIgnore();
    }

}

void Parser2::parseAssignement(bool ignore)
{
    if(!ignore)
    {
        if(m_current_tokens.get_type() == LITERAL && m_current_tokens.get_value() != "quit")
        {
            std::string var_name = m_current_tokens.get_value();
            next_tokens();
            if(m_current_tokens.get_type() == token_type::EGAL)
            {
                next_tokens();
                if(m_current_tokens.get_type() == token_type::NUMBER)
                {
                    variables[var_name] = std::stod(parseExpression());
                }
                else if(m_current_tokens.get_type() == token_type::LITERAL)
                {
                variables[var_name] = std::stod(parseExpression());
                }
                else
                {
                    print_error("Valeur après le '=' "+m_current_tokens.get_value()+" non reconnu");
                }
            }
            else
            {
                print_error("Erreur manque de '=' après "+var_name);
            }
        }
    }
    else
    {
        parseIgnore();
    }
}

std::string Parser2::parseFactor()
{
    if(m_current_tokens.get_type() == token_type::NUMBER )
    {
        return m_current_tokens.get_value();
    }
    else if (get_next_token_type() == token_type::PARENT_GAUCHE)
    {
        next_tokens();
        return parseExpression();
    }
    else if(m_current_tokens.get_type() == token_type::LITERAL)
    {
        return get_variable(m_current_tokens.get_value());
    }
    else
    {
        print_error("Erreur lors de parse Factor");
        return "";
    }
}

std::string Parser2::parseTerm()
{
    if((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() != token_type::MULTIPLICATION && get_next_token_type() != token_type::DIVISION))
    {
        return parseFactor();
    }
    else if ((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() == token_type::MULTIPLICATION || get_next_token_type() == token_type::DIVISION))
    {
        double nub1 = std::stod(parseFactor());
        next_tokens();
        switch (m_current_tokens.get_type())
        {
        case token_type::MULTIPLICATION :
            next_tokens();
            if(get_next_token_type() == token_type::MULTIPLICATION || get_next_token_type() == token_type::DIVISION)
                return std::to_string((nub1 * std::stod(parseTerm())));
            else if (get_next_token_type() == token_type::PLUS || get_next_token_type() == token_type::MOINS)
                return std::to_string((nub1 * std::stod(parseExpression())));
            else
                return std::to_string((nub1 * std::stod(parseFactor())));
            break;
        
        case token_type::DIVISION :
            next_tokens();
            if(get_next_token_type() == token_type::MULTIPLICATION || get_next_token_type() == token_type::DIVISION)
                return std::to_string((nub1 / std::stod(parseTerm())));
            else if (get_next_token_type() == token_type::PLUS || get_next_token_type() == token_type::MOINS)
                return std::to_string((nub1 / std::stod(parseExpression())));
            else
                return std::to_string((nub1 / std::stod(parseFactor())));
            break;
        }
    }
    else
    {
        print_error("Erreur lors de parseTerm");
        return "";
    }
}

std::string Parser2::parseExpression()
{
    if((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() == token_type::PLUS || get_next_token_type() == token_type::MOINS))
    {
        double nub1 = std::stod(parseTerm());
        next_tokens();
        switch (m_current_tokens.get_type())
        {
        case token_type::PLUS :
            next_tokens();
            while (get_next_token_type() == token_type::MOINS || get_next_token_type() == token_type::PLUS)
            {
                if(m_tokens[m_pos-2].get_type() == token_type::PLUS)
                {
                   nub1 += std::stod(parseTerm());
                  // std::cout << "passer et nub1  = "<< nub1<< std::endl;
                }
                else
                {
                   nub1 -= std::stod(parseTerm());
                }
                nub1 += std::stod(parseTerm());
                next_tokens();
                next_tokens();
            }
            if (m_tokens[m_pos - 2].get_type() == token_type::PLUS)
            {
                nub1 += std::stod(parseTerm());
            }
            else
            {
                nub1 -= std::stod(parseTerm());
            }
            return std::to_string(nub1);
            break;
        
        case token_type::MOINS :
            next_tokens();
            if(get_next_token_type() == token_type::MOINS || get_next_token_type() == token_type::PLUS)
                return std::to_string((nub1 - std::stod(parseExpression())));
            else
                return std::to_string((nub1 - std::stod(parseTerm())));
            break;
        }
    }
    else if((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() != token_type::PLUS && get_next_token_type() != token_type::MOINS))
    {
        return parseTerm();
    }
    else
    {
        print_error("Erreur lors de parseExpression");
        return "";
    }
}

//Parser un if
void Parser2::parseIf(bool ignore)
{
    if(!ignore)
    {
        next_tokens();
        if(m_current_tokens.get_type() == token_type::PARENT_GAUCHE)
        {
            next_tokens();
            bool condition;
            condition = conditionValide();
            next_tokens();
            if(m_current_tokens.get_type() == token_type::PARENT_DROITE)
            {
                next_tokens();
                if(m_current_tokens.get_type() == token_type::ACCOLADE_GAUCHE)
                {
                    if(condition)
                        parseStatments(0);
                    else
                        parseStatments(1);
                    
                    if(condition)
                    {
                        next_tokens();
                    }
                }
                else
                {
                    print_error("Erreur : Manque de '{' après la condition ");
                }
            }
            else
            {
                print_error("Erreur : Manque de ')' à la fin de la condition ");
            }
        }
        else
        {
            print_error("Erreur : Manque de '(' au début de 'if'");
        }
    }
    else
    {
        parseIgnore();
    }
}



/*
std::string Parser2::parseExpression()
{
    if((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() == token_type::PLUS || get_next_token_type() == token_type::MOINS))
    {
        double nub1 = std::stod(parseTerm());
        next_tokens();
        switch (m_current_tokens.get_type())
        {
        case token_type::PLUS :
            next_tokens();
            if(get_next_token_type() == token_type::MOINS || get_next_token_type() == token_type::PLUS)
                return std::to_string((nub1 + std::stod(parseExpression())));
            else
                return std::to_string((nub1 + std::stod(parseTerm())));
            break;
        
        case token_type::MOINS :
            next_tokens();
            if(get_next_token_type() == token_type::MOINS || get_next_token_type() == token_type::PLUS)
                return std::to_string((nub1 - std::stod(parseExpression())));
            else
                return std::to_string((nub1 - std::stod(parseTerm())));
            break;
        }
    }
    else if((m_current_tokens.get_type() == token_type::NUMBER || m_current_tokens.get_type() == token_type::LITERAL) && (get_next_token_type() != token_type::PLUS && get_next_token_type() != token_type::MOINS))
    {
        return parseTerm();
    }
    else
    {
        print_error("Erreur lors de parseExpression");
        return "";
    }
}*/




