#include "data.h"


tokentype type;
int value;
std::string text;


Token::Token(tokentype input_type) : type{ input_type }, value{ -1 } {}

Token::Token(tokentype input_type, int input_value) : type{ input_type }, value{ input_value } {}

Token::Token(tokentype input_type, std::string input_text) : type{ input_type }, text{ input_text } {}

std::string Token::description() {

    switch (type)
    {
    case identnumsym:
        return "IDENTNUMSYM (" + text + ")";
    case typespecsym:
        return "TYPESPECSYM";
    case jmpsym:
        return "JMPSYM";
    case spacesym:
        return "SPACESYM (" + std::to_string(value) + ")";
    case linelensym:
        return "LINELEN (" + std::to_string(value) + ")";
    case newlinesym:
        return "NEWLINESYM";
    case opsym:
        return "OPSYM";
    case poundsym:
        return "POUNDSYM";
    case lparensym:
        return "LPARENSYM";
    case rparensym:
        return "RPARENSYM";
    case lbracksym:
        return "LBRACKSYM";
    case rbracksym:
        return "RBRACKSYM";
    case eqlsym:
        return "EQLSYM";
    case semisym:
        return "SEMISYM";
    case lbracesym:
        return "LBRACESYM";
    case rbracesym:
        return "RBRACESYM";
    case slashsym:
        return "SLASHSYM";

    default:
        return "INVALIDSYM";
    }


}

tokentype Token::getType() {
    return type;
}

int Token::getValue() {
    return value;
}
std::string Token::getText() {
    return text;
}
