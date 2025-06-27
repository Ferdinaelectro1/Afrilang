#pragma once
#include <string>

enum token_type
{
    PLUS,
    MOINS,
    MULTIPLICATION,
    DIVISION,
    NUMBER,
    LITERAL,
    EGAL,
    PARENT_GAUCHE,
    PARENT_DROITE,
    GUILLEMENT,
    OTHER,
    BOOL,
    CHAINE_CARACTERE,
    ACCOLADE_DROITE,
    ACCOLADE_GAUCHE,
    INFERIEUR,
    SUPERIEUR,
    FIN
};


class Token
{
    public:
      Token() = default;
      Token(token_type type, std::string value);
      std::string get_value();
      token_type get_type();
      void set_token(const Token& token);
      void set_token(token_type type, std::string value);
    
    private:
      token_type m_type;
      std::string m_value;
};