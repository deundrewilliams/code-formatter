#include <iostream>
#include <list>

#ifndef DATA_FILE
#define DATA_FILE

typedef enum {
    opsym = 1, lesssym, gtrsym, poundsym, semisym, lparensym, rparensym,
    lbracksym, rbracksym, lbracesym, rbracesym, periodsym, quotesym, questsym, eqlsym, commasym, slashsym,
    colonsym, typespecsym, identnumsym, spacesym, newlinesym, tabsym, structsym, inlstartsym,
    decisionsym, constsym, enumsym, linelensym, jmpsym
} tokentype;

// token.cpp
class Token {

    private:
        tokentype type;
        int value;
        std::string text;

    public:
        Token(tokentype input_type);
        Token(tokentype input_type, int input_value);
        Token(tokentype input_type, std::string input_text);

        std::string description();
        tokentype getType();
        int getValue();
        std::string getText();
};

// lexer.cpp
std::list<Token> lexer( std::string filename, bool print_flag );
void tokenize( std::ifstream file_obj );
void printTokenList(std::list<Token> tokenlist);
tokentype getBufferTokenType( std::string buffer );
tokentype getSymbolTokenType ( char symbol );

// analyzer.cpp
void analyze( std::list<Token> tokenlist );

#endif
