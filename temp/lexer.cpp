#include "lexer.h"

Lexer::Lexer(std::string code): m_code(code){}

std::vector<Token> Lexer::generate_tokens()
{
    //ignorer les espaces du code et crée un nouveau code (temp_code) sans espace
    std::string temp_code = "";
    bool isguillement = 0;
    for(char element : m_code)
    {
      if(element != ' ' && element != '\n')
      {
          temp_code += element;
      }
    }
    //création des tokens
    std::string chaine = "";
    for(int i = 0; i < temp_code.size() ; i++)
    {
        //si il s'agit d'une lettre
        if(std::isalpha(temp_code[i]))
        {
            //si le caractère à venir est une lettre on continue de lire la chaine sinon on génère un token
            if(std::isalpha(temp_code[i+1]))
              chaine += temp_code[i];
            else
            {
                chaine += temp_code[i];
                m_tokens.push_back(Token(LITERAL,chaine));
                chaine = "";           
            }
        }
        //si il s'agit d'un nombre
        else if (std::isdigit(temp_code[i]))
        {
            //si le caractère à venir est un chiffre on continue de lire la chaine sinon on génère un token
            if(std::isdigit(temp_code[i+1]))
              chaine += temp_code[i];
            else
            {
                chaine += temp_code[i];
                m_tokens.push_back(Token(NUMBER,chaine));
                chaine = "";           
            }
        }
        else
        {
            switch (temp_code[i])
            {
                case '+':
                  m_tokens.push_back(Token(PLUS,""));
                  break;
                case '-':
                  m_tokens.push_back(Token(MOINS,""));
                  break;
                case '*':
                  m_tokens.push_back(Token(MULTIPLICATION,""));
                  break;
                case '/':
                  m_tokens.push_back(Token(DIVISION,""));
                  break;
                case '(':
                  m_tokens.push_back(Token(PARENT_GAUCHE,""));
                  break;
                case ')':
                  m_tokens.push_back(Token(PARENT_DROITE,""));
                  break;
                case '"':
                  m_tokens.push_back(Token(GUILLEMENT,""));
                  break;
                case '=':
                  m_tokens.push_back(Token(EGAL,""));
                  break;
                default:
                  m_tokens.push_back(Token(OTHER,""));
                  break;
            }
            
        }
    }
    //ajout d'un token de fin pour signaler la fin des tokens
    m_tokens.push_back(Token(FIN,""));
    return m_tokens;
}

void Lexer::print_error(std::string error)
{
    std::cerr << "Erreur : "<<error<<std::endl;
}




