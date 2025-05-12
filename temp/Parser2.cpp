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
    return std::to_string(variables[var_name]);
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
        parseStatments();
    }
}

void Parser2::parseStatments()
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
    if(m_current_tokens.get_type() == token_type::LITERAL && m_current_tokens.get_value() == "afficher")
    {
        parseAfficher();
    }
    else if(m_current_tokens.get_type() == LITERAL)
    {
        parseAssignement();
    }
    else
    {
        print_error("Erreur : "+m_current_tokens.get_value()+" non reconnu (ligne invalide)");
        return;
    }
}

void Parser2::parseAfficher()
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

std::string Parser2::calculator(std::string first_number,char operateur)
{
    next_tokens();
    if(get_next_token_type() == token_type::NUMBER || get_next_token_type() == token_type::LITERAL)
    {
        next_tokens();
        double nub2;
        if(m_current_tokens.get_type() == token_type::LITERAL)
        {
            if(variables.find(m_current_tokens.get_value()) != variables.end())
              nub2 = variables[m_current_tokens.get_value()];
            else
              print_error_without_quit("Erreur : la variable '"+m_current_tokens.get_value()+"' n'est pas reconnu");
              return "";
        }
        else
        {
            nub2 = std::stod(m_current_tokens.get_value());
        }
        double nub1 = std::stod(first_number);
        switch (operateur)
        {
        case '+':
            return std::to_string(nub1+nub2);
            break;
        case '-':
            return std::to_string(nub1-nub2);
            break;
        case '*':
            return std::to_string(nub1*nub2);
            break;
        case '/':
            return std::to_string(nub1/nub2);
            break;
        default:
            return "";
            break;
        }
    }
    else
    {
        std::string str_op(1,operateur);
        print_error_without_quit("Erreur : Valeur après le "+str_op+" non reconnu");
        return "";
    }
}

std::string Parser2::parseFactor()
{
    std::string number = m_current_tokens.get_value();
    if(get_next_token_type() == token_type::DIVISION)
    {
        return calculator(number,'/');
    }
    else if(get_next_token_type() == token_type::MULTIPLICATION)
    {
        return calculator(number,'*');
    }
    else if(get_next_token_type() == token_type::PLUS)
    {
        return calculator(number,'+');
    }
    else if (get_next_token_type() == token_type::MOINS)
    {
        return calculator(number,'-');
    }
    else if(get_next_token_type() == token_type::LITERAL)
    {
        next_tokens();
        std::string litteral_inconnu = m_current_tokens.get_value();
        if(get_next_token_type() == token_type::NUMBER)
          next_tokens();
        print_error_without_quit("Erreur : Littéral '"+litteral_inconnu+"' non reconnu !! ");
        return "";
    }
    else 
    {
        return number;
    }
}

void Parser2::parseAssignement()
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
                variables[var_name] = std::stod(m_current_tokens.get_value());
            }
            else if(m_current_tokens.get_type() == token_type::LITERAL)
            {
                if(variables.find(m_current_tokens.get_value()) != variables.end())
                {
                    variables[var_name] = variables[m_current_tokens.get_value()];
                }
                else
                {
                    print_error("Erreur : Variable '"+m_current_tokens.get_value()+"' non trouvé");
                }
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





