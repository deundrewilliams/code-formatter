#include <iostream>
#include <fstream>
#include <list>
#include <set>

#include "data.h"

std::list<Token> lexer( std::string filename, bool print_flag ) {

    std::ifstream myFile(filename);

    std::list<Token> tokenlist{};

    char c;

    std::string buffer = "";

    int line_length = 0;

    while (myFile.get(c)) {

        line_length++;

        // If a letter or number
        if (isalnum(c)) {
            // Append to buffer
            buffer.push_back(c);
        }

        // If not a letter
        else {

            // If whitespace
            if (isspace(c)) {

                // If new line
                if (c == '\n') {

                    if (!buffer.empty()) {

                        // Analyze buffer and add token
                        // std::cout << "Analyzing '" << buffer << "'\n";
                        tokentype new_type = getBufferTokenType(buffer);

                        if (new_type == identnumsym) {
                            tokenlist.push_back(Token(identnumsym, buffer));
                        }

                        else {
                            tokenlist.push_back(Token(new_type));
                        }

                        // Clear buffer
                        buffer.clear();
                    }

                    // Add line length token
                    // std::cout << "LINECOUNT (" << line_length << ")\n";
                    tokenlist.push_back(Token(linelensym, line_length - 1));

                    // Add new line token
                    // std::cout << "NEWLINESYM\n";
                    tokenlist.push_back(Token(newlinesym));



                    // Reset line length to 0
                    line_length = 0;
                }

                // If space, add space token
                else if (c == ' ') {

                    if (!buffer.empty()) {

                        // Analyze buffer and add token
                        // std::cout << "Analyzing '" << buffer << "'\n";
                        tokentype new_type = getBufferTokenType(buffer);

                        if (new_type == identnumsym) {
                            tokenlist.push_back(Token(identnumsym, buffer));
                        }

                        else {
                            tokenlist.push_back(Token(new_type));
                        }

                        // Clear buffer
                        buffer.clear();
                    }
                    // Clear buffer
                    buffer.clear();

                    // Add space token
                    // std::cout << "SPACESYM\n";
                    tokenlist.push_back(Token(spacesym));

                }
            }

            // If a symbol
            else {

                if (!buffer.empty()) {

                        // Analyze buffer and add token
                        // std::cout << "Analyzing '" << buffer << "'\n";
                        tokentype new_type = getBufferTokenType(buffer);

                        if (new_type == identnumsym) {
                            tokenlist.push_back(Token(identnumsym, buffer));
                        }

                        else {
                            tokenlist.push_back(Token(new_type));
                        }

                        // Clear buffer
                        buffer.clear();
                }

                // Clear buffer
                buffer.clear();

                // Determine symbol type and add token
                // std::cout << c << " SYM\n";
                tokenlist.push_back(Token(getSymbolTokenType(c)));

            }


        }
    }

    myFile.close();

    if (print_flag)
        printTokenList(tokenlist);

    return tokenlist;

}

// Returns the token type based on the text in the buffer
tokentype getBufferTokenType( std::string buffer ) {

    std::set<std::string> typespec_words {"void", "char", "short", "int", "long", "float", "double",
        "signed", "unsigned"};

    std::set<std::string> jump_words {"goto", "continue", "break", "return"};


    if (typespec_words.find(buffer) != typespec_words.end()) {
        return typespecsym;
    }

    else if (jump_words.find(buffer) != jump_words.end()) {
        return jmpsym;
    }

    else {
        return identnumsym;
    }

}

// Returns the token type based on the symbol
tokentype getSymbolTokenType ( char symbol ) {

    switch (symbol)
    {
    case '#':
        return poundsym;
    case '(':
        return lparensym;
    case ')':
        return rparensym;
    case '{':
        return lbracksym;
    case '}':
        return rbracksym;
    case '=':
        return eqlsym;
    case ';':
        return semisym;
    case '/':
        return slashsym;

    default:
        return opsym;
    }

}

// Prints a description of each token in the token list
void printTokenList(std::list<Token> tokenlist) {

    std::list<Token>::iterator i;

    for (i = tokenlist.begin(); i != tokenlist.end(); i++) {

        std::cout << i->description() << "\n";

    }


}

