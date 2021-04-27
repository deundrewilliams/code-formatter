#include <iostream>

#include "data.h"

int main( int argc, char **argv ) {

    if (argc < 2) {
        std::cout << "Format: ./a.out <file>\n";
        return 1;
    }

    std::cout << "Analyzing '" << argv[1] << "'\n";

    bool print_tokens = false;

    if (argc == 3)
        print_tokens = true;

    std::list<Token> token_list = lexer(argv[1], print_tokens);
    analyze(token_list);

    return 0;
}
