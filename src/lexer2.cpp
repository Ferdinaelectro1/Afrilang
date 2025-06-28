/*ATI ferdinand 
Lokossa 
11 mars 2025*/

#include "lexer2.h"

Lexer2::Lexer2(std::string code): m_code(code),isChaine(0){}

std::string Lexer2::tokenize_chaine(char caractere)
{
    if(caractere == '"')
    {
        
    }
    return "";
}

bool Lexer2::ischaine(char caractere)
{
    if(caractere == '"')
      isChaine =  !isChaine;
    
    return isChaine;
}

std::vector<Token> Lexer2::generate_tokens()
{
    //ignorer les espaces du code et crée un nouveau code (temp_code) sans espace
    std::string temp_code = "";
    for(char element : m_code)
    {
        if(!ischaine(element))
        {
          if(element != ' ' && element != '\n')
          {
          temp_code += element;
          }
        }
        else
        {
            temp_code += element;
        }
    }

    //reinitialisation de isChaine afin de pouvoir reutiliser la fonction ischaine sans maintenir les anciennes valeurs de isChaine
    isChaine = false;
    //création des tokens
    std::string chaine = "";
    for(int i = 0; i < temp_code.size() ; i++)
    {
        if(!ischaine(temp_code[i]))
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
                    m_tokens.push_back(Token(PLUS,"+"));
                    break;
                    case '-':
                    m_tokens.push_back(Token(MOINS,"-"));
                    break;
                    case '*':
                    m_tokens.push_back(Token(MULTIPLICATION,"*"));
                    break;
                    case '/':
                    m_tokens.push_back(Token(DIVISION,"/"));
                    break;
                    case '(':
                    m_tokens.push_back(Token(PARENT_GAUCHE,"("));
                    break;
                    case ')':
                    m_tokens.push_back(Token(PARENT_DROITE,")"));
                    break;
                    case '"':
                    m_tokens.push_back(Token(GUILLEMENT,"\""));
                    break;
                    case '{':
                    m_tokens.push_back(Token(ACCOLADE_GAUCHE,"{"));
                    break;
                    case '}':
                    m_tokens.push_back(Token(ACCOLADE_DROITE,"}"));
                    break;
                    case '<':
                    if(temp_code[i+1] == '=')
                    {
                        m_tokens.push_back(Token(INFERIEUR_EGAL,"<="));
                        i++; //on saute le '=' suivant
                    }
                    else
                        m_tokens.push_back(Token(INFERIEUR,"<"));
                    break;
                    case '>':
                    if(temp_code[i+1] == '=')
                    {
                        m_tokens.push_back(Token(SUPERIEUR_EGAL,">="));
                        i++; //on saute le '=' suivant
                    }
                    else
                        m_tokens.push_back(Token(SUPERIEUR,">"));
                    break;
                    case '!':
                    if(temp_code[i+1] == '=')
                    {
                        m_tokens.push_back(Token(DIFFERENT,"!="));
                        i++; //on saute le '=' suivant
                    }
                    else
                    {
                        m_tokens.push_back(Token(OTHER,"!"));
                    }
                    break;
                    case '=':
                    if(temp_code[i+1] == '=')
                    {
                        m_tokens.push_back(Token(EGALITE,"=="));
                        i++; //on saute le '=' suivant
                    }
                    else
                        m_tokens.push_back(Token(EGAL,"="));
                    break;
                    default:
                    m_tokens.push_back(Token(OTHER,""));
                    break;
                }
                
            }
        }
        else
        {
            //si c'est le caractere " on ajoute un token guillements 
            if(temp_code[i] == '"')
            {
                m_tokens.push_back(Token(GUILLEMENT,"\""));
            }

            //d'abord si le caratere est un " et le suivant est un " on ajoute directement une chaine vide
            //ensuite si le caratère n'est pas un " et le suivant n'est pas aussi un " alors on icremente la chaine 
            //ensuite si le caractère n'est pas un " et le suivant est un " on ajoute le caractere à la chaine et on retourne un token chaine de caractere 
            //et on remet chaine à ""(chaine vide afin de permettre un nouveau usage de chaine)
            if(temp_code[i] == '"' && temp_code[i+1] == '"')
            {
                m_tokens.push_back(Token(CHAINE_CARACTERE,""));
            }
            else if(temp_code[i] != '"' && temp_code[i+1] != '"')
            {
                chaine += temp_code[i];
            }
            else if(temp_code[i] != '"' && temp_code[i+1] == '"')
            {
                chaine += temp_code[i];
                m_tokens.push_back(Token(CHAINE_CARACTERE,chaine));
                chaine = "";
            }
        }
    }
    //ajout d'un token de fin pour signaler la fin des tokens
    m_tokens.push_back(Token(FIN,""));
    return m_tokens;
}

void Lexer2::print_error(std::string error)
{
    std::cerr << "Erreur : "<<error<<std::endl;
}




